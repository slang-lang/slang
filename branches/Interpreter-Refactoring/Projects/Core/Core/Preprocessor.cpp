
// Header
#include "Preprocessor.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Designtime/BluePrintEnum.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/VirtualMachine/Controller.h>
#include "Tokenizer.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Preprocessor::Preprocessor()
: mBluePrint(0),
  mScope(0)
{
}

/*
 * Replaces all 'scoped' tokens with 'concatenated' tokens
 */
bool Preprocessor::buildQualifiedNames(TokenIteratorMutable& token, bool skipFirstToken)
{
	if ( !skipFirstToken ) {
		expect(Token::Type::VISIBILITY, token++);
	}

	std::string type = token->content();
	bool update = false;

	while ( token->type() == Token::Type::IDENTIFER ) {
		if ( lookahead(token)->type() != Token::Type::SCOPE ) {
			break;
		}

		// erase token
		token = mTokens.erase(token);

		// add scope token to type definition
		type += ".";

		// erase scope token
		token = mTokens.erase(token);

		// add next token to type definition
		type += (token)->content();
	}

	// only update token if something has changed
	if ( token->content() != type ) {
		token->resetContentTo(type);
		token->resetTypeTo(Token::Type::TYPE);

		update = true;
	}

	return update;
}

Designtime::BluePrintObject* Preprocessor::createMember(TokenIterator token) const
{
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

	if ( visibility == Visibility::Public ) {
		// beware: public members are deprecated, remember the "Law of Demeter"
		// consider using wrappers (getter, setter) instead of directly providing access to members for outsiders
		// haven't you heard? outsiders, or sometimes called strangers, are evil
		throw Designtime::Exceptions::LawOfDemeterViolated("public member " + name + " violates \"Law of Demeter\"", token->position());
	}

	// look for a mutability token
	if ( token->category() == Token::Category::Modifier ) {
		mutability = Mutability::convert((*token).content());

		if ( (*token).content() == MODIFIER_FINAL ) {
			isFinal = true;
		}

		token++;
	}

	// look for an assignment token
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

	Designtime::BluePrintObject* blue = new Designtime::BluePrintObject(type, mFilename, name);
	blue->setFinal(isFinal);
	blue->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	blue->setMutability(mutability);
	blue->setMember(true);		// every object created here is a member object
	blue->setParent(mScope);
	blue->setQualifiedTypename(type);
	blue->setValue(value);
	blue->setVisibility(visibility);

	return blue;
}

Runtime::Method* Preprocessor::createMethod(TokenIterator token) const
{
	Designtime::BluePrintObject* blueprint = static_cast<Designtime::BluePrintObject*>(mBluePrint);

	bool isAbstract = false;
	bool isFinal = false;
	bool isRecursive = false;
	bool isStatic = true;
	MethodAttributes::MethodType::E methodType = MethodAttributes::MethodType::Method;
	Mutability::E mutability = Mutability::Const;		// extreme const correctness: all methods are const by default
	int numConstModifiers = 0;
	bool throws = false;

	// look for the visibility token
	std::string visibility = (*token++).content();
	// look for an optional language feature token
	LanguageFeatureState::E languageFeatureState = Parser::parseLanguageFeatureState(token, LanguageFeatureState::Stable);
	// look for the type token
	std::string type = Parser::identify(token);
	// look for the identifier token
	std::string name = (*token++).content();

	if ( name == blueprint->Typename() ) {
		// these methods have the same name as their containing object,
		// so this has to be a constructor or a destructor;
		// they can never ever be const, ever
		methodType = MethodAttributes::MethodType::Constructor;
		mutability = Mutability::Modify;
	}
	else if ( name == "~" + blueprint->Typename() ) {
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
			}
			else if ( token->content() == MODIFIER_CONST ) {
				mutability = Mutability::Const;
				numConstModifiers++;
			}
			else if ( token->content() == MODIFIER_FINAL ) {
				isFinal = true;
				//mutability = Mutability::Final;
				//numConstModifiers++;
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

	if ( mutability == Mutability::Const &&
		(methodType == MethodAttributes::MethodType::Constructor || methodType == MethodAttributes::MethodType::Destructor) ) {
		throw Common::Exceptions::SyntaxError("constructor or destructor cannot be const");
	}

	if ( token->type() == Token::Type::RESERVED_WORD && token->content() == RESERVED_WORD_THROWS ) {
		throws = true;
		token++;
	}

	// collect all tokens of this method
	TokenList tokens;
	if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
		tokens = Parser::collectScopeTokens(token);
	}

	if ( (isAbstract || blueprint->isInterface()) && !tokens.empty() ) {
		throw Common::Exceptions::SyntaxError("abstract methods cannot have an implementation");
	}

	Runtime::Method *method = new Runtime::Method(mScope, name, type);
	method->setAbstract(isAbstract || blueprint->isInterface());
	method->setFinal(isFinal);
	method->setLanguageFeatureState(languageFeatureState);
	method->setMethodType(methodType);
	method->setMutability(mutability);
	method->setQualifiedTypename(type);
	method->setRecursive(isRecursive);
	method->setSignature(params);
	method->setStatic(isStatic);
	method->setThrows(throws);
	method->setTokens(tokens);
	method->setVisibility(Visibility::convert(visibility));

	return method;
}

