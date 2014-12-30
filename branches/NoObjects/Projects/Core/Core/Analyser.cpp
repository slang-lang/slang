
// Header
#include "Analyser.h"

// Library includes
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

// Project includes
#include <Core/Utils/Exceptions.h>
#include "Tokenizer.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


std::string Analyser::createLibraryReference(TokenIterator& start)
{
	std::string reference;

	start++;

	while ( start->type() != Token::Type::SEMICOLON && start != mTokens.end() ) {
		reference += (*start++).content();
	}

	return reference;
}

BluePrint Analyser::createObject(TokenIterator& start)
{
	std::string name;
	std::string visibility;

	// look for the visibility token
	visibility = (*start++).content();
	// look for the object token
	(*start++).content();
	// look for the identifier token
	name = (*start).content();

	// look for the next opening curly brackets
	TokenIterator open = findNext(++start, Token::Type::BRACKET_CURLY_OPEN);
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, 0, Token::Type::BRACKET_CURLY_CLOSE);

	BluePrint::Ancestors parents;

	// check if we have some more tokens before our object declarations starts
	if ( start != open ) {
		if ( start->content() != "extends" ) {
			throw Exception("invalid token '" + start->content() + "' during object declaration");
		}

		// collect inheritences
		start++;

		do {
			std::string inheritance = (*start++).content();
			std::string ancestor = (*start++).content();

			parents[ancestor] = BluePrint::Ancestor(ancestor, Visibility::convert(inheritance));
		} while ( std::distance(start, open) > 0 && ++start != mTokens.end() );
	}

	// collect all tokens of this object
	TokenList tokens;

	for ( TokenIterator it = ++open; it != closed; ++it ) {
		tokens.push_back((*it));
	}

	start = closed;

	BluePrint blue(name, mFilename);
	blue.setAncestors(parents);
	blue.setAncestorVisibility(Visibility::convert(visibility));
	blue.setTokens(tokens);

	return blue;
}

Prototype Analyser::createPrototype(TokenIterator& start)
{
	BluePrint blue = createObject(start);

	Prototype p(blue);
	return p;
}

void Analyser::generateObjects()
{
	TokenList::const_iterator it = mTokens.begin();

	// loop over all tokens and look for imports and object declarations
	while ( it != mTokens.end() && it->type() != Token::Type::ENDOFFILE ) {
		if ( isLibraryReference(it) ) {
			std::string reference = createLibraryReference(it);
			mLibraries.push_back(reference);
		}
		else if ( isObjectDeclaration(it) ) {
			BluePrint o = createObject(it);
			mObjects.push_back(o);
		}
		else if ( isPrototypeDeclaration(it) ) {
			Prototype p = createPrototype(it);
			mPrototypes.push_back(p);
		}
/*
		else {
			os_error("syntax error: looks like a library, object or prototype declaration but is none");
			return;
		}
*/

		it++;
	}
}

void Analyser::generateTokens(const std::string& content)
{
	Tokenizer t(content);
	t.process();

	mTokens = t.tokens();
}

const std::list<std::string>& Analyser::getLibraryReferences() const
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
// <visibility> object <identifier> [extends <indentifier> [, <identifier>, ...]]
bool Analyser::isObjectDeclaration(TokenIterator start)
{
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}
	if ( (*start).type() != Token::Type::TYPE && (*start++).content() != "object" ) {
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
	mTokens.clear();

	OSdebug("process('" + mFilename + "')");

	// read file content
	std::ifstream in(mFilename.c_str(), std::ios_base::binary);
	in.exceptions(std::ios_base::badbit | std::ios_base::failbit | std::ios_base::eofbit);

	// create token list from file content
	generateTokens(std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()));

	// generate objects from tokens
	generateObjects();
}


}
