
// Header
#include "Repository.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/NumberObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Consts.h"
#include "Memory.h"
#include "Method.h"
#include "Preprocessor.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Repository::Repository(Memory *m)
: mMemory(m)
{
	addBlueprint(Designtime::BoolObject());
	addBlueprint(Designtime::FloatObject());
	addBlueprint(Designtime::IntegerObject());
	addBlueprint(Designtime::NumberObject());
	addBlueprint(Designtime::StringObject());
	addBlueprint(Designtime::VoidObject());
}

Repository::~Repository()
{
	for ( BluePrints::iterator it = mBluePrints.begin(); it != mBluePrints.end(); ++it ) {
		it->second.cleanup();
	}
	mBluePrints.clear();

	for ( ReferenceCountedObjects::iterator it = mInstances.begin(); it != mInstances.end(); ++it ) {
		it->first->Destructor();
	}
	for ( ReferenceCountedObjects::iterator it = mInstances.begin(); it != mInstances.end(); ++it ) {
		delete it->first;
	}
	mInstances.clear();

	mPrototypes.clear();
}

void Repository::addBlueprint(const Designtime::BluePrint& blueprint)
{
	OSinfo("addBlueprint('" + blueprint.Typename() + "')");

	BluePrints::iterator it = mBluePrints.find(blueprint.Typename());
	if ( it != mBluePrints.end() ) {
		throw Utils::Exceptions::Exception("duplicate object '" + blueprint.Typename() + "' added to repository");
	}

	mBluePrints.insert(std::make_pair(blueprint.Typename(), blueprint));

	BluePrints::iterator blueIt = mBluePrints.find(blueprint.Typename());

	// loop over all tokens of a blueprint object
	// and retype all identifier tokens with object names as values with type
	bool replaced = false;
	TokenList tokens = blueIt->second.getTokens();

	for ( TokenList::iterator tokenIt = tokens.begin(); tokenIt != tokens.end(); ++tokenIt ) {
		// we found an identifier token
		if ( tokenIt->type() == Token::Type::IDENTIFER ) {
			// check if its content is one of our newly added blueprint objects
			if ( tokenIt->content() != blueprint.Typename() && mBluePrints.find(tokenIt->content()) != mBluePrints.end() ) {
				tokenIt->resetTypeTo(Token::Type::TYPE);

				replaced = true;
			}
		}
	}

	if ( replaced ) {
		blueIt->second.setTokens(tokens);
	}

	Preprocessor preprocessor(this);
	preprocessor.process(&blueIt->second);
}

void Repository::addPrototype(const Prototype& prototype)
{
	std::string type = prototype.type();

	Prototypes::iterator it = mPrototypes.find(type);
	if ( it != mPrototypes.end() ) {
		throw Utils::Exceptions::Exception("duplicate object '" + type + "' added to repository");
	}

	mPrototypes.insert(std::make_pair(type, prototype));
}

void Repository::addReference(Runtime::Object *object)
{
	if ( !object ) {
		return;
	}

	switch ( object->getLanguageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + object->getName() + "' is marked as deprecated!"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + object->getName() + "' is marked as not implemented!"); throw Utils::Exceptions::NotImplemented(object->getName()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so no need to log anything here */ break;
		case LanguageFeatureState::Unknown: OSerror("unknown language feature state set for method '" + object->getName() + "'!"); break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + object->getName() + "' is marked as unstable!"); break;
	}

	ReferenceCountedObjects::iterator it = mInstances.find(object);
	if ( it != mInstances.end() ) {
		// increment reference count
		it->second++;
		return;
	}

	mInstances.insert(std::make_pair(object, 1));
}

void Repository::CollectGarbage()
{
	for ( ReferenceCountedObjects::iterator it = mInstances.begin(); it != mInstances.end(); ) {
		if ( it->second > 0 ) {
			++it;
			continue;
		}

		// as soon as we've lost all references, we can destroy our object
		if ( it->first && it->second <= 0 ) {
			// call object's destructor ...
			it->first->Destructor();
			// ... and delete it
			delete it->first;

			it = mInstances.erase(it);
		}
	}
}

