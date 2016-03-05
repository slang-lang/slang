
// Header
#include "Analyser.h"

// Library includes
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

// Project includes
#include <Core/Consts.h>
#include <Core/Designtime/SanityChecker.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Tools/Files.h>
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

Designtime::Ancestors Analyser::collectInheritance(TokenIterator &start) const
{
	Designtime::Ancestors ancestors;

	if ( start->type() != Token::Type::RESERVED_WORD ) {
		// no reserved word, no ancestors
		return ancestors;
	}

	bool replicates = false;
	Designtime::Ancestor::Type::E type = Designtime::Ancestor::Type::Unknown;
	Visibility::E visibility = Visibility::Public;

	for ( ; ; ) {
		if ( start->content() == RESERVED_WORD_EXTENDS ) {
			if ( replicates ) {
				throw Utils::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			start++;	// consume token

			type = Designtime::Ancestor::Type::Extends;
		}
		else if ( start->content() == RESERVED_WORD_IMPLEMENTS ) {
			if ( replicates ) {
				throw Utils::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			start++;	// consume token

			type = Designtime::Ancestor::Type::Implements;
		}
		else if ( start->content() == RESERVED_WORD_REPLICATES ) {
			start++;	// consume token

			replicates = true;
			type = Designtime::Ancestor::Type::Replicates;
		}
		else if ( start->type() == Token::Type::COLON ) {
			start++;	// consume token

			continue;
		}

		if ( start->type() != Token::Type::IDENTIFER ) {
			break;
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
		fullyQualifiedTypename = mScopeName + RESERVED_WORD_SCOPE_OPERATOR;
	}
	fullyQualifiedTypename += name;

	// collect inheritance (if present)
	Designtime::Ancestors inheritance = collectInheritance(++start);

	bool isReplication = false;
	if ( !inheritance.empty() ) {
		isReplication = (inheritance.begin()->type() == Designtime::Ancestor::Type::Replicates);
	}

	TokenList tokens;

	if ( !isReplication ) {	// only collect all tokens of this object if it's not a replication
		// object or interface declarations have to start with an '{' token
		expect(Token::Type::BRACKET_CURLY_OPEN, start);

		// look for the next opening curly brackets
		TokenIterator open = start;
		// look for balanced curly brackets
		TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

		for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
			tokens.push_back((*it));
		}

		start = closed;
	}

	Designtime::SanityChecker sanity;
	sanity.process(tokens);

	Designtime::BluePrint blue(name, mFilename);
	blue.setFullyQualifiedTypename(fullyQualifiedTypename);
	blue.setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	blue.setTokens(tokens);
	blue.setVisibility(Visibility::convert(visibility));

	// set up inheritance (if present)
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

	Designtime::SanityChecker sanity;
	sanity.process(tokens);

	if ( !mScopeName.empty() ) {
		mScopeName += RESERVED_WORD_SCOPE_OPERATOR;
	}
	mScopeName += name;

	generate(tokens);

	start = closed;
}

Designtime::Prototype Analyser::createPrototype(TokenIterator& start, TokenIterator end)
{
	return Designtime::Prototype(createBluePrint(start, end));
}

void Analyser::generate(const TokenList& tokens)
{
	TokenList::const_iterator it = tokens.begin();

	// loop over all tokens and look for imports and object declarations
	while ( it != tokens.end() && it->type() != Token::Type::ENDOFFILE ) {
		if ( isInterfaceDeclaration(it) ) {
			Designtime::BluePrint i = createBluePrint(it, tokens.end());
			mBluePrints.push_back(i);
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
			Designtime::Prototype p = createPrototype(it, tokens.end());
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

const StringList& Analyser::getLibraryReferences() const
{
	return mLibraries;
}

const Designtime::PrototypeList& Analyser::getPrototypes() const
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

/*
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::TYPE, std::string(RESERVED_WORD_INTERFACE)));
	tokens.push_back(Token(Token::Type::LANGUAGEFEATURE, true));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSynthax(start, tokens);
*/
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
	mLibraries.clear();
	mPrototypes.clear();

	OSinfo("Processing string data...");

	// create token list from string
	TokenList tokens = generateTokens(content);

	// execute basic sanity checks
	Designtime::SanityChecker sanity;
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
