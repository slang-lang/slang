
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
#include <Core/Designtime/Parser/Tokenizer.h>
#include <Core/Runtime/Namespace.h>
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

	BluePrintObject* blueprint = new BluePrintObject(type, mFilename);

	// determine implementation type
	if ( objectType == ObjectType::Interface ) {
		if ( implementationType != ImplementationType::FullyImplemented ) {
			throw Common::Exceptions::NotSupported("interfaces cannot be defined as abstract", token->position());
		}

		implementationType = ImplementationType::Interface;
	}

	TokenList tokens;

	if ( token->type() == Token::Type::SEMICOLON ) {
		if ( implementationType != ImplementationType::FullyImplemented ) {
			throw Common::Exceptions::NotSupported("forward declarations cannot be defined as interface or abstract object", token->position());
		}

		implementationType = ImplementationType::ForwardDeclaration;
	}
	else {
		// collect prototype constraints (if present)
		PrototypeConstraints constraints = Parser::collectPrototypeConstraints(token);

		blueprint->setPrototypeConstraints(constraints);

		// collect inheritance (if present)
		Ancestors inheritance = Parser::collectInheritance(token);

		bool isImplemented = true;
		if ( !inheritance.empty() ) {
			isImplemented = (inheritance.begin()->type() != Ancestor::Type::Replicates);
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

		blueprint->setTokens(tokens);

		bool extends = false;

		// set up inheritance (if present)
		if ( !inheritance.empty() ) {
			for ( Ancestors::const_iterator it = inheritance.begin(); it != inheritance.end(); ++it ) {
				if ( it->type() == Ancestor::Type::Extends ) {
					extends = true;
				}

				blueprint->addInheritance((*it));
			}
		}

		// in case this object has no inheritance set, we inherit from 'Object'
		if ( objectType != ObjectType::Interface && !extends ) {
			blueprint->addInheritance(Ancestor(OBJECT, Ancestor::Type::Extends, Visibility::Public, PrototypeConstraints()));
		}
	}

	blueprint->setImplementationType(implementationType);
	blueprint->setLanguageFeatureState(languageFeatureState);
	blueprint->setParent(mScope);
	blueprint->setQualifiedTypename(getQualifiedTypename(type));
	blueprint->setVisibility(Visibility::convert(visibility));

	mRepository->addBluePrint(blueprint);

	if ( implementationType == ImplementationType::ForwardDeclaration ) {
		return blueprint != 0;
	}

	mScope->define(blueprint->Typename(), blueprint);

	MethodScope* tmpScope = mScope;

	mProcessingInterface = implementationType == ImplementationType::Interface;
	mScope = blueprint;

	generate(tokens);

	mScope = tmpScope;
	mProcessingInterface = false;

	return blueprint != 0;
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

	BluePrintEnum* symbol = new BluePrintEnum(type, mFilename);
	symbol->setFinal(true);
	symbol->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	symbol->setMutability(Mutability::Modify);
	symbol->setParent(mScope);
	symbol->setQualifiedTypename(getQualifiedTypename(type));
	symbol->setTokens(tokens);
	symbol->setVisibility(Visibility::convert(visibility));
	symbol->setSealed(true);

	mRepository->addBluePrint(symbol);

	mScope->define(symbol->Typename(), symbol);

	return buildEnum(symbol, tokens);
}

bool Analyser::createLibraryReference(TokenIterator& token, TokenIterator end)
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

	mLibraries.push_back(reference);

	return true;
}

