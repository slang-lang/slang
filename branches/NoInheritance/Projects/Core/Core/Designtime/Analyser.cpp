
// Header
#include "Analyser.h"

// Library includes
#include <cstdlib>
#include <fstream>
#include <iostream>

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Designtime/Parser/Tokenizer.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Files.h>
#include <Utils.h>
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

	Runtime::AtomicValue previous_value = Runtime::AtomicValue(-1);
	Runtime::AtomicValue value = Runtime::AtomicValue(-1);

	// Format: <identifier> = <value>[, or ;]
	while ( token != tokens.end() ) {
		std::string name;

		expect(Token::Type::IDENTIFIER, token);
		name = (token++)->content();

		if ( token->type() == Token::Type::ASSIGN ) {
			expect(Token::Type::ASSIGN, token);
			++token;

			expect(Token::Type::CONST_INTEGER, token);
			value = (token++)->content();
		}
		else {
			value = value.toInt() + 1;
		}

		// verify declaration order (this also prevents duplicate values)
		if ( previous_value.toInt() >= value.toInt() ) {
			throw Common::Exceptions::Exception("enum values have to be defined in ascending order", token->position());
		}

		previous_value = value;

		// define enum entries as parent type
		//Runtime::Object* entry = mRepository->createInstance(mBluePrint->QualifiedTypename(), name, true);
		//entry->setConstructed(true);

		// define enum entries as integer type
		Runtime::Object* entry = new Runtime::IntegerObject(name, value.toInt());	// this prevents a double delete because all instances are freed by their surrounding scope
		entry->setMember(true);
		entry->setMutability(Mutability::Const);
		entry->setValue(value.toInt());
		entry->setVisibility(Visibility::Public);

		// define enum entries in current scope
		entry->setParent(symbol);
		symbol->define(name, entry);

		if ( token->type() == Token::Type::COMMA ) {
			++token;

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

bool Analyser::createBluePrint(TokenIterator& token)
{
	if ( mScope && (!dynamic_cast<Common::Namespace*>(mScope) && !dynamic_cast<BluePrintObject*>(mScope)) ) {
		throw Common::Exceptions::SyntaxError("objects can only be created within namespaces or objects", token->position());
	}

	PrototypeConstraints constraints;
	TokenList tokens;

	// look for an optional visibility token
	Visibility::E visibility = Parser::parseVisibility(token, Visibility::Private);
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);
	// look for an optional modifier token
	ImplementationType::E implementationType = Parser::parseImplementationType(token, ImplementationType::FullyImplemented);
	// look for the object token
	ObjectType::E objectType = Parser::parseObjectType(token);
	// look for the identifier token
	std::string name = (*token++).content();
	// look for an optional modifier token
	Mutability::E mutability = Mutability::Modify;

	BluePrintObject* blueprint = new BluePrintObject(name, mFilename);

	if ( token->type() == Token::Type::SEMICOLON ) {
		if ( implementationType != ImplementationType::FullyImplemented ) {
			throw Common::Exceptions::NotSupported("forward declarations cannot be defined as interface or abstract object", token->position());
		}

		// set implementation type
		implementationType = ImplementationType::ForwardDeclaration;
	}
	else {
		// collect prototype constraints (if present)
		constraints = Parser::collectDesigntimePrototypeConstraints(token);
		// collect mutability
		mutability = Parser::parseMutability(token, Mutability::Modify);
		// collect inheritance (if present)
		Ancestors inheritance = Parser::collectInheritance(token);

		bool isImplemented = true;
		if ( !inheritance.empty() ) {
			isImplemented = (inheritance.begin()->ancestorType() != Ancestor::Type::Replicates);
		}

		if ( isImplemented ) {
			isImplemented = (token->type() != Token::Type::SEMICOLON);
		}
		if ( isImplemented ) {	// only collect all tokens of this object if it is implemented
			tokens = Parser::collectScopeTokens(token);
		}

		bool extends = false;

		// set up inheritance (if present)
		if ( !inheritance.empty() ) {
			for ( Ancestors::const_iterator it = inheritance.begin(); it != inheritance.end(); ++it ) {
				if ( it->ancestorType() == Ancestor::Type::Extends ) {
					extends = true;
				}

				blueprint->addInheritance((*it));
			}
		}

		if ( objectType == ObjectType::Object && extends && mutability == Mutability::Const ) {
			throw Common::Exceptions::ConstCorrectnessViolated("const object '" + getQualifiedTypename(name) + "' cannot extend objects or implement interfaces", token->position());
		}

		// in case this object has no inheritance set, we inherit from 'Object'
		if ( objectType != ObjectType::Interface && !extends ) {
			blueprint->addInheritance(Ancestor(Common::TypeDeclaration(_object), Ancestor::Type::Extends, Visibility::Public));
		}
	}

	// validate mutability
	if ( mutability != Mutability::Const && mutability != Mutability::Modify ) {
		throw Common::Exceptions::SyntaxError("invalid mutability '" + Mutability::convert(mutability) + "' for " + getQualifiedTypename(name), token->position());
	}

	// determine implementation type
	if ( objectType == ObjectType::Interface ) {
		if ( mutability != Mutability::Modify ) {
			throw Common::Exceptions::NotSupported("interface mutability has to be modifiable", token->position());
		}

		implementationType = ImplementationType::Interface;
	}

	blueprint->setPrototypeConstraints(constraints);
	blueprint->setImplementationType(implementationType);
	blueprint->setIsReference(true);
	blueprint->setLanguageFeatureState(languageFeatureState);
	blueprint->setMutability(mutability);
	blueprint->setParent(mScope);
	blueprint->setQualifiedTypename(getQualifiedTypename(name));
	blueprint->setTokens(tokens);
	blueprint->setVisibility(visibility);
	blueprint->setSealed(mutability == Mutability::Const);

	if ( implementationType == ImplementationType::ForwardDeclaration ) {
		return blueprint != 0;
	}

	mScope->define(name, blueprint);

	MethodScope* tmpScope = mScope;

	mProcessingInterface = implementationType == ImplementationType::Interface;
	mScope = blueprint;

	generate(tokens);

	mScope = tmpScope;
	mProcessingInterface = false;

	// create default constructor if blueprint has no constructor at all
	if ( implementationType == ImplementationType::FullyImplemented && !blueprint->hasConstructor() ) {
		ParameterList params;
/*	this has to be used as soon as 'this' is passed to methods as first parameter
		params.push_back(Parameter::CreateDesigntime(
			IDENTIFIER_THIS, Common::TypeDeclaration(name, constraints)
		));
*/

		Common::Method* defaultConstructor = new Common::Method(blueprint, CONSTRUCTOR, _void);
		defaultConstructor->setExceptions(CheckedExceptions::Nothrow);
		defaultConstructor->setLanguageFeatureState(LanguageFeatureState::Stable);
		defaultConstructor->setMemoryLayout(MemoryLayout::Instance);
		defaultConstructor->setMethodType(MethodAttributes::MethodType::Constructor);
		defaultConstructor->setMutability(Mutability::Modify);
		defaultConstructor->setParent(blueprint);
		defaultConstructor->setSignature(params);
		defaultConstructor->setVirtuality(Virtuality::Virtual);
		defaultConstructor->setVisibility(Visibility::Public);

		blueprint->defineMethod(CONSTRUCTOR, defaultConstructor);
	}

	mRepository->addBluePrint(blueprint);

	return blueprint != 0;
}

bool Analyser::createEnum(TokenIterator& token)
{
	if ( mScope && (!dynamic_cast<Common::Namespace*>(mScope) && !dynamic_cast<BluePrintObject*>(mScope)) ) {
		throw Common::Exceptions::SyntaxError("enum can only be created within namespaces or objects", token->position());
	}

	// look for an optional visibility token
	Visibility::E visibility = Parser::parseVisibility(token, Visibility::Private);
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);

	// determine implementation type
	ObjectType::E objectType = Parser::parseObjectType(token);
	if ( objectType != ObjectType::Enum ) {
		throw Common::Exceptions::SyntaxError("enum type expected", token->position());
	}

	// look for the identifier token
	Common::TypeDeclaration type = Parser::parseTypeDeclaration(token, mScope);
	if ( !type.mConstraints.empty() ) {
		throw Common::Exceptions::SyntaxError("enums are now allowed to be prototypes", token->position());
	}

	// collect all tokens of this method
	TokenList tokens = Parser::collectScopeTokens(token);

	BluePrintEnum* symbol = new BluePrintEnum(type.mName, mFilename);
	symbol->setLanguageFeatureState(languageFeatureState);
	symbol->setMutability(Mutability::Modify);
	symbol->setParent(mScope);
	symbol->setPrototypeConstraints(type.mConstraints);
	symbol->setQualifiedTypename(getQualifiedTypename(type.mName));
	symbol->setTokens(tokens);
	symbol->setVisibility(visibility);
	symbol->setSealed(true);

	mScope->define(type.mName, symbol);

	mRepository->addBluePrint(symbol);

	return buildEnum(symbol, tokens);
}

