
// Header
#include "Analyser.h"

// Library includes
#include <cstdlib>
#include <fstream>
#include <iostream>

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/Namespace.h>
#include <Core/Tokenizer.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Files.h>
#include <Utils.h>
#include "Exceptions.h"
#include "SanityChecker.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


Analyser::Analyser()
: mProcessingInterface(false)
{
	mRepository = Controller::Instance().repository();
	mScope = Controller::Instance().stack()->globalScope();
}

Analyser::~Analyser()
{
}

bool Analyser::buildEnum(Designtime::BluePrintEnum* symbol, const TokenList& tokens)
{
	TokenIterator token = tokens.begin();

	Runtime::AtomicValue previous_value = (unsigned)-1;
	Runtime::AtomicValue value = (unsigned)-1;

	// Format: <identifier> = <value>[, or ;]
	while ( token != tokens.end() ) {
		std::string name;

		expect(Token::Type::IDENTIFER, token);
		name = (token++)->content();

		if ( token->type() == Token::Type::ASSIGN ) {
			expect(Token::Type::ASSIGN, token++);

			expect(Token::Type::CONST_INTEGER, token);
			value = (token++)->content();
		}
		else {
			value = value.toInt() + 1;
		}

		// verify declaration order (this also prevents duplicate values)
		if ( previous_value.toInt() >= value.toInt() ) {
			throw Common::Exceptions::Exception("enum values have to be defined in ascending order");
		}

		previous_value = value;

		// define enum entries as parent type
		//Runtime::Object* entry = mRepository->createInstance(mBluePrint->QualifiedTypename(), name, true);
		//entry->setConstructed(true);

		// define enum entries as integer type
		//Runtime::Object* entry = Controller::Instance().repository()->createInstance(Runtime::IntegerObject::TYPENAME, name, true);
		Runtime::Object* entry = new Runtime::IntegerObject(name, value.toInt());	// this prevents a double delete because all instances are freed by their surrounding scope
		entry->setMember(true);
		entry->setMutability(Mutability::Const);
		entry->setValue(value.toInt());
		entry->setVisibility(Visibility::Public);

		// define enum entries in current scope
		entry->setParent(symbol);
		symbol->define(name, entry);

		// define enum entries in parent scope
		//entry->setParent(symbol->getEnclosingScope());
		//symbol->getEnclosingScope()->define(name, entry);

		if ( token->type() == Token::Type::COMMA ) {
			token++;

			if ( lookahead(token) == tokens.end() ) {
				throw Common::Exceptions::Exception("new enum value expected but none found!", token->position());
			}
		}
		else if ( token->type() == Token::Type::SEMICOLON ) {
			return true;
		}
		else {
			throw Common::Exceptions::Exception("unexpected token '" + token->content() + "' found", token->position());
		}
	}

	throw Common::Exceptions::SyntaxError("invalid enum declaration", token->position());
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
				throw Common::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			token++;	// consume token

			inheritance = Designtime::Ancestor::Type::Extends;
		}
		else if ( token->content() == RESERVED_WORD_IMPLEMENTS ) {
			if ( replicates ) {
				throw Common::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			token++;	// consume token

			inheritance = Designtime::Ancestor::Type::Implements;
		}
		else if ( token->content() == RESERVED_WORD_REPLICATES ) {
			if ( replicates ) {
				throw Common::Exceptions::Exception("combinations with 'replicates' are not allowed");
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

bool Analyser::createBluePrint(TokenIterator& token, TokenIterator end)
{
	// look for the visibility token
	std::string visibility = (*token++).content();
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);
	// look for an optional modifier token
	ImplementationType::E implementationType = Parser::parseImplementationType(token, ImplementationType::FullyImplemented);
	// look for the object token
	ObjectType::E objectType = Parser::parseObjectType(token);
	// look for the identifier token
	std::string type = (*token++).content();

	Designtime::BluePrintObject* symbol = new Designtime::BluePrintObject(type, mFilename);

	// determine implementation type
	if ( objectType == ObjectType::Interface ) {
		if ( implementationType != ImplementationType::FullyImplemented ) {
			throw Common::Exceptions::NotSupported("interfaces cannot be defined abstract object");
		}

		implementationType = ImplementationType::Interface;
	}

	TokenList tokens;

	if ( token->type() == Token::Type::SEMICOLON ) {
		if ( implementationType != ImplementationType::FullyImplemented ) {
			throw Common::Exceptions::NotSupported("forward declarations cannot be defined as interface or abstract object");
		}

		implementationType = ImplementationType::ForwardDeclaration;
	}
	else {
		// collect inheritance (if present)
		Designtime::Ancestors inheritance = collectInheritance(token);

		bool isImplemented = true;
		if ( !inheritance.empty() ) {
			isImplemented = (inheritance.begin()->type() != Designtime::Ancestor::Type::Replicates);
		}

		if ( isImplemented ) {
			isImplemented = (token->type() != Token::Type::SEMICOLON);
		}

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

		symbol->setTokens(tokens);

		bool extends = false;

		// set up inheritance (if present)
		if ( !inheritance.empty() ) {
			for ( Designtime::Ancestors::const_iterator it = inheritance.begin(); it != inheritance.end(); ++it ) {
				if ( it->type() == Designtime::Ancestor::Type::Extends ) {
					extends = true;
				}

				symbol->addInheritance((*it));
			}
		}

		// in case this object has no inheritance set, we inherit from 'Object'
		if ( objectType != ObjectType::Interface && !extends ) {
			symbol->addInheritance(Designtime::Ancestor(OBJECT, Designtime::Ancestor::Type::Extends, Visibility::Public));
		}
	}

	symbol->setImplementationType(implementationType);
	symbol->setLanguageFeatureState(languageFeatureState);
	symbol->setParent(mScope);
	symbol->setQualifiedTypename(getQualifiedTypename(type));
	symbol->setVisibility(Visibility::convert(visibility));

	mRepository->addBluePrint(symbol, mScope);

	MethodScope* tmpScope = mScope;

	mProcessingInterface = implementationType == ImplementationType::Interface;
	mScope = symbol;

	generate(tokens);

	mScope = tmpScope;
	mProcessingInterface = false;

	return symbol != 0;
}

bool Analyser::createEnum(TokenIterator& token, TokenIterator end)
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

	mRepository->addBluePrint(symbol, mScope);

	return buildEnum(symbol, tokens);
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
	assert( mScope->getScopeType() == IScope::IType::MethodScope );

	bool isFinal = false;
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
	type = Parser::identify(token);
	// look for the identifier token
	name = (*token++).content();

/*
 * temporarily out of order
	if ( visibility == Visibility::Public ) {
		// beware: public members are deprecated, remember the "Law of Demeter"
		// consider using wrappers (getter, setter) instead of directly providing access to members for outsiders
		// haven't you heard? outsiders, or sometimes called strangers, are evil
		throw Designtime::Exceptions::LawOfDemeterViolated("public member " + name + " violates \"Law of Demeter\"", token->position());
	}
*/

	// look for a mutability keyword
	if ( token->category() == Token::Category::Modifier ) {
		mutability = Mutability::convert(token->content());

		if ( (*token).content() == MODIFIER_FINAL ) {
			isFinal = true;
		}

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
			default: throw Common::Exceptions::NotSupported("initialization is only allowed for atomic data types", token->position());
		}

		token++;
	}

	expect(Token::Type::SEMICOLON, token);

	if ( dynamic_cast<GlobalScope*>(mScope) ||dynamic_cast<Runtime::Namespace*>(mScope) ) {
		Runtime::Object *member = mRepository->createInstance(type, name, false);
		member->setFinal(isFinal);
		member->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
		member->setMember(true);
		member->setMutability(mutability);
		member->setParent(mScope);
		member->setQualifiedTypename(type);
		member->setValue(value);
		member->setVisibility(visibility);

		mScope->define(name, member);
	}
	else if ( dynamic_cast<Designtime::BluePrintObject*>(mScope) ){
		Designtime::BluePrintObject* blue = new Designtime::BluePrintObject(type, mFilename, name);
		blue->setFinal(isFinal);
		blue->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
		blue->setMember(true);
		blue->setMutability(mutability);
		blue->setParent(mScope);
		blue->setQualifiedTypename(type);
		blue->setValue(value);
		blue->setVisibility(visibility);

		mScope->define(name, blue);
	}
	else {
		throw Common::Exceptions::Exception("invalid parent scope type detected for symbol '" + name + "'", token->position());
	}

	return true;
}

