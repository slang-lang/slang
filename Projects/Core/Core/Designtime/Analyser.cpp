
// Header
#include "Analyser.h"

// Library includes
//#include <cstdlib>
#include <fstream>
#include <iostream>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Designtime/Parser/Tokenizer.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Files.h>
#include <Utils.h>
#include "SanityChecker.h"

// Namespace declarations


namespace Slang {
namespace Designtime {


Analyser::Analyser(bool doSanityCheck)
: mDoSanityCheck(doSanityCheck),
  mProcessingInterface(false)
{
	mRepository = Controller::Instance().repository();
	mScope = Controller::Instance().globalScope();
}

bool Analyser::buildEnum(Designtime::BluePrintObject* symbol, const TokenList& tokens)
{
	auto token = tokens.begin();

	Runtime::AtomicValue previous_value = Runtime::AtomicValue(-1);
	Runtime::AtomicValue value = Runtime::AtomicValue(-1);

	// Format: <identifier> = <value>[, or ;]
	while ( token != tokens.end() ) {
		expect(Token::Type::IDENTIFIER, token);

		std::string name = (token++)->content();

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
			throw Designtime::Exceptions::SyntaxError("enum values have to be defined in ascending order", token->position());
		}

		previous_value = value;

		// define enum entries as parent type
		Runtime::Object* entry = mRepository->createInstance(symbol->QualifiedTypename(), name);
		entry->setMember(true);
		entry->setMemoryLayout(MemoryLayout::Static);
		entry->setMutability(Mutability::Const);
		entry->setQualifiedOuterface(symbol->QualifiedTypename());
		entry->setValue(value.toInt());
		entry->setVisibility(Visibility::Public);

		// define enum entries in current scope
		entry->setParent(symbol);
		symbol->define(name, entry);

		if ( token->type() == Token::Type::COMMA ) {
			++token;

			if ( lookahead(token) == tokens.end() ) {
				throw Designtime::Exceptions::SyntaxError("new enum value expected but none found!", token->position());
			}
		}
		else if ( token->type() == Token::Type::SEMICOLON ) {
			return true;
		}
		else {
			throw Designtime::Exceptions::SyntaxError("unexpected token '" + token->content() + "' found", token->position());
		}
	}

	throw Designtime::Exceptions::SyntaxError("invalid enum declaration", token->position());
}

Ancestors Analyser::collectInheritance(TokenIterator& token)
{
	Ancestors ancestors = Parser::collectInheritance(token);
	Ancestors result;

	for ( const auto& it : ancestors ) {
		Ancestor ancestor(resolveType(it.typeDeclaration(), token), it.ancestorType(), it.visibility());

		result.insert(ancestor);
	}

	return result;
}

bool Analyser::createBluePrint(TokenIterator& token)
{
	if ( mScope && (!dynamic_cast<Common::Namespace*>(mScope) && !dynamic_cast<BluePrintObject*>(mScope)) ) {
		throw Designtime::Exceptions::SyntaxError("objects can only be created within namespaces or objects", token->position());
	}

	// look for an optional visibility token
	Visibility::E visibility = Parser::parseVisibility(token, Visibility::Private);
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);
	// look for an optional modifier token
	ImplementationType::E implementationType = Parser::parseImplementationType(token, ImplementationType::Concrete);
	// look for the object token, BlueprintType::Object is required
	BlueprintType::E blueprintType = Parser::parseBluePrintType(token);
	if ( blueprintType != BlueprintType::Object ) {
		throw Designtime::Exceptions::SyntaxError("object expected", token->position());
	}
	// look for the type declaration
	Common::TypeDeclaration type = parseTypeDeclaration(token, mScope);
	// collect inheritance (if present)
	Ancestors inheritance = collectInheritance(token);

	TokenList tokens;

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

	auto* blueprint = new BluePrintObject(type.mName, mFilename);
	bool extends = false;

	// set up inheritance (if present)
	if ( !inheritance.empty() ) {
		for ( const auto& it : inheritance ) {
			if ( it.ancestorType() == Ancestor::Type::Extends ) {
				extends = true;
			}

			blueprint->addInheritance(it);
		}
	}

	if ( extends && type.mMutability == Mutability::Const ) {
		throw Common::Exceptions::ConstCorrectnessViolated("const object '" + getQualifiedTypename(type.mName) + "' cannot extend objects or implement interfaces", token->position());
	}