bool Analyser::createLibraryReference(TokenIterator& token)
{
	std::string reference;

	expect(Token::Type::RESERVED_WORD, token);
	++token;

	while ( token->type() == Token::Type::IDENTIFIER ) {
		reference += (*token++).content();

		if ( token->type() != Token::Type::SCOPE ) {
			break;
		}

		reference += ".";
		++token;
	}

	expect(Token::Type::SEMICOLON, token);

	mLibraries.push_back(reference);

	return true;
}

bool Analyser::createMember(TokenIterator& token)
{
	// look for an optional visibility token
	Visibility::E visibility = Parser::parseVisibility(token, Visibility::Private);
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);
	// look for the type token
	Common::TypeDeclaration type = Parser::parseTypeDeclaration(token);
	// look for the identifier token
	std::string name = (*token++).content();

	return createMemberStub(token, visibility, languageFeatureState, type, name);
}

bool Analyser::createMemberOrMethod(TokenIterator& token)
{
	// look for an optional visibility token
	Visibility::E visibility = Parser::parseVisibility(token, Visibility::Private);
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);
	// look for the type token
	Common::TypeDeclaration type = Parser::parseTypeDeclaration(token, mScope);
	// look for the identifier token
	std::string name = (*token++).content();

	if ( token->type() == Token::Type::PARENTHESIS_OPEN ) {
		// create a new method
		return createMethodStub(token, visibility, languageFeatureState, type, name);
	}

	// create a new member
	return createMemberStub(token, visibility, languageFeatureState, type, name);
}

