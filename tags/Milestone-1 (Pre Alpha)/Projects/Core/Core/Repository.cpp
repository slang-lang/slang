
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
	addBlueprint(BoolObject());
	addBlueprint(FloatObject());
	addBlueprint(IntegerObject());
	addBlueprint(NumberObject());
	addBlueprint(StringObject());
	addBlueprint(VoidObject());
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

void Repository::addBlueprint(const BluePrint& object)
{
	std::string type = object.Typename();

	//OSinfo("addBlueprint('" + type + "')");

	BluePrints::iterator it = mBluePrints.find(type);
	if ( it != mBluePrints.end() ) {
		throw Utils::Exceptions::Exception("duplicate object '" + type + "' added to repository");
	}

	mBluePrints.insert(std::make_pair(type, object));

	BluePrints::iterator objIt = mBluePrints.find(type);

	// loop over all tokens of a blueprint object
	// and retype all identifier tokens with object names as values with type
	bool replaced = false;
	TokenList tokens = objIt->second.getTokens();

	for ( TokenList::iterator tokenIt = tokens.begin(); tokenIt != tokens.end(); ++tokenIt ) {
		// we found an identifier token
		if ( tokenIt->type() == Token::Type::IDENTIFER ) {
			// check if it's content is one of our newly added blueprint objects
			if ( tokenIt->content() != type && mBluePrints.find(tokenIt->content()) != mBluePrints.end() ) {
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

void Repository::addReference(Object *object)
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

Object* Repository::createInstance(const std::string& type, const std::string& name, const std::string& prototype)
{
	OSinfo("createInstance('" + type + "', '" + name + "', '" + prototype + "')");

	// non-reference-based instantiation
	BluePrint blueprint;

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

	Object *object = createObject(name, blueprint.Filename(), prototype + type);
	object->setTokens(blueprint.getTokens());
	object->connectRepository(this);

	Preprocessor preprocessor(this);
	preprocessor.process(object);
	//preprocessor.processScope(object, object->getTokens());

	addReference(object);

	return object;
}

Object* Repository::createObject(const std::string& name, const std::string& filename, const std::string& type)
{
	Object *object = 0;

	if ( type == BoolObject::TYPENAME ) {
		object = new BoolObject(name, BoolObject::DEFAULTVALUE);
	}
	else if ( type == FloatObject::TYPENAME ) {
		object = new FloatObject(name, FloatObject::DEFAULTVALUE);
	}
	else if ( type == IntegerObject::TYPENAME ) {
		object = new IntegerObject(name, IntegerObject::DEFAULTVALUE);
	}
	else if ( type == NumberObject::TYPENAME ) {
		object = new NumberObject(name, NumberObject::DEFAULTVALUE);
	}
	else if ( type == StringObject::TYPENAME ) {
		object = new StringObject(name, StringObject::DEFAULTVALUE);
	}
	else if ( type == VoidObject::TYPENAME ) {
		object = new VoidObject(name);
	}
	else {
		object = new UserObject(name, filename, type, UserObject::DEFAULTVALUE);
	}

	return object;
}

const Reference& Repository::createReference(const std::string& type, const std::string& name, const std::string& prototype)
{
	// reference-based instantiation
	BluePrint blueprint;

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

	Object *object = createObject(name, blueprint.Filename(), type);
	object->setTokens(blueprint.getTokens());
	object->connectRepository(this);

	Preprocessor preprocessor(this);
	preprocessor.process(object);
	//preprocessor.processScope(object, object->getTokens());

	return mMemory->newObject(object);
}

bool Repository::isAlreadyKnown(const std::string& name) const
{
	return mBluePrints.find(name) != mBluePrints.end();
}

void Repository::removeReference(Object *object)
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