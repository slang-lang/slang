
// Header
#include "Analyser.h"

// Library includes
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Tools/Files.h>
#include "SanityChecker.h"
#include "Scope.h"
#include "Tokenizer.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Analyser::Analyser(IScope* /*scope*/)
//: mScope(scope)
{
}

Analyser::~Analyser()
{
}

BluePrint Analyser::createBluePrint(TokenIterator& start, TokenIterator end)
{
	std::string languageFeature;
	std::string name;
	std::string visibility;

	// look for the visibility token
	visibility = (*start++).content();
	// look for the object token
	(*start++).content();
	// look for an optional language feature token
	if ( start->isOptional() ) {
		languageFeature = (*start++).content();
	}
	// look for the identifier token
	name = (*start).content();

	// look for the next opening curly brackets
	TokenIterator open = findNext(++start, Token::Type::BRACKET_CURLY_OPEN);
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

	BluePrint::Ancestors parents;

	// check if we have some more tokens before our object declarations starts
	if ( start != open ) {
		if ( start->content() == "extends" ) {
			// collect inheritances
			start++;

			do {
				std::string inheritance = (*start++).content();
				std::string ancestor = (*start++).content();

//				parents[ancestor] = BluePrint::Ancestor(ancestor, Visibility::convert(inheritance));
			} while ( std::distance(start, open) > 0 && ++start != end );
		}
		else if ( start->content() == "implements" ) {
			// collect inheritances
			start++;

			std::string inheritance = (*start++).content();
			parents[inheritance] = BluePrint::Ancestor(inheritance, Visibility::Public);
		}
		else {
			throw Utils::Exceptions::Exception("invalid token '" + start->content() + "' during object declaration");
		}
	}

	// collect all tokens of this object
	TokenList tokens;

	for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
		tokens.push_back((*it));
	}

	start = closed;

	SanityChecker sanity;
	sanity.process(tokens);

	BluePrint blue(name, mFilename);
	blue.setAncestors(parents);
	blue.setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	blue.setTokens(tokens);
	blue.setVisibility(Visibility::convert(visibility));

	return blue;
}

std::string Analyser::createLibraryReference(TokenIterator& start, TokenIterator end)
{
	std::string reference;

	start++;

	while ( start->type() != Token::Type::SEMICOLON && start != end ) {
		reference += (*start++).content();
	}

	return reference;
}

Interface Analyser::createInterface(TokenIterator& start, TokenIterator end)
{
	std::string languageFeature;
	std::string name;
	std::string visibility;

	// look for the visibility token
	visibility = (*start++).content();
	// look for the object token
	(*start++).content();
	// look for an optional language feature token
	if ( start->isOptional() ) {
		languageFeature = (*start++).content();
	}
	// look for the identifier token
	name = (*start).content();

	// look for the next opening curly brackets
	TokenIterator open = findNext(++start, Token::Type::BRACKET_CURLY_OPEN);
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

	// check if we have some more tokens before our object declarations starts
	if ( start != open ) {
		throw Utils::Exceptions::Exception("invalid token '" + start->content() + "' during interface declaration");
	}

	// collect all tokens of this object
	TokenList tokens;

	for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
		tokens.push_back((*it));
	}

	start = closed;

	SanityChecker sanity;
	sanity.process(tokens);

	Interface inter(name, mFilename);
	inter.setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	inter.setTokens(tokens);

	return inter;
}

void Analyser::createNamespace(TokenIterator& start, TokenIterator end)
{
	std::string languageFeature;
	std::string name;
	std::string visibility;

	// look for the visibility token
	visibility = (*start++).content();
	// look for the object token
	(*start++).content();
	// look for an optional language feature token
	if ( start->isOptional() ) {
		languageFeature = (*start++).content();
	}
	// look for the identifier token
	name = (*start).content();

	// look for the next opening curly brackets
	TokenIterator open = findNext(++start, Token::Type::BRACKET_CURLY_OPEN);
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

	// collect all tokens of this object
	TokenList tokens;
	for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
		tokens.push_back((*it));
	}

	SanityChecker sanity;
	sanity.process(tokens);

	//mScope = new LocalScope(name, mScope);

	generate(tokens);

	start = closed;
}

Prototype Analyser::createPrototype(TokenIterator& start, TokenIterator end)
{
	return Prototype(createBluePrint(start, end));
}