bool Analyser::createMemberStub(TokenIterator& token, Visibility::E visibility, LanguageFeatureState::E languageFeature, Common::TypeDeclaration type, const std::string& name)
{
	assert( mScope->getScopeType() == IScope::IType::MethodScope );

	Mutability::E mutability = Parser::parseMutability(token, Mutability::Modify);
	MemoryLayout::E memoryLayout = Parser::parseMemoryLayout(token, MemoryLayout::Instance);
	AccessMode::E access = Parser::parseAccessMode(token, AccessMode::ByValue);

	// check parent's constness
	BluePrintObject* parent = dynamic_cast<BluePrintObject*>(mScope);
	if ( parent && parent->isConst() && mutability != Mutability::Const ) {
		throw Common::Exceptions::ConstCorrectnessViolated("cannot add modifiable member '" + name + "' to const object '" + parent->getFullScopeName() + "'", token->position());
	}

	Runtime::AtomicValue value = 0;
	if ( token->type() == Token::Type::ASSIGN ) {
		++token;

		value = Parser::parseValueInitialization(token);

		++token;
	}

	expect(Token::Type::SEMICOLON, token);

	if ( dynamic_cast<BluePrintGeneric*>(mScope) && memoryLayout != MemoryLayout::Static ) {
		BluePrintObject* member = new BluePrintObject(type.mName, mFilename, name);
		member->setIsReference(access == AccessMode::ByReference);
		member->setLanguageFeatureState(languageFeature);
		member->setMember(true);
		member->setMemoryLayout(memoryLayout);
		member->setMutability(mutability);
		member->setParent(NULL);
		member->setPrototypeConstraints(type.mConstraints);
		member->setQualifiedTypename(type.mName);
		member->setValue(value);
		member->setVisibility(visibility);

		mScope->define(name, member);
	}
	else {
		Runtime::Object* symbol = mRepository->createInstance(type.mName, name, type.mConstraints);
		symbol->setIsReference(access == AccessMode::ByReference);
		symbol->setLanguageFeatureState(languageFeature);
		symbol->setMember(dynamic_cast<BluePrintGeneric*>(mScope));
		symbol->setMemoryLayout(memoryLayout);
		symbol->setMutability(mutability);
		symbol->setParent(mScope);
		symbol->setValue(value);
		symbol->setVisibility(visibility);

		mScope->define(name, symbol);
	}

	return true;
}