	// in case this object has no inheritance set, we inherit from 'Object'
	if ( isImplemented && !extends ) {
		blueprint->addInheritance(Ancestor(Common::TypeDeclaration(std::string(_object)), Ancestor::Type::Extends, Visibility::Public));
	}

	// validate mutability
	if ( type.mMutability == Mutability::Unknown ) {
		throw Designtime::Exceptions::SyntaxError("invalid mutability '" + Mutability::convert(type.mMutability) + "' for " + getQualifiedTypename(type.mName), token->position());
	}

	blueprint->setBluePrintType(blueprintType);
	blueprint->setImplementationType(implementationType);
	blueprint->setIsReference(true);
	blueprint->setLanguageFeatureState(languageFeatureState);
	blueprint->setMutability(type.mMutability);
	blueprint->setParent(mScope);
	blueprint->setPrototypeConstraints(type.mConstraints);
	blueprint->setQualifiedTypename(getQualifiedTypename(type.mName));
	blueprint->setTokens(tokens);
	blueprint->setVisibility(visibility);
	//blueprint->setSealed(type.mMutability == Mutability::Const);

	mScope->define(type.mName, blueprint);

	MethodScope* tmpScope = mScope;

	mScope = blueprint;

	generate(tokens);

	mScope = tmpScope;

	// create default constructor if blueprint has no constructor at all, except it is a replication
	if ( isImplemented && implementationType == ImplementationType::Concrete && !blueprint->hasConstructor() ) {
		ParameterList params;

		auto* defaultConstructor = new Common::Method(blueprint, RESERVED_WORD_CONSTRUCTOR, Common::TypeDeclaration(_void));
		defaultConstructor->setExceptions(CheckedExceptions::Nothrow);
		defaultConstructor->setLanguageFeatureState(LanguageFeatureState::Stable);
		defaultConstructor->setMemoryLayout(MemoryLayout::Instance);
		defaultConstructor->setMethodType(MethodAttributes::MethodType::Constructor);
		defaultConstructor->setMutability(Mutability::Modify);
		defaultConstructor->setParent(blueprint);
		defaultConstructor->setSignature(params);
		defaultConstructor->setVirtuality(Virtuality::Virtual);
		defaultConstructor->setVisibility(Visibility::Public);

		blueprint->defineMethod(RESERVED_WORD_CONSTRUCTOR, defaultConstructor);
	}

	mRepository->addBluePrint(blueprint);

	return blueprint != nullptr;
}

bool Analyser::createEnum(TokenIterator& token)
{
	if ( mScope && (!dynamic_cast<Common::Namespace*>(mScope) && !dynamic_cast<BluePrintObject*>(mScope)) ) {
		throw Designtime::Exceptions::SyntaxError("enum can only be created within namespaces or objects", token->position());
	}

	// look for an optional visibility token
	Visibility::E visibility = Parser::parseVisibility(token, Visibility::Private);
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);
	// look for an optional modifier token
	ImplementationType::E implementationType = Parser::parseImplementationType(token, ImplementationType::Concrete);
	// look for the object token, BlueprintType::Enum is required
	BlueprintType::E bluePrintType = Parser::parseBluePrintType(token);
	if (bluePrintType != BlueprintType::Enum ) {
		throw Designtime::Exceptions::SyntaxError("enum type expected", token->position());
	}
	// look for the type declaration
	Common::TypeDeclaration type = Parser::parseTypeDeclaration(token, mScope);
	if ( !type.mConstraints.empty() ) {
		throw Designtime::Exceptions::SyntaxError("enums are now allowed to be prototypes", token->position());
	}

	// collect all tokens of this method
	TokenList tokens = Parser::collectScopeTokens(token);

	auto* symbol = new BluePrintObject(type.mName, mFilename);
	symbol->setBluePrintType(bluePrintType);
	symbol->setImplementationType(implementationType);
	symbol->setLanguageFeatureState(languageFeatureState);
	symbol->setMutability(Mutability::Modify);
	symbol->setParent(mScope);
	symbol->setPrototypeConstraints(type.mConstraints);
	symbol->setQualifiedTypename(getQualifiedTypename(type.mName));
	symbol->setTokens(tokens);
	symbol->setValue(Runtime::AtomicValue(0));
	symbol->setVisibility(visibility);
	symbol->setSealed(true);

	mScope->define(type.mName, symbol);

	mRepository->addBluePrint(symbol);

	return buildEnum(symbol, tokens);
}