Runtime::Object* Repository::createInstance(const std::string& type, const std::string& name, const std::string& prototype)
{
	OSinfo("createInstance('" + type + "', '" + name + "', '" + prototype + "')");

	// non-reference-based instantiation
	Designtime::BluePrint blueprint;

	Prototypes::iterator it = mPrototypes.find(prototype);
	if ( it != mPrototypes.end() ) {
		blueprint = it->second.generateBluePrint(type);
	}
	else {
		BluePrints::iterator it = mBluePrints.find(type);
		if ( it != mBluePrints.end() ) {
			blueprint = it->second;
		}
		else {
			throw Utils::Exceptions::Exception("trying to create instance of unknown object '" + type + "'");
		}
	}

	Runtime::Object *object = createObject(name, &blueprint);

	addReference(object);

	return object;
}

Runtime::Object* Repository::createObject(const std::string& name, Designtime::BluePrint* blueprint)
{
	Runtime::Object *object = 0;

	// instantiate atomic types
	if ( blueprint->Typename() == Runtime::BoolObject::TYPENAME ) {
		object = new Runtime::BoolObject(name, Runtime::BoolObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::FloatObject::TYPENAME ) {
		object = new Runtime::FloatObject(name, Runtime::FloatObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::IntegerObject::TYPENAME ) {
		object = new Runtime::IntegerObject(name, Runtime::IntegerObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::NumberObject::TYPENAME ) {
		object = new Runtime::NumberObject(name, Runtime::NumberObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::StringObject::TYPENAME ) {
		object = new Runtime::StringObject(name, Runtime::StringObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::VoidObject::TYPENAME ) {
		object = new Runtime::VoidObject(name);
	}
	else {
		// instantiate user defined type
		object = new Runtime::UserObject(name, blueprint->Filename(), blueprint->Typename(), Runtime::UserObject::DEFAULTVALUE);

		object->setRepository(this);

		// define this-symbol
		object->define(KEYWORD_THIS, object);

		// create and define all members
		Symbols symbols = blueprint->provideSymbols();
		for ( Symbols::const_iterator it = symbols.begin(); it != symbols.end(); ++it ) {
			if ( !it->second || it->second->getType() != Symbol::IType::BluePrintSymbol ) {
				continue;
			}

			Designtime::BluePrint *blue = static_cast<Designtime::BluePrint*>(it->second);
			if ( blue->isAbstract() ) {
				throw Utils::Exceptions::AbstractException("cannot instantiate abstract object '" + blue->Typename() + "'");
			}

			Symbol *symbol = createInstance(blue->Typename(), blue->getName(), "");

			object->define(symbol->getName(), symbol);
		}

		// define and create all methods
		MethodScope::MethodCollection methods = blueprint->provideMethods();
		for ( MethodScope::MethodCollection::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
			Runtime::Method* method = new Runtime::Method(object, (*it)->getName(), (*it)->getTypeName());
			*method = *(*it);

			object->defineMethod(method);
		}
	}

	assert(object);
	return object;
}

const Reference& Repository::createReference(const std::string& type, const std::string& name, const std::string& prototype)
{
	// reference-based instantiation
	Designtime::BluePrint blueprint;

	Prototypes::iterator it = mPrototypes.find(prototype);
	if ( it != mPrototypes.end() ) {
		blueprint = it->second.generateBluePrint(type);
	}
	else {
		BluePrints::iterator it = mBluePrints.find(type);
		if ( it != mBluePrints.end() ) {
			blueprint = it->second;
		}
		else {
			throw Utils::Exceptions::Exception("trying to create instance of unknown object '" + type + "'");
		}
	}

	Runtime::Object *object = createObject(name, &blueprint);

	return mMemory->newObject(object);
}

bool Repository::isAlreadyKnown(const std::string& name) const
{
	return mBluePrints.find(name) != mBluePrints.end();
}

void Repository::removeReference(Runtime::Object *object)
{
	if ( !object ) {
		return;
	}

	ReferenceCountedObjects::iterator it = mInstances.find(object);
	if ( it == mInstances.end() ) {
		return;
	}

	// decrement reference count
	it->second--;

	// as soon as we removed all references, we can destroy our object
	if ( it->first && it->second <= 0 ) {
		// call object's destructor ...
		it->first->Destructor();
		// ... and delete it
		//delete it->first;

		//mInstances.erase(it);
	}
}


}