bool Analyser::createMethod(TokenIterator& token)
{
	// look for an optional visibility token
	Visibility::E visibility = Parser::parseVisibility(token, Visibility::Private);
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);
	// look for the type token
	Common::TypeDeclaration type = Parser::parseTypeDeclaration(token);
	// look for the identifier token
	std::string name = (*token++).content();

	return createMethodStub(token, visibility, languageFeatureState, type, name);
}

bool Analyser::createMethodStub(TokenIterator& token, Visibility::E visibility, LanguageFeatureState::E languageFeature, Common::TypeDeclaration type, const std::string& name)
{
	assert( mScope->getScopeType() == IScope::IType::MethodScope );

	CheckedExceptions::E exceptions = CheckedExceptions::Nothrow;
	MemoryLayout::E memoryLayout = MemoryLayout::Instance;
	MethodAttributes::MethodType::E methodType = MethodAttributes::MethodType::Function;
	Mutability::E mutability = Mutability::Const;	// extreme const correctness: all methods are const by default (except constructors and destructors)
	bool throws = false;
	Virtuality::E virtuality = mProcessingInterface ? Virtuality::Abstract : Virtuality::Virtual;


	BluePrintGeneric* blueprint = dynamic_cast<BluePrintGeneric*>(mScope);
	if ( blueprint && name == RESERVED_WORD_CONSTRUCTOR ) {
		// constructors can never ever be const
		methodType = MethodAttributes::MethodType::Constructor;
		mutability = Mutability::Modify;
	}
	else if ( blueprint && name == RESERVED_WORD_DESTRUCTOR ) {
		// destructors can never ever be const
		methodType = MethodAttributes::MethodType::Destructor;
		mutability = Mutability::Modify;
	}

	ParameterList params = Parser::parseParameters(token, mScope);
/*
	// if this is an object method add 'this' as first parameter
	if ( blueprint ) {
		params.push_front(Parameter::CreateDesigntime(
				IDENTIFIER_THIS,
				Common::TypeDeclaration(blueprint->QualifiedTypename()),
				Runtime::AtomicValue(),
				false,
				mutability,
				AccessMode::ByReference
		));
	}
*/

	++token;

	mutability = Parser::parseMutability(token, mutability);
	memoryLayout = Parser::parseMemoryLayout(token, memoryLayout);
	exceptions = Parser::parseExceptions(token, exceptions);
	virtuality = Parser::parseVirtuality(token, virtuality);

	if ( methodType == MethodAttributes::MethodType::Destructor && exceptions == CheckedExceptions::Throw ) {
		OSwarn("exceptions thrown in destructor cannot be caught in " + token->position().toString());
	}

	// check parent's constness
	if ( methodType != MethodAttributes::MethodType::Constructor && methodType != MethodAttributes::MethodType::Destructor ) {
		BluePrintObject* parent = dynamic_cast<BluePrintObject*>(mScope);
		if ( parent && parent->isConst() && mutability != Mutability::Const ) {
			throw Common::Exceptions::ConstCorrectnessViolated("cannot add modifiable method '" + name + "' to const object '" + parent->getFullScopeName() + "'", token->position());
		}
	}

	// collect all tokens of this method
	TokenList tokens;
	if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
		if ( virtuality == Virtuality::Abstract ) {
			throw Common::Exceptions::SyntaxError("interface methods are not allowed to be implemented", token->position());
		}

		tokens = Parser::collectScopeTokens(token);
	}
	else if ( virtuality != Virtuality::Abstract ) {
		throw Common::Exceptions::SyntaxError("method '" + name + "' is not declared as abstract but has no implementation", token->position());
	}

	// if this method is a runtime method then prototype constraints are not allowed (because they will never get resolved)
	if ( !blueprint && !type.mConstraints.hasRuntimeTypes() ) {
		throw Common::Exceptions::SyntaxError("only resolved prototype constraints are allowed in non-object methods", token->position());
	}

	// create a new method with the corresponding return type
	Common::Method* method = new Common::Method(mScope, name, type.mName);
	method->setExceptions(exceptions);
	method->setLanguageFeatureState(languageFeature);
	method->setMethodType(methodType);
	method->setMemoryLayout(memoryLayout);
	method->setMutability(mutability);
	method->setParent(mScope);
	method->setPrototypeConstraints(type.mConstraints);
	method->setSignature(params);
	method->setTokens(tokens);
	method->setVirtuality(virtuality);
	method->setVisibility(visibility);

	mScope->defineMethod(name, method);

	return true;
}