bool Analyser::createMember(TokenIterator& token, TokenIterator /*end*/)
{
	assert( mScope->getScopeType() == IScope::IType::MethodScope );

	bool isFinal = false;
	std::string languageFeature;
	Mutability::E mutability = Mutability::Modify;
	std::string name;
	TypeDeclaration type;
	Runtime::AtomicValue value = 0;
	Visibility::E visibility;

	// look for the visibility token
	visibility = Visibility::convert((*token++).content());
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the type token
	type = Parser::parseTypeDeclaration(token);
	// look for the identifier token
	name = (*token++).content();

/*	temporary deactivated
	if ( !dynamic_cast<Runtime::Namespace*>(mScope) ) {
		if ( visibility == Visibility::Public ) {
			// beware: public members are deprecated, remember the "Law of Demeter"
			// consider using wrappers (getter, setter) instead of directly providing access to members for outsiders
			// haven't you heard? outsiders, or sometimes called strangers, are evil
			throw Exceptions::LawOfDemeterViolated("public member " + name + " violates \"Law of Demeter\"", token->position());
		}
	}
*/

	// look for a mutability keyword
	if ( token->category() == Token::Category::Modifier ) {
		mutability = Mutability::convert(token->content());

		if ( token->content() == MODIFIER_FINAL ) {
			isFinal = true;
		}

		token++;
	}

	if ( token->type() == Token::Type::ASSIGN ) {
		token++;

		value = Parser::parseValueInitialization(token);

		token++;
	}

	expect(Token::Type::SEMICOLON, token);

	if ( dynamic_cast<BluePrintGeneric*>(mScope) ){
		BluePrintObject* blue = new BluePrintObject(type.mTypename, mFilename, name);
		blue->setFinal(isFinal);
		blue->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
		blue->setMember(true);
		blue->setMutability(mutability);
		blue->setParent(mScope);
		blue->setPrototypeConstraints(type.mConstraints);
		blue->setQualifiedTypename(type.mTypename);
		blue->setValue(value);
		blue->setVisibility(visibility);

		mScope->define(name, blue);
	}
	else {
		Runtime::Object *member = mRepository->createInstance(type.mTypename, name, type.mConstraints, false);
		member->setFinal(isFinal);
		member->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
		member->setMember(true);
		member->setMutability(mutability);
		member->setParent(mScope);
		member->setQualifiedTypename(type.mTypename);
		member->setValue(value);
		member->setVisibility(visibility);

		mScope->define(name, member);
	}

	return true;
}

