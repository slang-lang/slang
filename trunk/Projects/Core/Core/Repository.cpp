
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
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Consts.h"
#include "Memory.h"
#include "Preprocessor.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Repository::Repository(Memory *m)
: mMemory(m)
{
	addBlueprint(Runtime::BoolObject());
	addBlueprint(Runtime::FloatObject());
	addBlueprint(Runtime::IntegerObject());
	addBlueprint(Runtime::NumberObject());
	addBlueprint(Runtime::StringObject());
	addBlueprint(Runtime::VoidObject());
}

Repository::~Repository()
{
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

void Repository::addBlueprint(const Designtime::BluePrint& object)
{
	OSinfo("addBlueprint('" + object.Typename() + "')");

	BluePrints::iterator it = mBluePrints.find(object.Typename());
	if ( it != mBluePrints.end() ) {
		throw Utils::Exceptions::Exception("duplicate object '" + object.Typename() + "' added to repository");
	}

	mBluePrints.insert(std::make_pair(object.Typename(), object));

	BluePrints::iterator objIt = mBluePrints.find(object.Typename());

	// loop over all tokens of a blueprint object
	// and retype all identifier tokens with object names as values with type
	bool replaced = false;
	TokenList tokens = objIt->second.getTokens();

	for ( TokenList::iterator tokenIt = tokens.begin(); tokenIt != tokens.end(); ++tokenIt ) {
		// we found an identifier token
		if ( tokenIt->type() == Token::Type::IDENTIFER ) {
			// check if it's content is one of our newly added blueprint objects
			if ( tokenIt->content() != object.Typename() && mBluePrints.find(tokenIt->content()) != mBluePrints.end() ) {
				tokenIt->resetTypeTo(Token::Type::TYPE);

				replaced = true;
			}
		}
	}

	if ( replaced ) {
		objIt->second.setTokens(tokens);
	}
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

	switch ( object->languageFeatureState() ) {
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
		if ( it->second <= 0 ) {
			if ( it->first ) {
				// call object's destructor ...
				it->first->Destructor();

				// ... and delete it
				delete it->first;
			}

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

	Runtime::Object *object = createObject(name, blueprint.Filename(), prototype + type);
	object->setTokens(blueprint.getTokens());

	Preprocessor preprocessor(this);
	preprocessor.process(object);

	object->define(KEYWORD_THIS, object);

	addReference(object);

	return object;
}

Runtime::Object* Repository::createObject(const std::string& name, const std::string& filename, const std::string& type)
{
	Runtime::Object *object = 0;

	if ( type == Runtime::BoolObject::TYPENAME ) {
		object = new Runtime::BoolObject(name, Runtime::BoolObject::DEFAULTVALUE);
	}
	else if ( type == Runtime::FloatObject::TYPENAME ) {
		object = new Runtime::FloatObject(name, Runtime::FloatObject::DEFAULTVALUE);
	}
	else if ( type == Runtime::IntegerObject::TYPENAME ) {
		object = new Runtime::IntegerObject(name, Runtime::IntegerObject::DEFAULTVALUE);
	}
	else if ( type == Runtime::NumberObject::TYPENAME ) {
		object = new Runtime::NumberObject(name, Runtime::NumberObject::DEFAULTVALUE);
	}
	else if ( type == Runtime::StringObject::TYPENAME ) {
		object = new Runtime::StringObject(name, Runtime::StringObject::DEFAULTVALUE);
	}
	else if ( type == Runtime::VoidObject::TYPENAME ) {
		object = new Runtime::VoidObject(name);
	}
	else {
		object = new Runtime::UserObject(name, filename, type, Runtime::UserObject::DEFAULTVALUE);
	}

	object->setRepository(this);
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

	Runtime::Object *object = createObject(name, blueprint.Filename(), type);
	object->setTokens(blueprint.getTokens());

	Preprocessor preprocessor(this);
	preprocessor.process(object);

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
		delete it->first;

		mInstances.erase(it);
	}
}


}
