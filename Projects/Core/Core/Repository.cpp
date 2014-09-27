
// Header
#include "Repository.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/Bool.h>
#include <Core/BuildInObjects/Number.h>
#include <Core/BuildInObjects/String.h>
#include <Core/BuildInObjects/Void.h>
#include "Exceptions.h"
#include "Preprocessor.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Repository::Repository()
{
	addBlueprint(Bool());
	addBlueprint(Number());
	addBlueprint(String());
	addBlueprint(Void());
}

Repository::~Repository()
{
	mBluePrints.clear();
}

void Repository::addBlueprint(const BluePrint& object)
{
	std::string type = object.Typename();

	OSdebug("addBlueprint('" + type + "')");

	BluePrints::iterator it = mBluePrints.find(type);
	if ( it != mBluePrints.end() ) {
		throw Exception("duplicate object '" + type + "' added to repository");
	}

	mBluePrints.insert(
		std::make_pair<std::string, BluePrint>(type, object)
	);
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
		throw Exception("duplicate object '" + type + "' added to repository");
	}

	mPrototypes.insert(
		std::make_pair<std::string, Prototype>(type, prototype)
	);
/*
	Prototypes::iterator objIt = mPrototypes.find(type);

	// loop over all tokens of a prototype blueprint object
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
*/
}

Object Repository::createInstance(const std::string& type, const std::string& name)
{
	OSdebug("createInstance('" + type + "', '" + name + "')");

	BluePrints::iterator it = mBluePrints.find(type);
	if ( it == mBluePrints.end() ) {
		throw Exception("trying to create instance of unknown object '" + type + "'");
	}

	Object object(name, it->second.filename(), type, "");
	object.setTokens(it->second.getTokens());

	Preprocessor pre;
	pre.process(&object);

	return object;
}

Object Repository::createInstanceFromPrototype(const std::string& prototype, const std::string& type, const std::string& name)
{
	OSdebug("createInstanceFromPrototype('" + prototype + ", " + type + "', '" + name + "')");

	Prototypes::iterator it = mPrototypes.find(prototype);
	if ( it == mPrototypes.end() ) {
		throw Exception("trying to create prototype instance of unknown object '" + type + "'");
	}

	BluePrint blue = it->second.generateBluePrint(type);

	Object object(name, blue.filename(), prototype + " of " + type, "");
	object.setTokens(blue.getTokens());

	Preprocessor pre;
	pre.process(&object);

	return object;
}

bool Repository::isAlreadyKnown(const std::string& name) const
{
	return mBluePrints.find(name) != mBluePrints.end();
}


}