bool Analyser::createMemberOrMethod(TokenIterator& token, TokenIterator /*end*/)
{
	assert( mScope->getScopeType() == IScope::IType::MethodScope );

	bool isAbstract = mProcessingInterface;
	bool isFinal = false;
	bool isRecursive = false;
	bool isStatic = false;
	std::string languageFeature;
	MethodAttributes::MethodType::E methodType = MethodAttributes::MethodType::Function;
	Mutability::E mutability = Mutability::Const;	// extreme const correctness: all methods are const by default
	std::string name;
	int numConstModifiers = 0;
	bool throws = false;
	TypeDeclaration type;
	Runtime::AtomicValue value = 0;
	Visibility::E visibility;


	// look for the visibility token
	visibility = Visibility::convert((*token++).content());
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the type token
	type = Parser::parseTypeDeclaration(token);
	// look for the identifier token
	name = (*token++).content();

	if ( token->type() == Token::Type::PARENTHESIS_OPEN ) {
		BluePrintGeneric* blueprint = dynamic_cast<BluePrintGeneric*>(mScope);
		if ( blueprint && name == RESERVED_WORD_CONSTRUCTOR ) {
			// these methods have the same name as their containing object,
			// so this has to be a constructor or a destructor;
			// they can never ever be const, ever
			methodType = MethodAttributes::MethodType::Constructor;
			mutability = Mutability::Modify;
		}
		else if ( blueprint && name == RESERVED_WORD_DESTRUCTOR ) {
			// these methods have the same name as their containing object,
			// so this has to be a constructor or a destructor;
			// they can never ever be const, ever
			methodType = MethodAttributes::MethodType::Destructor;
			mutability = Mutability::Modify;
		}

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

					if ( !blueprint ) {
						throw Common::Exceptions::NotSupported("global methods cannot be declared as abstract", token->position());
					}
				}
				else if ( token->content() == MODIFIER_CONST ) {
					mutability = Mutability::Const;
					numConstModifiers++;
				}
				else if ( token->content() == MODIFIER_FINAL ) {
					isFinal = true;
					//mutability = Mutability::Final;
					//numConstModifiers++;

					if ( !blueprint ) {
						throw Common::Exceptions::NotSupported("global methods cannot be declared as final", token->position());
					}
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
				}
				else if ( token->content() == MODIFIER_THROWS ) {
					if ( methodType == MethodAttributes::MethodType::Destructor ) {
						OSinfo("exceptions thrown in destructor cannot be caught in " + token->position().toString());
					}

					throws = true;
				}
			}
			else {
				isModifierToken = false;
			}
		} while ( isModifierToken && token->type() != Token::Type::BRACKET_CURLY_OPEN );

		if ( numConstModifiers > 1 ) {
			throw Common::Exceptions::Exception("modifiers 'const' & 'modify' are exclusive", token->position());
		}

		// collect all tokens of this method
		TokenList tokens;
		if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
			if ( mProcessingInterface ) {
				throw Common::Exceptions::SyntaxError("interface methods are not allowed to be implemented", token->position());
			}

			tokens = Parser::collectScopeTokens(token);
		}
		else if ( !isAbstract ) {
			throw Common::Exceptions::SyntaxError("method '" + name + "' is not declared as abstract but has no implementation", token->position());
		}

		// create a new method with the corresponding return value
		Runtime::Method *method = new Runtime::Method(mScope, name, Designtime::Parser::buildConstraintTypename(type.mTypename, type.mConstraints));
		method->setAbstract(isAbstract || mProcessingInterface);
		method->setFinal(isFinal);
		method->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
		method->setMethodType(methodType);
		method->setMutability(mutability);
		method->setParent(mScope);
		method->setPrototypeConstraints(type.mConstraints);
		method->setRecursive(isRecursive);
		method->setSignature(params);
		method->setStatic(isStatic);
		method->setThrows(throws);
		method->setTokens(tokens);
		method->setVisibility(visibility);

		mScope->defineMethod(name, method);
	}
	else {
		// look for a mutability keyword
		if ( token->category() == Token::Category::Modifier ) {
			mutability = Mutability::convert(token->content());

			if ( token->content() == MODIFIER_FINAL ) {
				isFinal = true;
			}

			token++;
		}
		else {
			mutability = Mutability::Modify;
		}

		if ( token->type() == Token::Type::ASSIGN ) {
			token++;

			value = Parser::parseValueInitialization(token);

			token++;
		}

		expect(Token::Type::SEMICOLON, token);

		if ( dynamic_cast<BluePrintGeneric*>(mScope) ){
			BluePrintObject* blue = new BluePrintObject(type.mTypename, mFilename, name);
			blue->setFinal(isFinal);
			blue->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
			blue->setMember(true);
			blue->setMutability(mutability);
			blue->setParent(mScope);
			blue->setPrototypeConstraints(type.mConstraints);
			blue->setQualifiedTypename(type.mTypename);
			blue->setValue(value);
			blue->setVisibility(visibility);

			mScope->define(name, blue);
		}
		else {
			Runtime::Object *member = mRepository->createInstance(type.mTypename, name, type.mConstraints, false);
			member->setFinal(isFinal);
			member->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
			member->setMember(true);
			member->setMutability(mutability);
			member->setParent(mScope);
			member->setQualifiedTypename(type.mTypename);
			member->setValue(value);
			member->setVisibility(visibility);

			mScope->define(name, member);
		}
	}

	return true;
}