bool Analyser::createNamespace(TokenIterator& token)
{
	if ( mScope && !dynamic_cast<Common::Namespace*>(mScope) ) {
		throw Common::Exceptions::SyntaxError("namespaces can only be created within namespaces", token->position());
	}

	// look for an optional visibility token
	Visibility::E visibility = Parser::parseVisibility(token, Visibility::Private);
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);
	// look for the "namespace" token
	expect(Token::Type::RESERVED_WORD, token);
	++token;

	MethodScope* tmpScope = mScope;

	while ( token->type() == Token::Type::IDENTIFIER ) {
		// look for the identifier token
		std::string name = (*token++).content();

		if ( token->type() == Token::Type::SCOPE ) {
			++token;
		}

		Common::Namespace* space = 0;

		// check for an existing namespace with this name
		Symbol* symbol = mScope->resolve(name, true, Visibility::Designtime);
		if ( !symbol ) {
			space = new Common::Namespace(name, mScope);
			space->setLanguageFeatureState(languageFeatureState);
			space->setQualifiedTypename(getQualifiedTypename(name));
			space->setVisibility(visibility);
			space->setSealed(space->getVisibility() == Visibility::Private);		// seal has to be the last attribute to be set

			mScope->define(name, space);
		}
		else {
			switch ( symbol->getSymbolType() ) {
				case Symbol::IType::NamespaceSymbol:
					space = static_cast<Common::Namespace*>(symbol);
					break;
				case Symbol::IType::BluePrintEnumSymbol:
				case Symbol::IType::BluePrintObjectSymbol:
				case Symbol::IType::MethodSymbol:
				case Symbol::IType::ObjectSymbol:
					throw Common::Exceptions::Exception("cannot extend non-namespace symbol '" + symbol->getName() + "'", token->position());
			}
		}

		mScope = space;
	}

	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	TokenList tokens = Parser::collectScopeTokens(token);

	generate(tokens);

	static_cast<Common::Namespace*>(mScope)->initialize();

	mScope = tmpScope;

	return true;
}

/*
 * loop over all tokens and look for imports and object declarations
 */
void Analyser::generate(const TokenList& tokens)
{
	TokenList::const_iterator token = tokens.begin();
	TokenList::const_iterator localEnd = tokens.end();

	while ( token != localEnd && token->type() != Token::Type::ENDOFFILE ) {
		if ( Parser::isInterfaceDeclaration(token) || Parser::isObjectDeclaration(token) ) {
			createBluePrint(token);
		}
		else if ( Parser::isEnumDeclaration(token) ) {
			createEnum(token);
		}
		else if ( Parser::isLibraryReference(token) ) {
			createLibraryReference(token);
		}
		else if ( Parser::isMemberDeclaration(token) ) {
			createMember(token);
		}
		else if ( Parser::isMethodDeclaration(token) ) {
			createMethod(token);
		}
		else if ( Parser::isNamespaceDeclaration(token) ) {
			createNamespace(token);
		}
		else if ( !createMemberOrMethod(token) ) {
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		};

		++token;
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

void Analyser::processFile(const std::string& filename)
{
	mFilename = filename;

	if ( !::Utils::Tools::Files::exists(mFilename) ) {
		throw Common::Exceptions::Exception("File '" + mFilename + "' not found");
	}

	// read file content
	std::ifstream in(mFilename.c_str(), std::ios_base::binary);

	// create token list from string
	TokenList tokens = generateTokens(std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()));

	// start the real processing
	processTokens(tokens);
}

void Analyser::processString(const std::string& content, const std::string& filename)
{
	mFilename = filename;

	// create token list from string
	TokenList tokens = generateTokens(content);

	// start the real processing
	processTokens(tokens);
}

void Analyser::processTokens(const TokenList& tokens)
{
	// factory reset
	mLibraries.clear();

	// execute basic sanity checks
	SanityChecker sanity;
	sanity.process(tokens);

	// generate objects from tokens
	generate(tokens);
}


}
}
