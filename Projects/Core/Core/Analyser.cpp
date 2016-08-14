
// Header
#include "Analyser.h"

// Library includes
#include <cstdlib>
#include <fstream>
#include <iostream>

// Project includes
#include <Core/Designtime/SanityChecker.h>
#include <Core/Parser/Parser.h>
#include <Core/Runtime/Namespace.h>
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

Designtime::Ancestors Analyser::collectInheritance(TokenIterator& token) const
{
	Designtime::Ancestors ancestors;

	if ( token->type() != Token::Type::RESERVED_WORD ) {
		// no reserved word, no ancestors
		return ancestors;
	}

	bool replicates = false;
	Designtime::Ancestor::Type::E inheritance = Designtime::Ancestor::Type::Unknown;
	Visibility::E visibility = Visibility::Public;

	for ( ; ; ) {
		if ( token->content() == RESERVED_WORD_EXTENDS ) {
			if ( replicates ) {
				throw Utils::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			token++;	// consume token

			inheritance = Designtime::Ancestor::Type::Extends;
		}
		else if ( token->content() == RESERVED_WORD_IMPLEMENTS ) {
			if ( replicates ) {
				throw Utils::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			token++;	// consume token

			inheritance = Designtime::Ancestor::Type::Implements;
		}
		else if ( token->content() == RESERVED_WORD_REPLICATES ) {
			if ( replicates ) {
				throw Utils::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			token++;	// consume token

			replicates = true;
			inheritance = Designtime::Ancestor::Type::Replicates;
		}
		else if ( token->type() == Token::Type::COMMA ) {
			token++;	// consume token

			continue;
		}

		if ( token->type() != Token::Type::IDENTIFER ) {
			break;
		}

		//std::string type = identify(token, TokenIterator());

		ancestors.insert(
			Designtime::Ancestor(getQualifiedTypename((token++)->content()), inheritance, visibility)
			//Designtime::Ancestor(type, inheritance, visibility)
		);

		//token++;
	}

	return ancestors;
}

bool Analyser::createBluePrint(TokenIterator& token, TokenIterator end, bool isInterface) const
{
	bool isAbstract = false;
	std::string languageFeature;
	std::string type;
	std::string visibility;

	// look for the visibility token
	visibility = (*token++).content();
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the object token
	(*token++).content();
	// look for the identifier token
	type = (*token).content();

	// collect inheritance (if present)
	Designtime::Ancestors inheritance = collectInheritance(++token);

	bool isImplemented = true;
	if ( !inheritance.empty() ) {
		isImplemented = (inheritance.begin()->type() != Designtime::Ancestor::Type::Replicates);
	}

	if ( isImplemented ) {
		isImplemented = (token->type() != Token::Type::SEMICOLON);
	}

	TokenList tokens;

	if ( isImplemented ) {	// only collect all tokens of this object if it is implemented
		// interface, object or prototype declarations have to start with an '{' token
		expect(Token::Type::BRACKET_CURLY_OPEN, token);

		// look for the next opening curly brackets
		TokenIterator open = token;
		// look for balanced curly brackets
		TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

		for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
			tokens.push_back((*it));
		}

		token = closed;
	}

	Designtime::BluePrintObject* symbol = new Designtime::BluePrintObject(type, mFilename);
	symbol->setAbstract(isAbstract || isInterface);
	symbol->setInterface(isInterface);
	symbol->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	symbol->setParent(mScope);
	symbol->setQualifiedTypename(getQualifiedTypename(type));
	symbol->setTokens(tokens);
	symbol->setVisibility(Visibility::convert(visibility));

	// set up inheritance (if present)
	if ( !inheritance.empty() ) {
		for ( Designtime::Ancestors::const_iterator it = inheritance.begin(); it != inheritance.end(); ++it ) {
			symbol->addInheritance((*it));
		}
	}

	mRepository->addBluePrint(symbol);

	return true;
}

bool Analyser::createEnum(TokenIterator& token, TokenIterator end) const
{
	std::string languageFeature;
	std::string type;
	std::string visibility;

	// look for the visibility token
	visibility = (*token++).content();
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the object token
	(*token++).content();
	// look for the identifier token
	type = (*token++).content();

	// interface, object or prototype declarations have to start with an '{' token
	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	// look for the next opening curly brackets
	TokenIterator open = token;
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

	TokenList tokens;
	for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
		tokens.push_back((*it));
	}

	token = closed;

	Designtime::BluePrintEnum* symbol = new Designtime::BluePrintEnum(type, mFilename);
	symbol->setFinal(true);
	symbol->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	symbol->setMutability(Mutability::Modify);
	symbol->setParent(mScope);
	symbol->setQualifiedTypename(getQualifiedTypename(type));
	symbol->setTokens(tokens);
	symbol->setVisibility(Visibility::convert(visibility));
	symbol->setSealed(true);

	mRepository->addBluePrint(symbol);

	return symbol;
}

std::string Analyser::createLibraryReference(TokenIterator& token, TokenIterator end) const
{
	std::string reference;

	expect(Token::Type::RESERVED_WORD, token++);

	while ( token->type() == Token::Type::IDENTIFER && token != end ) {
		reference += (*token++).content();

		if ( token->type() != Token::Type::SCOPE ) {
			break;
		}

		reference += ".";
		token++;
	}

	expect(Token::Type::SEMICOLON, token);

	return reference;
}

bool Analyser::createMember(TokenIterator& token, TokenIterator /*end*/)
{
	std::string languageFeature;
	Mutability::E mutability = Mutability::Modify;
	std::string name;
	std::string type;
	Runtime::AtomicValue value = 0;
	Visibility::E visibility;

	// look for the visibility token
	visibility = Visibility::convert((*token++).content());
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the type token
	type = (*token++).content();
	// look for the identifier token
	name = (*token++).content();

	// look for a mutability keyword
	if ( token->category() == Token::Category::Modifier ) {
		mutability = Mutability::convert(token->content());
		token++;
	}

	if ( token->type() == Token::Type::ASSIGN ) {
		token++;

		switch ( token->type() ) {
			case Token::Type::CONST_BOOLEAN: value = Tools::stringToBool(token->content()); break;
			case Token::Type::CONST_DOUBLE: value = Tools::stringToDouble(token->content()); break;
			case Token::Type::CONST_FLOAT: value = Tools::stringToFloat(token->content()); break;
			case Token::Type::CONST_INTEGER: value = Tools::stringToInt(token->content()); break;
			case Token::Type::CONST_LITERAL: value = token->content(); break;
			case Token::Type::CONST_NUMBER: value = Tools::stringToNumber(token->content()); break;
			default: throw Utils::Exceptions::NotSupported("initialization is only allowed for atomic data types", token->position());
		}

		token++;
	}

	expect(Token::Type::SEMICOLON, token);

	Runtime::Object *member = mRepository->createInstance(type, name);
	member->setMember(false);
	member->setMutability(mutability);
	member->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	member->setParent(mScope);
	member->setQualifiedTypename(type);
	member->setRepository(mRepository);
	member->setValue(value);
	member->setVisibility(visibility);

	mScope->define(name, member);

	return true;
}

bool Analyser::createMethod(TokenIterator& token, TokenIterator end)
{
	bool isAbstract = false;
	bool isRecursive = false;
	std::string languageFeature;
	MethodAttributes::MethodType::E methodType = MethodAttributes::MethodType::Function;
	Mutability::E mutability = Mutability::Const;
	std::string name;
	std::string type;
	std::string visibility;

	// look for the visibility token
	visibility = (*token++).content();
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the type token
	type = (*token++).content();
	// look for the identifier token
	name = (*token++).content();

	expect(Token::Type::PARENTHESIS_OPEN, token);

	ParameterList params = Parser::parseParameters(token);

	// look for the next opening curly brackets
	TokenIterator open = findNext(token, Token::Type::BRACKET_CURLY_OPEN);
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

	// collect all tokens of this object
	TokenList tokens;
	for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
		tokens.push_back((*it));
	}

	token = closed;

	// create a new method with the corresponding return value
	Runtime::Method *method = new Runtime::Method(mScope, name, type);
	method->setAbstract(isAbstract);
	method->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	method->setMethodType(methodType);
	method->setMutability(mutability);
	method->setParent(mScope);
	method->setQualifiedTypename(type);
	method->setRecursive(isRecursive);
	method->setRepository(mRepository);
	method->setSignature(params);
	method->setTokens(tokens);
	method->setVisibility(Visibility::convert(visibility));

	mScope->defineMethod(name, method);

	return true;
}

