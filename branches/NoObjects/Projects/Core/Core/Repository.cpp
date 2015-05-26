
// Header
#include "Repository.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/Bool.h>
#include <Core/BuildInObjects/Number.h>
#include <Core/BuildInObjects/String.h>
#include <Core/BuildInObjects/Void.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Memory.h"
#include "Preprocessor.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Repository::Repository(Memory *m)
: mMemory(m)
{
	addBlueprint(Bool());
	addBlueprint(Number());
	addBlueprint(String());
	addBlueprint(Void());
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
		throw Utils::Exception("duplicate object '" + type + "' added to repository");
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

	//OSinfo("addPrototype('" + type + "')");

	Prototypes::iterator it = mPrototypes.find(type);
	if ( it != mPrototypes.end() ) {
		throw Utils::Exception("duplicate object '" + type + "' added to repository");
	}

	mPrototypes.insert(std::make_pair(type, prototype));
}

void Repository::addReference(Object *object)
{
	if ( !object ) {
		return;
	}

	switch ( object->languageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + object->name() + "' is marked as deprecated!"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + object->name() + "' is marked as not implemented!"); throw Utils::NotImplemented(object->name()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so no need to log anything here */ break;
		case LanguageFeatureState::Unknown: OSerror("unknown language feature state set for method '" + object->name() + "'!"); break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + object->name() + "' is marked as unstable!"); break;
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
	//OSinfo("createInstance('" + type + "', '" + name + "', '" + prototype + "')");

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
			throw Utils::Exception("trying to create instance of unknown object '" + type + "'");
		}
	}

	Object *object = new Object(name, blueprint.Filename(), prototype + type, "");
	object->setTokens(blueprint.getTokens());
	object->connectRepository(this);

	Preprocessor preprocessor;
	preprocessor.process(object);

	addReference(object);

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
			throw Utils::Exception("trying to create instance of unknown object '" + type + "'");
		}
	}

	Object *object = new Object(name, blueprint.Filename(), type, "");
	object->setTokens(blueprint.getTokens());
	object->connectRepository(this);

	Preprocessor preprocessor;
	preprocessor.process(object);

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
