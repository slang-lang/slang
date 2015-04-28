
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

	for ( Objects::iterator it = mInstances.begin(); it != mInstances.end(); ++it ) {
		if ( (*it) ) {
			delete (*it);
			(*it) = 0;
		}
	}

	mInstances.clear();
	mPrototypes.clear();
}

void Repository::addBlueprint(const BluePrint& object)
{
	std::string type = object.Typename();

	OSdebug("addBlueprint('" + type + "')");

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

	OSdebug("addPrototype('" + type + "')");

	Prototypes::iterator it = mPrototypes.find(type);
	if ( it != mPrototypes.end() ) {
		throw Utils::Exception("duplicate object '" + type + "' added to repository");
	}

	mPrototypes.insert(std::make_pair(type, prototype));
}

Object* Repository::createInstance(const std::string& type, const std::string& name)
{
	OSdebug("createInstance('" + type + "', '" + name + "')");

	BluePrints::iterator it = mBluePrints.find(type);
	if ( it == mBluePrints.end() ) {
		throw Utils::Exception("trying to create instance of unknown object '" + type + "'");
	}

	// non-reference-based instantiation
	return createInstance(it->second, type, name);
}

Object* Repository::createInstance(const BluePrint& blueprint, const std::string& type, const std::string& name)
{
	// non-reference-based instantiation

	Object *object = new Object(name, blueprint.Filename(), type, "");
	object->setTokens(blueprint.getTokens());

	Preprocessor preprocessor(object);
	preprocessor.process();

	mInstances.insert(object);

	return object;
}

Object* Repository::createInstanceFromPrototype(const std::string& prototype, const std::string& type, const std::string& name)
{
	OSdebug("createInstanceFromPrototype('" + prototype + ", " + type + "', '" + name + "')");

	Prototypes::iterator it = mPrototypes.find(prototype);
	if ( it == mPrototypes.end() ) {
		throw Utils::Exception("trying to create prototype instance of unknown object '" + type + "'");
	}

	// non-reference-based instantiation
	return createInstance(it->second.generateBluePrint(type), prototype + type, name);
}

const Reference& Repository::createReference(const std::string& type, const std::string& name)
{
	OSdebug("createReference('" + type + "', '" + name + "')");

	BluePrints::iterator it = mBluePrints.find(type);
	if ( it == mBluePrints.end() ) {
		throw Utils::Exception("trying to create reference on unknown object '" + type + "'");
	}

	return createReference(it->second, type, name);
}

const Reference& Repository::createReference(const BluePrint& blueprint, const std::string& type, const std::string& name)
{
	// reference-based instantiation

	Object *obj = new Object(name, blueprint.Filename(), type, "");
	obj->setTokens(blueprint.getTokens());

	Preprocessor preprocessor(obj);
	preprocessor.process();

	return mMemory->newObject(obj);
}

const Reference& Repository::createReferenceFromPrototype(const std::string& prototype, const std::string& type, const std::string& name)
{
	OSdebug("createReferenceFromPrototype('" + prototype + ", " + type + "', '" + name + "')");

	Prototypes::iterator it = mPrototypes.find(prototype);
	if ( it == mPrototypes.end() ) {
		throw Utils::Exception("trying to create prototype reference on unknown object '" + type + "'");
	}

	return createReference(it->second.generateBluePrint(type), prototype + type, name);
}

bool Repository::isAlreadyKnown(const std::string& name) const
{
	return mBluePrints.find(name) != mBluePrints.end();
}


}