bool Analyser::createNamespace(TokenIterator& token, TokenIterator end)
{
	std::string languageFeature;
	std::string name;
	std::string visibility;

	// look for the visibility token
	visibility = (*token++).content();
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the "namespace" token
	expect(Token::Type::RESERVED_WORD, token++);

	MethodScope* tmpScope = mScope;

	while ( token->type() == Token::Type::IDENTIFER ) {
		// look for the identifier token
		name = (*token++).content();

		if ( token->type() == Token::Type::SCOPE ) {
			token++;
		}

		Runtime::Namespace* space = 0;

		// check for an existing namespace with this name
		Symbol* symbol = mScope->resolve(name, true);
		if ( !symbol ) {
			space = new Runtime::Namespace(name, mScope);
			space->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
			space->setQualifiedTypename(getQualifiedTypename(name));
			space->setVisibility(Visibility::convert(visibility));
			space->setSealed(space->getVisibility() == Visibility::Private);		// seal has to be the last attribute to be set

			mScope->define(name, space);
		}
		else {
			switch ( symbol->getSymbolType() ) {
				case Symbol::IType::NamespaceSymbol:
					space = static_cast<Runtime::Namespace*>(symbol);
					break;
				case Symbol::IType::BluePrintEnumSymbol:
				case Symbol::IType::BluePrintObjectSymbol:
				case Symbol::IType::MethodSymbol:
				case Symbol::IType::ObjectSymbol:
				case Symbol::IType::UnknownSymbol:
					throw Utils::Exceptions::Exception("cannot extend non-namespace symbol '" + symbol->getName() + "'");
			}
		}

		mScope = space;
	}

	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	TokenIterator open = token;
	// look for balanced curly brackets
	TokenIterator closed = findNextBalancedCurlyBracket(open, end, 0, Token::Type::BRACKET_CURLY_CLOSE);

	// collect all tokens of this object
	TokenList tokens;
	for ( TokenIterator it = ++open; it != closed && it != end; ++it ) {
		tokens.push_back((*it));
	}

	generate(tokens);

	mScope = tmpScope;

	token = closed;

	return true;
}

