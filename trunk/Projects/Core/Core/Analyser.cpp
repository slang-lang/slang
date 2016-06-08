
// Header
#include "Analyser.h"

// Library includes
#include <cstdlib>
#include <fstream>
#include <iostream>

// Project includes
#include <Core/Designtime/SanityChecker.h>
#include <Core/Parser/Parser.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Tools/Files.h>
#include "Repository.h"
#include "Tokenizer.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Analyser::Analyser(Repository *repository)
: mRepository(repository)
{
	mScope = mRepository->getGlobalScope();
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

Designtime::BluePrint Analyser::createBluePrint(TokenIterator& start, TokenIterator end, bool isInterface) const
{
	std::string fullyQualifiedName;
	bool isAbstract = false;
	std::string languageFeature;
	std::string name;
	std::string visibility;

	// look for the visibility token
	visibility = (*start++).content();
	// look for an optional language feature token
	if ( start->isOptional() ) {
		languageFeature = (*start++).content();
	}
	// look for the object token
	(*start++).content();
	// look for the identifier token
	name = (*start).content();

	if ( !mScopeName.empty() ) {
		fullyQualifiedName = mScopeName + RESERVED_WORD_SCOPE_OPERATOR;
	}
	fullyQualifiedName += name;

	// collect inheritance (if present)
	Designtime::Ancestors inheritance = collectInheritance(++start);

	bool isImplemented = true;
	if ( !inheritance.empty() ) {
		isImplemented = (inheritance.begin()->type() != Designtime::Ancestor::Type::Replicates);
	}

	if ( isImplemented ) {
		isImplemented = (start->type() != Token::Type::SEMICOLON);
	}

	TokenList tokens;

	if ( isImplemented ) {	// only collect all tokens of this object if it is implemented
		// interface, object or prototype declarations have to start with an '{' token
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

	Designtime::BluePrint blue(name, mFilename);
	blue.setAbstract(isAbstract || isInterface);
	blue.setFullyQualifiedTypename(fullyQualifiedName);
	blue.setInterface(isInterface);
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

std::string Analyser::createLibraryReference(TokenIterator& start, TokenIterator end) const
{
	std::string reference;

	expect(Token::Type::RESERVED_WORD, start++);

	while ( start->type() == Token::Type::IDENTIFER && start != end ) {
		reference += (*start++).content();

		if ( start->type() != Token::Type::SCOPE ) {
			break;
		}

		reference += ".";
		start++;
	}

	expect(Token::Type::SEMICOLON, start);

	return reference;
}

void Analyser::createMember(TokenIterator& start, TokenIterator /*end*/)
{
	std::string fullyQualifiedName;
	bool isFinal = false;
	std::string languageFeature;
	Mutability::E mutability = Mutability::Modify;
	std::string name;
	std::string type;
	std::string visibility;

	// look for the visibility token
	visibility = (*start++).content();
	// look for an optional language feature token
	if ( start->isOptional() ) {
		languageFeature = (*start++).content();
	}
	// look for the type token
	type = (*start++).content();
	// look for the identifier token
	name = (*start++).content();

	if ( !mScopeName.empty() ) {
		fullyQualifiedName = mScopeName + RESERVED_WORD_SCOPE_OPERATOR;
	}
	fullyQualifiedName += name;

	if ( (*start).type() != Token::Type::SEMICOLON ) {
		throw Utils::Exceptions::Exception("initialization not allowed during declaration", start->position());
	}

	Runtime::Object *member = mRepository->createInstance(type, name);
	member->setFinal(isFinal);
	member->setMember(false);
	member->setMutability(mutability);
	member->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	member->setParent(mScope);
	member->setRepository(mRepository);
	member->setVisibility(Visibility::convert(visibility));

	mScope->define(name, member);
}

void Analyser::createMethod(TokenIterator &start, TokenIterator end)
{
	bool isAbstract = false;
	bool isFinal = false;
	bool isRecursive = false;
	std::string languageFeature;
	MethodAttributes::MethodType::E methodType = MethodAttributes::MethodType::Function;
	Mutability::E mutability = Mutability::Const;
	std::string name;
	std::string type;
	std::string visibility;

	// look for the visibility token
	visibility = (*start++).content();
	// look for an optional language feature token
	if ( start->isOptional() ) {
		languageFeature = (*start++).content();
	}
	// look for the type token
	type = (*start++).content();
	// look for the identifier token
	name = (*start++).content();

	// look for the next opening parenthesis
	if ( (*start).type() != Token::Type::PARENTHESIS_OPEN ) {
		throw Utils::Exceptions::SyntaxError("parameter declaration expected");
	}

	ParameterList params = Parser::parseParameters(start);

	// look for the next opening curly brackets
	TokenIterator open = findNext(start, Token::Type::BRACKET_CURLY_OPEN);
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

	// collect all tokens of this object
	TokenList tokens;
	for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
		tokens.push_back((*it));
	}

	// create a new method with the corresponding return value
	Runtime::Method *method = new Runtime::Method(mScope, name, type);
	method->setAbstract(isAbstract);
	method->setFinal(isFinal);
	method->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	method->setMethodType(methodType);
	method->setMutability(mutability);
	method->setParent(mScope);
	method->setRecursive(isRecursive);
	method->setRepository(mRepository);
	method->setSignature(params);
	method->setTokens(tokens);
	method->setVisibility(Visibility::convert(visibility));

	mScope->defineMethod(name, method);

	start = closed;
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

	if ( !mScopeName.empty() ) {
		mScopeName += RESERVED_WORD_SCOPE_OPERATOR;
	}
	mScopeName += name;

	generate(tokens);

	start = closed;
}

Designtime::Prototype Analyser::createPrototype(TokenIterator& start, TokenIterator end) const
{
	return Designtime::Prototype(createBluePrint(start, end));
}

void Analyser::generate(const TokenList& tokens)
{
	TokenList::const_iterator it = tokens.begin();

	// loop over all tokens and look for imports and object declarations
	while ( it != tokens.end() && it->type() != Token::Type::ENDOFFILE ) {
		if ( Parser::isInterfaceDeclaration(it) ) {
			Designtime::BluePrint i = createBluePrint(it, tokens.end(), true);
			mBluePrints.push_back(i);
		}
		else if ( Parser::isLibraryReference(it) ) {
			std::string reference = createLibraryReference(it, tokens.end());
			mLibraries.push_back(reference);
		}
		else if ( Parser::isMemberDeclaration(it) ) {
			createMember(it, tokens.end());
		}
		else if ( Parser::isMethodDeclaration(it) ) {
			createMethod(it, tokens.end());
		}
		else if ( Parser::isNamespaceDeclaration(it) ) {
			createNamespace(it, tokens.end());
		}
		else if ( Parser::isObjectDeclaration(it) ) {
			Designtime::BluePrint o = createBluePrint(it, tokens.end());
			mBluePrints.push_back(o);
		}
		else if ( Parser::isPrototypeDeclaration(it) ) {
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

void Analyser::process(const TokenList& tokens)
{
	// factory reset
	mBluePrints.clear();
	mLibraries.clear();
	mPrototypes.clear();

	OSdebug("Processing string data...");

	// execute basic sanity checks
	Designtime::SanityChecker sanity;
	sanity.process(tokens);

	// generate objects from tokens
	generate(tokens);
}

void Analyser::processFile(const std::string& filename)
{
	OSdebug("Preparing file '" + filename + "'...");

	mFilename = filename;

	if ( !::Utils::Tools::Files::exists(mFilename) ) {
		throw Utils::Exceptions::Exception("File '" + mFilename + "' not found");
	}

	// read file content
	std::ifstream in(mFilename.c_str(), std::ios_base::binary);

	// create token list from string
	TokenList tokens = generateTokens(std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()));

	// start the real processing
	process(tokens);
}

void Analyser::processString(const std::string& content, const std::string& filename)
{
	OSdebug("Preparing string data...");

	mFilename = filename;

	// create token list from string
	TokenList tokens = generateTokens(content);

	// start the real processing
	process(tokens);
}

void Analyser::processTokens(const TokenList& tokens)
{
	OSdebug("Preparing token data...");

	// start the real processing
	process(tokens);
}


}