bool Analyser::createMethod(TokenIterator& token, TokenIterator /*end*/)
{
	bool isAbstract = mProcessingInterface;
	bool isFinal = false;
	bool isRecursive = false;
	bool isStatic = false;
	std::string languageFeature;
	MethodAttributes::MethodType::E methodType = MethodAttributes::MethodType::Function;
	Mutability::E mutability = Mutability::Const;	// extreme const correctness: all methods are const by default
	std::string name;
	int numConstModifiers = 0;
	bool throws = false;
	TypeDeclaration type;
	Visibility::E visibility;

	// look for the visibility token
	visibility = Visibility::convert((*token++).content());
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the type token
	type = Parser::parseTypeDeclaration(token);
	// look for the identifier token
	name = (*token++).content();

	BluePrintGeneric* blueprint = dynamic_cast<BluePrintGeneric*>(mScope);
	if ( blueprint && name == RESERVED_WORD_CONSTRUCTOR ) {
		// these methods have the same name as their containing object,
		// so this has to be a constructor or a destructor;
		// they can never ever be const, ever
		methodType = MethodAttributes::MethodType::Constructor;
		mutability = Mutability::Modify;
	}
	else if ( blueprint && name == RESERVED_WORD_DESTRUCTOR ) {
		// these methods have the same name as their containing object,
		// so this has to be a constructor or a destructor;
		// they can never ever be const, ever
		methodType = MethodAttributes::MethodType::Destructor;
		mutability = Mutability::Modify;
	}

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

				if ( !blueprint ) {
					throw Common::Exceptions::NotSupported("global methods cannot be declared as abstract", token->position());
				}
			}
			else if ( token->content() == MODIFIER_CONST ) {
				mutability = Mutability::Const;
				numConstModifiers++;
			}
			else if ( token->content() == MODIFIER_FINAL ) {
				isFinal = true;
				//mutability = Mutability::Final;
				//numConstModifiers++;

				if ( !blueprint ) {
					throw Common::Exceptions::NotSupported("global methods cannot be declared as final", token->position());
				}
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
			}
			else if ( token->content() == MODIFIER_THROWS ) {
				if ( methodType == MethodAttributes::MethodType::Destructor ) {
					OSinfo("exceptions thrown in destructor cannot be caught in " + token->position().toString());
				}

				throws = true;
			}
		}
		else {
			isModifierToken = false;
		}
	} while ( isModifierToken && token->type() != Token::Type::BRACKET_CURLY_OPEN );

	if ( numConstModifiers > 1 ) {
		throw Common::Exceptions::Exception("modifiers 'const' & 'modify' are exclusive", token->position());
	}

	// collect all tokens of this method
	TokenList tokens;
	if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
		if ( mProcessingInterface ) {
			throw Common::Exceptions::SyntaxError("interface methods are not allowed to be implemented", token->position());
		}

		tokens = Parser::collectScopeTokens(token);
	}
	else if ( !isAbstract ) {
		throw Common::Exceptions::SyntaxError("method '" + name + "' is not declared as abstract but has no implementation", token->position());
	}

	// create a new method with the corresponding return value
	Runtime::Method *method = new Runtime::Method(mScope, name, type.mTypename);
	method->setAbstract(isAbstract || mProcessingInterface);
	method->setFinal(isFinal);
	method->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	method->setMethodType(methodType);
	method->setMutability(mutability);
	method->setParent(mScope);
	method->setRecursive(isRecursive);
	method->setSignature(params);
	method->setStatic(isStatic);
	method->setThrows(throws);
	method->setTokens(tokens);
	method->setVisibility(visibility);

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
					throw Common::Exceptions::Exception("cannot extend non-namespace symbol '" + symbol->getName() + "'", token->position());
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
			createLibraryReference(it, tokens.end());
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
		else {
			createMemberOrMethod(it, tokens.end());
			//throw Common::Exceptions::SyntaxError("invalid token '" + it->content() + "' found", it->position());
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

	// execute basic sanity checks
	SanityChecker sanity;
	sanity.process(tokens);

	// generate objects from tokens
	generate(tokens);
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
	process(tokens);
}

void Analyser::processString(const std::string& content, const std::string& filename)
{
	mFilename = filename;

	// create token list from string
	TokenList tokens = generateTokens(content);

	// start the real processing
	process(tokens);
}

void Analyser::processTokens(const TokenList& tokens)
{
	// start the real processing
	process(tokens);
}


}
}
