
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


Analyser::Analyser()
{
}

Analyser::~Analyser()
{
}

Designtime::Ancestors Analyser::collectInheritance(TokenIterator &start, TokenIterator end) const
{
	Designtime::Ancestors ancestors;

	Designtime::Ancestor::Type::E type = Designtime::Ancestor::Type::Unknown;
	Visibility::E visibility = Visibility::Public;

	while ( start != end ) {
		if ( start->content() == RESERVED_WORD_EXTENDS ) {
			// consume token
			start++;

			type = Designtime::Ancestor::Type::Extends;
		}
		else if ( start->content() == RESERVED_WORD_IMPLEMENTS ) {
			// consume token
			start++;

			type = Designtime::Ancestor::Type::Implements;
		}
		else if ( start->type() == Token::Type::COLON ) {
			// consume token
			start++;

			continue;
		}

		if ( start->type() != Token::Type::IDENTIFER ) {
			throw Utils::Exceptions::Exception("invalid token found: '" + start->content() + "'", start->position());
		}

		ancestors.insert(Designtime::Ancestor((start++)->content(), type, visibility));
	}

	return ancestors;
}

TokenList Analyser::collectScopeTokens(TokenIterator& token) const
{
	if ( (*token).type() != Token::Type::BRACKET_CURLY_OPEN ) {
		throw Utils::Exceptions::Exception("collectScopeTokens: invalid start token found");
	}

	int scope = 0;
	TokenList tokens;

	// look for the corresponding closing curly bracket
	while ( (*++token).type() != Token::Type::BRACKET_CURLY_CLOSE || scope > 0 ) {
		if ( (*token).type() == Token::Type::BRACKET_CURLY_OPEN ) {
			scope++;
		}
		if ( (*token).type() == Token::Type::BRACKET_CURLY_CLOSE ) {
			scope--;
		}

		tokens.push_back((*token));
	}

	return tokens;
}

Designtime::BluePrint Analyser::createBluePrint(TokenIterator& start, TokenIterator end)
{
	std::string fullyQualifiedTypename;
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

	if ( !mScopeName.empty() ) {
		fullyQualifiedTypename = mScopeName + RESERVED_WORD_SCOPE_OPERATOR + name;
	}
	else {
		fullyQualifiedTypename = name;
	}

	// look for the next opening curly brackets
	TokenIterator open = findNext(++start, Token::Type::BRACKET_CURLY_OPEN);
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

	// check if we have some more tokens before our object declarations starts
	Designtime::Ancestors inheritance = collectInheritance(start, open);

	// collect all tokens of this object
	TokenList tokens;

	for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
		tokens.push_back((*it));
	}

	start = closed;

	SanityChecker sanity;
	sanity.process(tokens);

	Designtime::BluePrint blue(name, mFilename);
	blue.setFullyQualifiedTypename(fullyQualifiedTypename);
	blue.setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	blue.setTokens(tokens);
	blue.setVisibility(Visibility::convert(visibility));

	// set up inheritances (if present)
	if ( !inheritance.empty() ) {
		for ( Designtime::Ancestors::const_iterator it = inheritance.begin(); it != inheritance.end(); ++it ) {
			blue.addInheritance((*it));
		}
	}

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
	std::string fullyQualifiedName;
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

	if ( !mScopeName.empty() ) {
		fullyQualifiedName = mScopeName + RESERVED_WORD_SCOPE_OPERATOR + name;
	}

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

	Interface interface(name, mFilename);
	//interface.setFullyQualifiedName(fullyQualifiedName);
	interface.setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	interface.setTokens(tokens);

	return interface;
}

void Analyser::createNamespace(TokenIterator& start, TokenIterator end)
{
	std::string languageFeature;
	std::string name;
	std::string visibility;
	bool isSealed = false;

	// look for the visibility token
	visibility = (*start++).content();
	// look for the object token
	(*start++).content();
	// look for an optional language feature token
	if ( start->isOptional() ) {
		languageFeature = (*start++).content();
	}
	// look for the identifier token
	name = (*start++).content();

	if ( (*start).content() == MODIFIER_SEALED ) {
		isSealed = true;
	}

	// look for the next opening curly brackets
	TokenIterator open = findNext(start, Token::Type::BRACKET_CURLY_OPEN);
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

	// collect all tokens of this object
	TokenList tokens;
	for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
		tokens.push_back((*it));
	}

	SanityChecker sanity;
	sanity.process(tokens);

	if ( !mScopeName.empty() ) {
		mScopeName += RESERVED_WORD_SCOPE_OPERATOR;
	}
	mScopeName += name;

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
			Designtime::BluePrint o = createBluePrint(it, tokens.end());
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

const Designtime::BluePrintList& Analyser::getBluePrints() const
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
// <visibility> interface [language feature] <identifier> { ... }
bool Analyser::isInterfaceDeclaration(TokenIterator start)
{
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}
	if ( (*start).type() != Token::Type::TYPE && (*start++).content() != RESERVED_WORD_INTERFACE ) {
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

	if ( (*start++).content() != RESERVED_WORD_IMPORT ) {
		return false;
	}

	tokens.push_back(Token(Token::Type::IDENTIFER));
	tokens.push_back(Token(Token::Type::SEMICOLON));

	return checkSynthax(start, tokens);
}

// syntax:
// <visibility> namespace [language feature] <identifier> { ... }
bool Analyser::isNamespaceDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::TYPE, std::string(RESERVED_WORD_NAMESPACE)));
	tokens.push_back(Token(Token::Type::LANGUAGEFEATURE, true));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSynthax(start, tokens);
}

// syntax:
// <visibility> object [language feature] <identifier> [extends <identifier> [implements <identifier>, ...]] { ... }
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
// <visibility> prototype [language feature] <identifier> [extends <identifier> [implements <identifier>, ...]] { ... }
bool Analyser::isPrototypeDeclaration(TokenIterator start)
{
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}
	if ( (*start).type() != Token::Type::TYPE && (*start++).content() != RESERVED_WORD_PROTOTYPE ) {
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

void Analyser::process(const std::string& content)
{
	// factory reset
	mBluePrints.clear();
	mInterfaces.clear();
	mLibraries.clear();
	mPrototypes.clear();

	OSinfo("Analyzing string...");

	// create token list from string
	TokenList tokens = generateTokens(content);

	// execute basic sanity checks
	SanityChecker sanity;
	sanity.process(tokens);

	// generate objects from tokens
	generate(tokens);
}

void Analyser::processFile(const std::string& filename)
{
	OSinfo("Preparing file '" + filename + "'...");

	mFilename = filename;

	if ( !::Utils::Tools::Files::exists(mFilename) ) {
		throw Utils::Exceptions::Exception("File '" + mFilename + "' not found");
	}

	// read file content
	std::ifstream in(mFilename.c_str(), std::ios_base::binary);

	process(std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()));
}

void Analyser::processString(const std::string& content, const std::string& filename)
{
	OSinfo("Preparing string data...");

	mFilename = filename;

	process(content);
}


}