bool Analyser::createMethod(TokenIterator& token, TokenIterator /*end*/)
{
	bool isAbstract = false;
	bool isFinal = false;
	bool isRecursive = false;
	bool isStatic = false;
	std::string languageFeature;
	MethodAttributes::MethodType::E methodType = MethodAttributes::MethodType::Function;
	Mutability::E mutability = Mutability::Const;	// extreme const correctness: all methods are const by default
	std::string name;
	int numConstModifiers = 0;
	bool throws = false;
	std::string type;
	std::string visibility;

	// look for the visibility token
	visibility = (*token++).content();
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the type token
	//type = (*token++).content();
	type = Parser::identify(token);
	// look for the identifier token
	name = (*token++).content();

	expect(Token::Type::PARENTHESIS_OPEN, token);


	ParameterList params = Parser::parseParameters(token);

	// look at possible attributes (abstract, const, final, modify, throws, etc.)
	// while looking for the next opening curly bracket
	bool isModifierToken = true;
	do {
		token++;

		if ( token->category() == Token::Category::Modifier ) {
			if ( token->content() == MODIFIER_ABSTRACT ) {
				isAbstract = true;

				//throw Common::Exceptions::NotSupported("global methods cannot be declared as abstract");
			}
			else if ( token->content() == MODIFIER_CONST ) {
				mutability = Mutability::Const;
				numConstModifiers++;
			}
			else if ( token->content() == MODIFIER_FINAL ) {
				isFinal = true;
				//mutability = Mutability::Final;
				//numConstModifiers++;

				//throw Common::Exceptions::NotSupported("global methods cannot be declared as final");
			}
			else if ( token->content() == MODIFIER_MODIFY ) {
				mutability = Mutability::Modify;
				numConstModifiers++;
			}
			else if ( token->content() == MODIFIER_RECURSIVE ) {
				isRecursive = true;
			}
			else if ( token->content() == MODIFIER_STATIC ) {
				isStatic = true;

				//throw Common::Exceptions::NotSupported("global methods cannot be declared as static");
			}
			else if ( token->content() == RESERVED_WORD_THROWS ) {
				throws = true;
			}
		}
		else {
			isModifierToken = false;
		}
	} while ( isModifierToken && token->type() != Token::Type::BRACKET_CURLY_OPEN );

	if ( numConstModifiers > 1 ) {
		throw Common::Exceptions::Exception("modifiers 'const' & 'modify' are exclusive");
	}

	if ( token->type() == Token::Type::RESERVED_WORD && token->content() == RESERVED_WORD_THROWS ) {
		throws = true;
		token++;
	}


	// collect all tokens of this method
	TokenList tokens;
	if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
		if ( mProcessingInterface ) {
			throw Common::Exceptions::SyntaxError("interface methods are not allowed to be implemented", token->position());
		}

		tokens = Parser::collectScopeTokens(token);
	}

	// create a new method with the corresponding return value
	Runtime::Method *method = new Runtime::Method(mScope, name, type);
	method->setAbstract(isAbstract || mProcessingInterface);
	method->setFinal(isFinal);
	method->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	method->setMethodType(methodType);
	method->setMutability(mutability);
	method->setParent(mScope);
	method->setQualifiedTypename(type);
	method->setRecursive(isRecursive);
	method->setSignature(params);
	method->setStatic(isStatic);
	method->setThrows(throws);
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
					throw Common::Exceptions::Exception("cannot extend non-namespace symbol '" + symbol->getName() + "'");
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
		if ( Parser::isInterfaceDeclaration(it) || Parser::isObjectDeclaration(it) ) {
			createBluePrint(it, tokens.end());
		}
		else if ( Parser::isEnumDeclaration(it) ) {
			createEnum(it, tokens.end());
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
		else if ( Parser::isPrototypeDeclaration(it) ) {
			createPrototype(it, tokens.end());
		}
		else {
			throw Common::Exceptions::SyntaxError("invalid token '" + it->content() + "' found", it->position());
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
		throw Common::Exceptions::Exception("File '" + mFilename + "' not found");
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
}