bool Analyser::createPrototype(TokenIterator& start, TokenIterator end) const
{
assert(!"prototypes not supported!");

(void)end;
(void)start;

	return false;
}

/*
 * loop over all tokens and look for imports and object declarations
 */
void Analyser::generate(const TokenList& tokens)
{
	TokenList::const_iterator it = tokens.begin();

	while ( it != tokens.end() && it->type() != Token::Type::ENDOFFILE ) {
		if ( Parser::isInterfaceDeclaration(it) ) {
			createBluePrint(it, tokens.end(), true);
		}
		else if ( Parser::isEnumDeclaration(it) ) {
			createEnum(it, tokens.end());
		}
		else if ( Parser::isLibraryReference(it) ) {
			std::string reference = createLibraryReference(it, tokens.end());
			mLibraries.push_back(reference);
		}
		else if ( Parser::isMemberDeclaration(it) || Parser::isMemberDeclarationWithModifier(it) ) {
			createMember(it, tokens.end());
		}
		else if ( Parser::isMethodDeclaration(it) ) {
			createMethod(it, tokens.end());
		}
		else if ( Parser::isNamespaceDeclaration(it) ) {
			createNamespace(it, tokens.end());
		}
		else if ( Parser::isObjectDeclaration(it) ) {
			createBluePrint(it, tokens.end());
		}
		else if ( Parser::isPrototypeDeclaration(it) ) {
			createPrototype(it, tokens.end());
		}
		else {
			throw Utils::Exceptions::SyntaxError("invalid token '" + it->content() + "' found", it->position());
		};

		it++;
	}
}

TokenList Analyser::generateTokens(const std::string& content)
{
	Tokenizer t(mFilename, content);
	t.process();

	return t.tokens();
}

const StringList& Analyser::getLibraryReferences() const
{
	return mLibraries;
}

std::string Analyser::getQualifiedTypename(const std::string& type) const
{
	std::string result = mScope->getFullScopeName();

	if ( !result.empty() && !type.empty() ) {
		result += RESERVED_WORD_SCOPE_OPERATOR;
	}
	result += type;

	return result;
}

std::string Analyser::identify(TokenIterator& start, TokenIterator /*end*/) const
{
	std::string type = start->content();

	while ( start->type() == Token::Type::IDENTIFER ) {
		if ( lookahead(start++)->type() != Token::Type::SCOPE ) {
			break;
		}

		// add next token to type definition
		type += (start++)->content();
		type += (start++)->content();
	}

	return type;
}

void Analyser::process(const TokenList& tokens)
{
	// factory reset
	mLibraries.clear();

	OSdebug("Processing tokens...");

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
//	OSdebug("Preparing string data...");

	mFilename = filename;

	// create token list from string
	TokenList tokens = generateTokens(content);

	// start the real processing
	process(tokens);
}

void Analyser::processTokens(const TokenList& tokens)
{
//	OSdebug("Preparing token data...");

	// start the real processing
	process(tokens);
}


}