bool Analyser::createInterface(TokenIterator& token)
{
	if ( mScope && (!dynamic_cast<Common::Namespace*>(mScope) && !dynamic_cast<BluePrintObject*>(mScope)) ) {
		throw Designtime::Exceptions::SyntaxError("objects can only be created within namespaces or objects", token->position());
	}

	// look for an optional visibility token
	Visibility::E visibility = Parser::parseVisibility(token, Visibility::Private);
	// look for an optional language feature token, default is unstable
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Unstable);
	// look for an optional modifier token
	ImplementationType::E implementationType = Parser::parseImplementationType(token, ImplementationType::Abstract);
	if ( implementationType != ImplementationType::Abstract ) {
		throw Designtime::Exceptions::SyntaxError("interfaces cannot be concrete", token->position());
	}
	// look for the object token, BlueprintType::Interface is required
	BlueprintType::E blueprintType = Parser::parseBluePrintType(token);
	if (blueprintType != BlueprintType::Interface ) {
		throw Designtime::Exceptions::SyntaxError("interface type expected", token->position());
	}
	// look for the type declaration
	Common::TypeDeclaration type = Parser::parseTypeDeclaration(token, mScope);
	if ( type.mMutability == Mutability::Unknown ) {
		throw Designtime::Exceptions::SyntaxError("invalid mutability '" + Mutability::convert(type.mMutability) + "' for " + getQualifiedTypename(type.mName), token->position());
	}
	// collect inheritance (if present)
	Ancestors inheritance = Parser::collectInheritance(token);

	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	auto* blueprint = new BluePrintObject(type.mName, mFilename);

	// set up inheritance (if present)
	if ( !inheritance.empty() ) {
		for ( const auto& it : inheritance ) {
			if ( it.ancestorType() != Ancestor::Type::Implements ) {
				throw Common::Exceptions::NotSupported("Interfaces can only implement other interfaces", token->position());
			}

			blueprint->addInheritance(it);
		}
	}

	TokenList tokens = Parser::collectScopeTokens(token);

	blueprint->setBluePrintType(blueprintType);
	blueprint->setImplementationType(implementationType);
	blueprint->setIsReference(true);
	blueprint->setLanguageFeatureState(languageFeatureState);
	blueprint->setMutability(type.mMutability);
	blueprint->setParent(mScope);
	blueprint->setPrototypeConstraints(type.mConstraints);
	blueprint->setQualifiedTypename(getQualifiedTypename(type.mName));
	blueprint->setTokens(tokens);
	blueprint->setVisibility(visibility);

	mScope->define(type.mName, blueprint);

	auto* tmpScope = mScope;

	mProcessingInterface = true;
	mScope = blueprint;

	generate(tokens);

	mScope = tmpScope;
	mProcessingInterface = false;

	mRepository->addBluePrint(blueprint);

	return blueprint != nullptr;
}

bool Analyser::createLibraryReference(TokenIterator& token)
{
	std::string reference;

	expect(Token::Type::RESERVED_WORD, token);
	++token;

	while ( token->type() == Token::Type::IDENTIFIER ) {
		reference += (*token++).content();

		if ( token->type() != Token::Type::OPERATOR_SCOPE ) {
			break;
		}

		reference += ".";
		++token;
	}

	expect(Token::Type::SEMICOLON, token);

	mLibraries.push_back(reference);

	return true;
}

bool Analyser::createMemberOrMethod(TokenIterator& token)
{
	// look for an optional visibility token
	Visibility::E visibility = Parser::parseVisibility(token, Visibility::Private);
	// look up memory layout
	MemoryLayout::E memoryLayout = Parser::parseMemoryLayout(token, MemoryLayout::Instance);
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);
	// look for the type token and resolve full typename
	Common::TypeDeclaration type = parseTypeDeclaration(token, mScope);
	// look for the identifier token
	std::string name = (*token++).content();

	if ( token->type() == Token::Type::PARENTHESIS_OPEN ) {
		// create a new method
		return createMethodStub(token, visibility, memoryLayout, languageFeatureState, type, name);
	}

	// create a new member
	return createMemberStub(token, visibility, memoryLayout, languageFeatureState, type, name);
}

