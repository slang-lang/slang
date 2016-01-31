
// Header
#include "Preprocessor.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Object.h"
#include "Repository.h"
#include "Scope.h"
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

Designtime::BluePrint* Preprocessor::createMember(TokenIterator token)
{
	std::string name;
	std::string type;
	std::string visibility;
	bool isConst = false;
	bool isFinal = false;

	// look for the visibility token
	visibility = (*token++).content();
	// look for the type token
	type = (*token++).content();
	// look for the identifier token
	name = (*token++).content();

	if ( (*token).isOptional() ) {
		if ( (*token).content() == MODIFIER_CONST ) {
			isConst = true;
		}
		else if ( (*token).content() == MODIFIER_FINAL ) {
			isFinal = true;
		}
		else if ( (*token).content() == MODIFIER_MODIFY ) {
			isConst = false;
		}

		token++;
	}

	if ( (*token).type() != Token::Type::SEMICOLON ) {
		throw Utils::Exceptions::Exception("member initialization not allowed during declaration", token->position());
	}

	Designtime::BluePrint* blue = new Designtime::BluePrint(type, mFilename, name);
	blue->setConst(isConst);
	blue->setFinal(isFinal);
	blue->setMember(true);		// every object created here is a member object
	blue->setVisibility(Visibility::convert(visibility));

	return blue;
}

Runtime::Method* Preprocessor::createMethod(TokenIterator token)
{
	bool isAbstract = false;
	bool isConst = true;		// all methods are const by default (this is the only way the 'modify' attribute makes sense)
	bool isStructor = false;
	bool isFinal = false;
	std::string name;
	std::string languageFeature;
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
	name = (*token).content();

	if ( name == mBluePrint->Typename() ||
		 name == "~" + mBluePrint->Typename() ) {
		// these methods have the same name as their containing object,
		// so this has to be a constructor or a destructor;
		// they can never ever be const
		isConst = false;
		isStructor = true;
	}

	// look for the next opening parenthesis
	do { token++; } while ( (*token).type() != Token::Type::PARENTHESIS_OPEN );

	ParameterList params = parseParameters(token);

	// look at possible attributes (const, final, modify, static, etc.)
	// while looking for the next opening curly bracket
	do {
		token++;

		if ( token->category() == Token::Category::Modifier ) {
			if ( token->content() == MODIFIER_CONST ) {
				isConst = true;
			}
			else if ( token->content() == MODIFIER_FINAL ) {
				isFinal = false;
			}
			else if ( token->content() == MODIFIER_MODIFY ) {
				isConst = false;
			}
		}
	} while ( token->type() != Token::Type::BRACKET_CURLY_OPEN );

	if ( isStructor && isConst ) {
		throw Utils::Exceptions::SyntaxError("constructor or destructor cannot be const");
	}

	// collect all tokens of this method
	TokenList tokens;

	int scope = 0;
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

	// create a new method with the corresponding return value
	Runtime::Method *method = new Runtime::Method(mScope, name, type);
	method->setAbstract(isAbstract);
	method->setConst(isConst);
	method->setFinal(isFinal);
	method->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	method->setRepository(mRepository);
	method->setSignature(params);
	method->setTokens(tokens);
	method->setVisibility(Visibility::convert(visibility));

	return method;
}

void Preprocessor::generateObject()
{
	assert(mBluePrint);

	typedef std::list<TokenIterator> TokenList;
	TokenList visList;

	// find all visibility keywords which we use as starting point for our interpreter
	for ( TokenIterator it = mTokens.begin(); it != mTokens.end(); ++it ) {
		if ( it->type() == Token::Type::VISIBILITY ) {
			visList.push_back(it);
		}
	}

	// loop over all visibility declarations and check if we have a member declaration or a method declaration
	for ( TokenList::const_iterator it = visList.begin(); it != visList.end(); ++it ) {
		if ( isMemberDeclaration((*it)) ) {
			Designtime::BluePrint *member = createMember((*it));

			mBluePrint->define(member->getName(), member);
		}
		else if ( isMethodDeclaration((*it)) ) {
			Runtime::Method *method = createMethod((*it));

			mBluePrint->defineMethod(method);
		}
	}
}

void Preprocessor::generateTokens(const std::string& content)
{
	Tokenizer t(mFilename, content);
	t.process();

	mTokens = t.tokens();
}

// syntax:
// <type> <identifier>
bool Preprocessor::isLocalDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSynthax(start, tokens);
}

// syntax:
// <visibility> <type> <identifier> ;
bool Preprocessor::isMemberDeclaration(TokenIterator start)
{
	// initialization is not allowed during member creation

	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::IDENTIFER));
	tokens.push_back(Token(Token::Type::SEMICOLON));

	return checkSynthax(start, tokens);
}

// syntax:
// <visibility> <type> <identifier> (
bool Preprocessor::isMethodDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	//tokens.push_back(Token(Token::Type::LANGUAGEFEATURE, true)); // this is an optional token
	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::IDENTIFER));
	tokens.push_back(Token(Token::Type::PARENTHESIS_OPEN));

	return checkSynthax(start, tokens);
}

bool Preprocessor::isParameterDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::IDENTIFER));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSynthax(start, tokens);
}

ParameterList Preprocessor::parseParameters(TokenIterator &token)
{
	ParameterList params;

	while ( (*++token).type() != Token::Type::PARENTHESIS_CLOSE ) {
		if ( !isLocalDeclaration(token) && !isParameterDeclaration(token) ) {
			throw Utils::Exceptions::SyntaxError("could not parse parameter declaration", token->position());
		}

		Parameter::AccessMode::E accessmode = Parameter::AccessMode::ByValue;
		bool hasDefaultValue = false;
		bool isConst = false;
		std::string value;

		std::string type = token->content();
		token++;

		std::string name = token->content();
		token++;

		if ( token->content() == MODIFIER_CONST ) {
			isConst = true;
			token++;
		}

		if ( token->content() == RESERVED_WORD_BY_REFERENCE ) {
			if ( isConst ) {
				// const reference parameters are not supported, they won't make sense
				throw Utils::Exceptions::NotSupported("const reference parameters are not supported");
			}

			accessmode = Parameter::AccessMode::ByReference;
			token++;
		}
		else if ( token->content() == RESERVED_WORD_BY_VALUE ) {
			accessmode = Parameter::AccessMode::ByValue;
			token++;
		}

		if ( token->type() == Token::Type::ASSIGN ) {
			hasDefaultValue = true;
			token++;
			value = token->content();
			token++;
		}

		Parameter param(name, type, value, hasDefaultValue, isConst, accessmode, 0);
		params.push_back(param);

		if ( token->type() == Token::Type::PARENTHESIS_CLOSE ) {
			break;
		}
	}

	return params;
}

void Preprocessor::process(Designtime::BluePrint* blueprint)
{
	assert(blueprint);
	mBluePrint = blueprint;

	OSdebug("process('" + mBluePrint->Typename() + "')");

	mFilename = mBluePrint->Filename();
	mTokens = mBluePrint->getTokens();

	// build object from tokens
	generateObject();

	mBluePrint = 0;
}


}
