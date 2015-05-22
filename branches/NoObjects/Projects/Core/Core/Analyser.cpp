
// Header
#include "Analyser.h"

// Library includes
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Scope.h"
#include "Tokenizer.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Analyser::Analyser()
: mScope(0)
{
	mScope = new GlobalScope();
}

Analyser::~Analyser()
{
	while ( mScope ) {
		IScope *scope = mScope->getEnclosingScope();

		delete mScope;
		mScope = scope;
	}
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
(void)end;

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
	TokenIterator closed = findNextBalancedCurlyBracket(open, 0, Token::Type::BRACKET_CURLY_CLOSE);

	// check if we have some more tokens before our object declarations starts
	if ( start != open ) {
		throw Utils::Exception("invalid token '" + start->content() + "' during interface declaration");
	}

	// collect all tokens of this object
	TokenList tokens;

	for ( TokenIterator it = ++open; it != closed; ++it ) {
		tokens.push_back((*it));
	}

	start = closed;

	Interface inter(name, mFilename);
	inter.setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	inter.setTokens(tokens);

	return inter;
}

void Analyser::createNamespace(TokenIterator& start, TokenIterator end)
{
(void) end;

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

	mScope = new LocalScope(name, mScope);

	// look for the next opening curly brackets
	TokenIterator open = findNext(++start, Token::Type::BRACKET_CURLY_OPEN);
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, 0, Token::Type::BRACKET_CURLY_CLOSE);

	// collect all tokens of this object
	TokenList tokens;
	for ( TokenIterator it = ++open; it != closed; ++it ) {
		tokens.push_back((*it));
	}

	generateObjects(tokens);

	start = closed;
}

BluePrint Analyser::createObject(TokenIterator& start, TokenIterator end)
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
	TokenIterator closed = findNextBalancedCurlyBracket(open, 0, Token::Type::BRACKET_CURLY_CLOSE);

	BluePrint::Ancestors parents;

	// check if we have some more tokens before our object declarations starts
	if ( start != open ) {
		if ( start->content() == "extends" ) {
			// collect inheritences
			start++;

			do {
				std::string inheritance = (*start++).content();
				std::string ancestor = (*start++).content();

//				parents[ancestor] = BluePrint::Ancestor(ancestor, Visibility::convert(inheritance));
			} while ( std::distance(start, open) > 0 && ++start != end );
		}
		else if ( start->content() == "implements" ) {
			// collect inheritences
			start++;

			std::string inheritance = (*start++).content();
			parents[inheritance] = BluePrint::Ancestor(inheritance, Visibility::Public);
		}
		else {
			throw Utils::Exception("invalid token '" + start->content() + "' during object declaration");
		}
	}

	// collect all tokens of this object
	TokenList tokens;

	for ( TokenIterator it = ++open; it != closed; ++it ) {
		tokens.push_back((*it));
	}

	start = closed;

	BluePrint blue(name, mFilename);
	blue.setAncestors(parents);
	blue.setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	blue.setTokens(tokens);
	blue.setVisibility(Visibility::convert(visibility));

	return blue;
}

Prototype Analyser::createPrototype(TokenIterator& start, TokenIterator end)
{
	BluePrint blue = createObject(start, end);

	Prototype p(blue);
	return p;
}

void Analyser::generateObjects(const TokenList& tokens)
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
			BluePrint o = createObject(it, tokens.end());
			mObjects.push_back(o);
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
	Tokenizer t(content);
	t.process();

	return t.tokens();
}

const InterfaceList& Analyser::getInterfaces() const
{
	return mInterfaces;
}

const StringList& Analyser::getLibraryReferences() const
{
	return mLibraries;
}

const BluePrintList& Analyser::getObjects() const
{
	return mObjects;
}

const PrototypeList& Analyser::getPrototypes() const
{
	return mPrototypes;
}

// syntax:
// <visibility> interface <identifier> ;
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
// <visibility> namespace <identifier>
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
// <visibility> object <identifier> [extends <indentifier> [, <identifier>, ...]]
bool Analyser::isObjectDeclaration(TokenIterator start)
{
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}
	if ( (*start).type() != Token::Type::TYPE && (*start++).content() != "object" ) {
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
// <visibility> prototype <identifier> [extends <indentifier> [, <identifier>, ...]]
bool Analyser::isPrototypeDeclaration(TokenIterator start)
{
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}
	if ( (*start).type() != Token::Type::TYPE && (*start++).content() != "prototype" ) {
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
	mLibraries.clear();
	mObjects.clear();

	OSinfo("Analyzing file '" + mFilename + "'...");

	try {
		// read file content
		std::ifstream in(mFilename.c_str(), std::ios_base::binary);
		in.exceptions(std::ios_base::badbit | std::ios_base::failbit | std::ios_base::eofbit);

		// create token list from file content
		TokenList tokens = generateTokens(std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()));

		// generate objects from tokens
		generateObjects(tokens);
	}
	catch ( std::exception &e ) {
		throw Utils::Exception("file not found '" + filename + "'");
	}
}


}
