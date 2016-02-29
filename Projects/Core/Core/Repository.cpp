
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
#include "Preprocessor.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Repository::Repository()
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
	// Cleanup blue prints
	// {
	for ( Designtime::BluePrintMap::iterator it = mBluePrints.begin(); it != mBluePrints.end(); ++it ) {
		it->second.cleanup();
	}
	mBluePrints.clear();
	// }

	// Cleanup instances
	// {
	for ( ReferenceCountedObjects::iterator it = mInstances.begin(); it != mInstances.end(); ++it ) {
		it->first->Destructor();
	}

	for ( ReferenceCountedObjects::iterator it = mInstances.begin(); it != mInstances.end(); ++it ) {
		delete it->first;
	}
	mInstances.clear();
	// }

	// Cleanup prototypes
	// {
	mPrototypes.clear();
	// }
}

void Repository::addBlueprint(const Designtime::BluePrint& blueprint)
{
	OSinfo("addBlueprint('" + blueprint.Typename() + "')");

	Designtime::BluePrintMap::iterator it = mBluePrints.find(blueprint.Typename());
	if ( it != mBluePrints.end() ) {
		throw Utils::Exceptions::Exception("duplicate object '" + blueprint.Typename() + "' added to repository");
	}

	mBluePrints.insert(std::make_pair(blueprint.Typename(), blueprint));

	Designtime::BluePrintMap::iterator blueIt = mBluePrints.find(blueprint.Typename());

	// loop over all tokens of a blueprint object
	// and retype all identifier tokens with object names as values with type
	// {
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
	// }

	Preprocessor preprocessor(this);
	preprocessor.process(&blueIt->second);
}

void Repository::addPrototype(const Designtime::Prototype& prototype)
{
	std::string type = prototype.type();

	Designtime::PrototypeMap::iterator it = mPrototypes.find(type);
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
	bool success = true;

	while ( success ) {
		success = false;

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
/*
				delete it->first;

				it = mInstances.erase(it);
*/
				success = true;
			}
		}
	}
}

Runtime::Object* Repository::createInstance(const std::string& type, const std::string& name, const std::string& prototype)
{
	// non-reference-based instantiation
	OSinfo("createInstance('" + type + "', '" + name + "', '" + prototype + "')");

	Designtime::BluePrint blueprint;

/*
	Prototypes::iterator it = mPrototypes.find(prototype);
	if ( it != mPrototypes.end() ) {
		blueprint = it->second.generateBluePrint(type);
	}
	else {
*/
		Designtime::BluePrintMap::iterator it = mBluePrints.find(type);
		if ( it != mBluePrints.end() ) {
			blueprint = it->second;
		}
		else {
			throw Utils::Exceptions::Exception("trying to create instance of unknown object '" + type + "'");
		}
/*
	}
*/

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
	// instantiate user defined type
	else {
		object = createUserObject(name, blueprint);
	}

	object->setConst(blueprint->isConst());
	object->setFinal(blueprint->isFinal());
	object->setLanguageFeatureState(blueprint->getLanguageFeatureState());
	object->setMember(blueprint->isMember());
	object->setRepository(this);
	object->setVisibility(blueprint->getVisibility());

	return object;
}

Runtime::Object* Repository::createUserObject(const std::string& name, Designtime::BluePrint* blueprint)
{
	assert(blueprint);

	if ( blueprint->isAbstract() ) {
		throw Utils::Exceptions::AbstractException("cannot instantiate abstract object '" + blueprint->Typename() + "'");
	}

	Runtime::Object *object = new Runtime::UserObject(name, blueprint->Filename(), blueprint->Typename(), Runtime::UserObject::DEFAULTVALUE);
	object->define(KEYWORD_THIS, object);	// define this-symbol

	//Designtime::Ancestors ancestors = blueprint->getAncestors();
	Designtime::Ancestors ancestors = blueprint->getInheritance();

	if ( !ancestors.empty() ) {
		object->define(KEYWORD_BASE, object);
	}

	// add our base object to our ancestor collection (thanks to Ancestor::Type::Base sort places it in first position)
	ancestors.insert(Designtime::Ancestor(
		blueprint->Typename(), Designtime::Ancestor::Type::Base, Visibility::Public
	));

	// walk through inheritance and create all members and methods
	for ( Designtime::Ancestors::const_iterator ancestorIt = ancestors.begin(); ancestorIt != ancestors.end(); ++ancestorIt ) {
		Designtime::BluePrintMap::const_iterator blueIt = mBluePrints.find(ancestorIt->name());
		if ( blueIt == mBluePrints.end() ) {
			throw Utils::Exceptions::Exception("trying to initialize unknown object '" + ancestorIt->name() + "'");
		}

		// create and define all members
		Symbols symbols = blueIt->second.provideSymbols();
		for ( Symbols::const_iterator it = symbols.begin(); it != symbols.end(); ++it ) {
			if ( !it->second ||
				 it->second->getType() != Symbol::IType::BluePrintSymbol ) {
				continue;
			}

			Designtime::BluePrint *blue = static_cast<Designtime::BluePrint*>(it->second);

			Runtime::Object *symbol = createInstance(blue->Typename(), blue->getName(), "");
			symbol->setConst(blue->isConst());
			symbol->setFinal(blue->isFinal());
			symbol->setLanguageFeatureState(blue->getLanguageFeatureState());
			symbol->setMember(blue->isMember());
			symbol->setRepository(this);
			symbol->setVisibility(blue->getVisibility());

			object->define(symbol->getName(), symbol);
		}

		// define and create all methods
		ObjectScope::MethodCollection methods = blueIt->second.provideMethods();
		for (ObjectScope::MethodCollection::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
			Runtime::Method* method = new Runtime::Method(object, (*it)->getName(), (*it)->Typename());
			*method = *(*it);

			MethodSymbol* baseMethod = object->resolveMethod(method->getName(), method->provideSignature(), true);
			if ( baseMethod ) {
				// override base method by undefining it
				object->undefineMethod(static_cast<Runtime::Method*>(baseMethod));
				delete baseMethod;
			}

			object->defineMethod(method);
		}
	}

	return object;
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
