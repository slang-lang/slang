
// Header
#include "Preprocessor.h"

// Library includes

// Project includes
#include <Core/Designtime/BluePrint.h>
#include <Core/Parser/Parser.h>
#include <Core/Utils/Exceptions.h>
#include "Repository.h"
#include "Tokenizer.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Preprocessor::Preprocessor(Repository *repo)
: mBluePrint(0),
  mRepository(repo),
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

Designtime::BluePrint* Preprocessor::createMember(TokenIterator token) const
{
	bool isFinal = false;
	std::string languageFeature;
	Mutability::E mutability = Mutability::Modify;
	std::string name;
	std::string type;
	Runtime::AtomicValue value = 0;
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

	if ( Visibility::convert(visibility) == Visibility::Public ) {
		// beware: public members are deprecated, remember the "Law of Demeter"
		// consider using wrappers (getter, setter) instead of directly providing access to members to outsiders
		// haven't you heard? outsiders, or sometimes called strangers, are evil
		throw Utils::Exceptions::LawOfDemeterViolated("public member " + name + " violates \"Law of Demeter\"", token->position());
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
			default: throw Utils::Exceptions::NotSupported("initialization is only allowed for atomic data types", token->position());
		}

		token++;
	}

	expect(Token::Type::SEMICOLON, token);

	Designtime::BluePrint* blue = new Designtime::BluePrint(type, mFilename, name);
	blue->setFinal(isFinal);
	blue->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	blue->setMutability(mutability);
	blue->setMember(true);		// every object created here is a member object
	blue->setParent(mScope);
	blue->setQualifiedTypename(type);
	blue->setValue(value);
	blue->setVisibility(Visibility::convert(visibility));

	return blue;
}

Runtime::Method* Preprocessor::createMethod(TokenIterator token) const
{
	bool isAbstract = false;
	bool isConst = true;		// extreme const correctness: all methods are const by default
	bool isFinal = false;
	bool isRecursive = false;
	std::string languageFeature;
	MethodAttributes::MethodType::E methodType = MethodAttributes::MethodType::Method;
	Mutability::E mutability = Mutability::Const;
	std::string name;
	std::string type;
	std::string visibility;
	int numConstModifiers = 0;

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

	if ( name == mBluePrint->Typename() ) {
		// these methods have the same name as their containing object,
		// so this has to be a constructor or a destructor;
		// they can never ever be const, ever
		isConst = false;
		methodType = MethodAttributes::MethodType::Constructor;
		mutability = Mutability::Modify;
	}
	else if ( name == "~" + mBluePrint->Typename() ) {
		// these methods have the same name as their containing object,
		// so this has to be a constructor or a destructor;
		// they can never ever be const, ever
		isConst = false;
		methodType = MethodAttributes::MethodType::Destructor;
		mutability = Mutability::Modify;
	}

	expect(Token::Type::PARENTHESIS_OPEN, token);

	ParameterList params = Parser::parseParameters(token);

	// look at possible attributes (abstract, const, final, modify, etc.)
	// while looking for the next opening curly bracket
	bool isModifierToken = true;
	do {
		token++;

		if ( token->category() == Token::Category::Modifier ) {
			if ( token->content() == MODIFIER_ABSTRACT ) {
				isAbstract = true;
			}
			else if ( token->content() == MODIFIER_CONST ) {
				isConst = true;
				mutability = Mutability::Const;
				numConstModifiers++;
			}
			else if ( token->content() == MODIFIER_FINAL ) {
				isFinal = true;
				//mutability = Mutability::Final;
				//numConstModifiers++;
			}
			else if ( token->content() == MODIFIER_MODIFY ) {
				isConst = false;
				mutability = Mutability::Modify;
				numConstModifiers++;
			}
			else if ( token->content() == MODIFIER_RECURSIVE ) {
				isRecursive = true;
			}
		}
		else {
			isModifierToken = false;
		}
	} while ( isModifierToken && token->type() != Token::Type::BRACKET_CURLY_OPEN );

	if ( numConstModifiers > 1 ) {
		throw Utils::Exceptions::Exception("modifiers 'const' & 'modify' are exclusive");
	}

	if ( isConst &&
		(methodType == MethodAttributes::MethodType::Constructor || methodType == MethodAttributes::MethodType::Destructor) ) {
		throw Utils::Exceptions::SyntaxError("constructor or destructor cannot be const");
	}

	// collect all tokens of this method
	TokenList tokens;
	if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
		tokens = Parser::collectScopeTokens(token);
	}

	if ( isAbstract && !tokens.empty() ) {
		throw Utils::Exceptions::SyntaxError("abstract methods cannot have an implementation");
	}

	// create a new method with the corresponding return value
	Runtime::Method *method = new Runtime::Method(mScope, name, type);
	method->setAbstract(isAbstract || mBluePrint->isInterface());
	method->setFinal(isFinal);
	method->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	method->setMethodType(methodType);
	method->setMutability(mutability);
	method->setRecursive(isRecursive);
	method->setRepository(mRepository);
	method->setSignature(params);
	method->setTokens(tokens);
	method->setVisibility(Visibility::convert(visibility));

	return method;
}

void Preprocessor::generateObject()
{
	assert(mBluePrint);

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
			Designtime::BluePrint *member = createMember((*it));

			mBluePrint->define(member->getName(), member);
		}
		else if ( Parser::isMethodDeclaration((*it)) || Parser::isStructorDeclaration((*it)) ) {
			Runtime::Method *method = createMethod((*it));

			mBluePrint->defineMethod(method->getName(), method);
		}
		else {
			throw Utils::Exceptions::SyntaxError("invalid token '" + (*it)->content() + "' found at " + (*it)->position().toString());
		}
	}
}

void Preprocessor::generateTokens(const std::string& content)
{
	Tokenizer t(mFilename, content);
	t.process();

	mTokens = t.tokens();
}

void Preprocessor::process(Designtime::BluePrint* blueprint)
{
	assert(blueprint);
	mBluePrint = blueprint;

	mFilename = mBluePrint->Filename();
	mTokens = mBluePrint->getTokens();

	// rebuild object tokens
	rebuildObject();

	// build object from tokens
	generateObject();

	mBluePrint = 0;
}

void Preprocessor::rebuildObject()
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