bool Analyser::createMemberStub(TokenIterator& token, Visibility::E visibility, MemoryLayout::E memoryLayout, LanguageFeatureState::E languageFeature, const Common::TypeDeclaration& type, const std::string& name)
{
	assert( mScope->getScopeType() == IScope::IType::MethodScope );

	// look for an optional mutability token
	Mutability::E mutability = Parser::parseMutability(token, Mutability::Modify);
	// look up access mode
	AccessMode::E access = Parser::parseAccessMode(token, AccessMode::ByValue);

	// check parent's constness
	auto* parent = dynamic_cast<BluePrintObject*>(mScope);
	if ( parent && parent->isConst() && mutability != Mutability::Const ) {
		throw Common::Exceptions::ConstCorrectnessViolated("cannot add modifiable member '" + name + "' to const object '" + parent->getFullScopeName() + "'", token->position());
	}

	Runtime::AtomicValue value = (type == _string) ? Runtime::AtomicValue(std::string(VALUE_NONE)) : Runtime::AtomicValue(int(0));
	if ( token->type() == Token::Type::ASSIGN ) {
		++token;

		value = Parser::parseValueInitialization(token, type.mName);

		++token;
	}

	expect(Token::Type::SEMICOLON, token);

	if ( dynamic_cast<BluePrintObject*>(mScope) && memoryLayout != MemoryLayout::Static ) {
		auto* member = new BluePrintObject(type.mName, mFilename, name);
		member->setIsReference(access == AccessMode::ByReference);
		member->setLanguageFeatureState(languageFeature);
		member->setMember(true);
		member->setMemoryLayout(memoryLayout);
		member->setMutability(mutability);
		member->setParent(nullptr);
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
		symbol->setMember(dynamic_cast<BluePrintObject*>(mScope));
		symbol->setMemoryLayout(memoryLayout);
		symbol->setMutability(mutability);
		symbol->setParent(mScope);
		symbol->setValue(value);
		symbol->setVisibility(visibility);

		mScope->define(name, symbol);
	}

	return true;
}

bool Analyser::createMethodStub(TokenIterator& token, Visibility::E visibility, MemoryLayout::E memoryLayout, LanguageFeatureState::E languageFeature, const Common::TypeDeclaration& type, const std::string& name)
{
	assert( mScope->getScopeType() == IScope::IType::MethodScope );

	CheckedExceptions::E exceptions = CheckedExceptions::Nothrow;
	MethodAttributes::MethodType::E methodType = MethodAttributes::MethodType::Function;
	Mutability::E mutability = Mutability::Const;	// extreme const correctness: all methods are const by default (except constructors and destructors)
	Virtuality::E virtuality = mProcessingInterface ? Virtuality::Abstract : Virtuality::Virtual;

	auto* blueprint = dynamic_cast<BluePrintObject*>(mScope);
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

	ParameterList params = parseParameters(token, mScope);

	++token;

	mutability = Parser::parseMutability(token, mutability);
	exceptions = Parser::parseExceptions(token, exceptions);
	virtuality = Parser::parseVirtuality(token, virtuality);

	if ( methodType == MethodAttributes::MethodType::Destructor && exceptions == CheckedExceptions::Throw ) {
		OSwarn("exceptions thrown in destructor cannot be caught in " + token->position().toString());
	}

	// check parent's constness
	if ( methodType != MethodAttributes::MethodType::Constructor && methodType != MethodAttributes::MethodType::Destructor ) {
		auto* parent = dynamic_cast<BluePrintObject*>(mScope);
		if ( parent && parent->isConst() && mutability != Mutability::Const ) {
			throw Common::Exceptions::ConstCorrectnessViolated("cannot add modifiable method '" + name + "' to const object '" + parent->getFullScopeName() + "'", token->position());
		}
	}

	// collect all tokens of this method
	TokenList tokens;
	if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
		if ( virtuality == Virtuality::Abstract ) {
			throw Designtime::Exceptions::SyntaxError("abstract methods are not allowed to be implemented", token->position());
		}

		tokens = Parser::collectScopeTokens(token);
	}
	else if ( languageFeature != LanguageFeatureState::NotImplemented && virtuality != Virtuality::Abstract ) {
		throw Designtime::Exceptions::SyntaxError("method '" + name + "' is not declared as abstract or not annotated with '" + LANGUAGE_FEATURE_NOTIMPLEMENTED + "' but has no implementation", token->position());
	}

	// if this method is a runtime method then prototype constraints are not allowed (because they will never get resolved)
	if ( !blueprint && !type.mConstraints.hasRuntimeTypes() ) {
		throw Designtime::Exceptions::SyntaxError("only resolved prototype constraints are allowed in static methods", token->position());
	}

	// create a new method with the corresponding return type
	auto* method = new Common::Method(mScope, name, type);
	method->setExceptions(exceptions);
	method->setLanguageFeatureState(languageFeature);
	method->setMemoryLayout(memoryLayout);
	method->setMethodMutability(mutability);
	method->setMethodType(methodType);
	method->setMutability(type.mMutability);
	method->setParent(mScope);
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
		throw Designtime::Exceptions::SyntaxError("namespaces can only be created within namespaces", token->position());
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

		if ( token->type() == Token::Type::OPERATOR_SCOPE ) {
			++token;
		}

		Common::Namespace* space = nullptr;

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
					space = dynamic_cast<Common::Namespace*>(symbol);
					break;
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

	mScope = tmpScope;

	return true;
}