/*
 * Process all enum tokens and create const symbols
 */
void Preprocessor::generateBluePrintEnum()
{
	assert(mBluePrint);
	assert(mBluePrint->getSymbolType() == Symbol::IType::BluePrintEnumSymbol);

	Designtime::BluePrintEnum* blueprint = static_cast<Designtime::BluePrintEnum*>(mBluePrint);

	Designtime::BluePrintObject* symbol = new Designtime::BluePrintObject(blueprint->Typename(), blueprint->Filename(), blueprint->getName());
	symbol->setMutability(blueprint->getMutability());
	symbol->setParent(blueprint->getEnclosingScope());
	symbol->setQualifiedTypename(blueprint->QualifiedTypename());
	symbol->setVisibility(blueprint->getVisibility());

	Controller::Instance().repository()->addBluePrint(symbol, mScope);

	TokenIterator token = mTokens.begin();

	Runtime::AtomicValue previous_value = (unsigned)-1;
	Runtime::AtomicValue value = (unsigned)-1;

	// Format: <identifier> = <value>[, or ;]
	while ( token != mTokens.end() ) {
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
		Runtime::Object* entry = Controller::Instance().repository()->createInstance(Runtime::IntegerObject::TYPENAME, name, true);
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

			if ( lookahead(token) == mTokens.end() ) {
				throw Common::Exceptions::Exception("new enum value expected but none found!", token->position());
			}
		}
		else if ( token->type() == Token::Type::SEMICOLON ) {
			return;
		}
		else {
			throw Common::Exceptions::Exception("unexpected token '" + token->content() + "' found", token->position());
		}
	}
}

void Preprocessor::generateBluePrintObject()
{
	assert(mBluePrint);
	assert(mBluePrint->getSymbolType() == Symbol::IType::BluePrintObjectSymbol);

	Designtime::BluePrintObject* blueprint = static_cast<Designtime::BluePrintObject*>(mBluePrint);

	typedef std::list<TokenIterator> TokenIteratorList;
	TokenIteratorList visList;

	// find all visibility keywords which we use as starting point for our interpreter
	for ( TokenIterator it = mTokens.begin(); it != mTokens.end(); ++it ) {
		if ( it->type() == Token::Type::VISIBILITY ) {
			visList.push_back(it);
		}
	}

	// loop over all visibility declarations and check if we have a member declaration or a method declaration
	for ( TokenIteratorList::const_iterator it = visList.begin(); it != visList.end(); ++it ) {
		if ( Parser::isMemberDeclaration((*it)) || Parser::isMemberDeclarationWithModifier((*it)) ) {
			Designtime::BluePrintObject *member = createMember((*it));

			blueprint->define(member->getName(), member);
		}
		else if ( Parser::isMethodDeclaration((*it)) || Parser::isStructorDeclaration((*it)) ) {
			Runtime::Method *method = createMethod((*it));

			blueprint->defineMethod(method->getName(), method);
		}
		else {
			throw Common::Exceptions::SyntaxError("invalid token '" + (*it)->content() + "'", (*it)->position());
		}
	}
}

void Preprocessor::generateTokens(const std::string& content)
{
	Tokenizer t(mFilename, content);
	t.process();

	mTokens = t.tokens();
}

void Preprocessor::process(Designtime::BluePrintGeneric* blueprint)
{
	assert(blueprint);
	mBluePrint = blueprint;

	mFilename = blueprint->Filename();
	mTokens = blueprint->getTokens();

	switch ( blueprint->getSymbolType() ) {
		case Symbol::IType::BluePrintEnumSymbol: {
			generateBluePrintEnum();	// build enum from tokens
		} break;
		case Symbol::IType::BluePrintObjectSymbol: {
			rebuildBluePrintObject();	// rebuild object tokens
			generateBluePrintObject();	// build object from tokens
		} break;
		default:
			throw Common::Exceptions::Exception("invalid symbol type provided");
	}

	mBluePrint = 0;
}

void Preprocessor::rebuildBluePrintObject()
{
	assert(mBluePrint);

	typedef std::list<TokenIteratorMutable> TokenIteratorList;
	TokenIteratorList visList;

	// find all visibility keywords which we use as starting point for our interpreter
	for ( TokenIteratorMutable it = mTokens.begin(); it != mTokens.end(); ++it ) {
		if ( it->type() == Token::Type::VISIBILITY ) {
			visList.push_back(it);
		}
	}

	for ( TokenIteratorList::iterator it = visList.begin(); it != visList.end(); ++it ) {
		TokenIteratorMutable token = (*it);

		// handle members or method result types
		buildQualifiedNames(token, false);

		// handle parameter types
		while ( token != mTokens.end() && token->type() != Token::Type::SEMICOLON && token->type() != Token::Type::PARENTHESIS_CLOSE ) {
			buildQualifiedNames(token, true);

			if ( token != mTokens.end() ) {
				token++;
			}
		}
	}
}


}