void Analyser::generate(const TokenList& tokens)
{
	TokenList::const_iterator it = tokens.begin();

	// loop over all tokens and look for imports and object declarations
	while ( it != tokens.end() && it->type() != Token::Type::ENDOFFILE ) {
		if ( isInterfaceDeclaration(it) ) {
			Interface i = createInterface(it, tokens.end());
			mInterfaces.push_back(i);
		}
		else if ( isLibraryReference(it) ) {
			std::string reference = createLibraryReference(it, tokens.end());
			mLibraries.push_back(reference);
		}
		else if ( isNamespaceDeclaration(it) ) {
			createNamespace(it, tokens.end());
		}
		else if ( isObjectDeclaration(it) ) {
			BluePrint o = createBluePrint(it, tokens.end());
			mBluePrints.push_back(o);
		}
		else if ( isPrototypeDeclaration(it) ) {
			Prototype p = createPrototype(it, tokens.end());
			mPrototypes.push_back(p);
		}

		it++;
	}
}

TokenList Analyser::generateTokens(const std::string& content)
{
	Tokenizer t(mFilename, content);
	t.process();

	return t.tokens();
}

const BluePrintList& Analyser::getBluePrints() const
{
	return mBluePrints;
}

const InterfaceList& Analyser::getInterfaces() const
{
	return mInterfaces;
}

const StringList& Analyser::getLibraryReferences() const
{
	return mLibraries;
}

const PrototypeList& Analyser::getPrototypes() const
{
	return mPrototypes;
}

// syntax:
// <visibility> interface [language feature] <identifier> ;
bool Analyser::isInterfaceDeclaration(TokenIterator start)
{
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}
	if ( (*start).type() != Token::Type::TYPE && (*start++).content() != "interface" ) {
		return false;
	}
	if ( (*start).isOptional() && (*start++).type() != Token::Type::LANGUAGEFEATURE ) {
		return false;
	}
	if ( (*start++).type() != Token::Type::IDENTIFER ) {
		return false;
	}

	return true;
}

// syntax:
// import <identifier> ;
bool Analyser::isLibraryReference(TokenIterator start)
{
	TokenList tokens;

	if ( (*start++).content() != "import" ) {
		return false;
	}

	tokens.push_back(Token(Token::Type::IDENTIFER));
	tokens.push_back(Token(Token::Type::SEMICOLON));

	return checkSynthax(start, tokens);
}

// syntax:
// <visibility> namespace [language feature] <identifier>
bool Analyser::isNamespaceDeclaration(TokenIterator start)
{
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}
	if ( (*start).type() != Token::Type::TYPE && (*start++).content() != "namespace" ) {
		return false;
	}
	if ( (*start).isOptional() && (*start++).type() != Token::Type::LANGUAGEFEATURE ) {
		return false;
	}
	if ( (*start++).type() != Token::Type::IDENTIFER ) {
		return false;
	}

	return true;
}

// syntax:
// <visibility> object [language feature] <identifier> [extends <identifier> [, <identifier>, ...]]
bool Analyser::isObjectDeclaration(TokenIterator start)
{
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}
	if ( (*start).type() != Token::Type::TYPE && (*start++).content() != RESERVED_WORD_OBJECT ) {
		return false;
	}
	if ( (*start).isOptional() && (*start++).type() != Token::Type::LANGUAGEFEATURE ) {
		return false;
	}
	if ( (*start++).type() != Token::Type::IDENTIFER ) {
		return false;
	}

	return true;
}

// syntax:
// <visibility> prototype [language feature] <identifier> [extends <identifier> [, <identifier>, ...]]
bool Analyser::isPrototypeDeclaration(TokenIterator start)
{
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}
	if ( (*start).type() != Token::Type::TYPE && (*start++).content() != "prototype" ) {
		return false;
	}
	if ( (*start).isOptional() && (*start++).type() != Token::Type::LANGUAGEFEATURE ) {
		return false;
	}
	if ( (*start++).type() != Token::Type::IDENTIFER ) {
		return false;
	}

	return true;
}

void Analyser::process(const std::string& filename)
{
	// factory reset
	mFilename = filename;
	mBluePrints.clear();
	mInterfaces.clear();
	mLibraries.clear();
	mPrototypes.clear();

	OSinfo("Analyzing file '" + mFilename + "'...");

	if ( !::Utils::Tools::Files::exists(mFilename) ) {
		throw Utils::Exceptions::Exception(mFilename + " file not found");
	}

	// read file content
	std::ifstream in(mFilename.c_str(), std::ios_base::binary);

	// create token list from file content
	TokenList tokens = generateTokens(std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()));

	SanityChecker sanity;
	sanity.process(tokens);

	// generate objects from tokens
	generate(tokens);
}


}