/*
 * loop over all tokens and look for imports and object declarations
 */
void Analyser::generate(const TokenList& tokens)
{
	auto token = tokens.cbegin();
	auto localEnd = tokens.cend();

	while ( token != localEnd && token->type() != Token::Type::ENDOFFILE ) {
		if ( Parser::isObjectDeclaration(token) ) {
			createBluePrint(token);
		}
		else if ( Parser::isEnumDeclaration(token) ) {
			createEnum(token);
		}
		else if ( Parser::isInterfaceDeclaration(token) ) {
			createInterface(token);
		}
		else if ( Parser::isLibraryReference(token) ) {
			createLibraryReference(token);
		}
		else if ( Parser::isNamespaceDeclaration(token) ) {
			createNamespace(token);
		}
		else if ( createMemberOrMethod(token) ) {
			// nothing to do here
		}
		else {
			throw Designtime::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
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

ParameterList Analyser::parseParameters(TokenIterator& token, IScope* scope)
{
	ParameterList params = Parser::parseParameters(token, scope);

	for ( auto& param : params ) {
		param.mType = resolveType(param.typeDeclaration(), token);
	}

	return params;
}

Common::TypeDeclaration Analyser::parseTypeDeclaration(TokenIterator& token, IScope* scope)
{
	return resolveType(Parser::parseTypeDeclaration(token, scope), token);
}

void Analyser::processFile(const std::string& filename)
{
	mFilename = filename;

	if ( !::Utils::Tools::Files::exists(mFilename) ) {
		throw Common::Exceptions::Exception("File '" + mFilename + "' not found");
	}

	// read file content
	std::ifstream in(mFilename.c_str(), std::ios_base::binary);

	// start the real processing
	processTokens(
		// create token list from string
		generateTokens(std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()))
	);
}

void Analyser::processString(const std::string& content, const std::string& filename)
{
	mFilename = filename;

	// start the real processing
	processTokens(
		// create token list from string
		generateTokens(content)
	);
}

void Analyser::processTokens(const TokenList& tokens)
{
	// factory reset
	mLibraries.clear();

	if ( mDoSanityCheck ) {
		// execute basic sanity checks
		SanityChecker sanity;
		sanity.process(tokens);
	}

	// generate objects from tokens
	generate(tokens);
}

std::string Analyser::resolveType(const std::string& type, const TokenIterator& token) const
{
	// look up type in scope
	IScope* scope = mScope;

	while ( scope ) {
		Symbol* symbol = scope->resolve(type, false, Visibility::Private);
		if ( symbol ) {
			switch ( symbol->getSymbolType() ) {
				case Symbol::IType::BluePrintObjectSymbol: return dynamic_cast<BluePrintObject*>(symbol)->QualifiedTypename();
				case Symbol::IType::MethodSymbol:
				case Symbol::IType::NamespaceSymbol:
				case Symbol::IType::ObjectSymbol:
					throw Designtime::Exceptions::SyntaxError("invalid symbol type detected", token->position());
			}
		}

		scope = scope->getEnclosingScope();
	}

	// nothing found so return the original type
	return type;
}

Common::TypeDeclaration Analyser::resolveType(const Common::TypeDeclaration& type, const TokenIterator& token) const
{
	Common::TypeDeclaration result;
	result.mMutability = type.mMutability;

	// resolve type
	result.mName = resolveType(type.mName, token);
	result.mCombinedName = result.mName;

	// resolve prototype constraints
	for ( const auto& mConstraint : type.mConstraints ) {
		PrototypeConstraint constraint = mConstraint;

		constraint.mConstraint = resolveType(mConstraint.mConstraint, token);
		constraint.mRunType = resolveType(mConstraint.mRunType, token);

		result.mConstraints.push_back(constraint);
	}

	return result;
}


}
}
