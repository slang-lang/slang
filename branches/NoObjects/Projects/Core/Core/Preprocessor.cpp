
// Header
#include "Preprocessor.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Object.h"
#include "Repository.h"
#include "Tokenizer.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Preprocessor::Preprocessor(Repository *repo)
: mObject(0),
  mRepository(repo)
{
}

Object* Preprocessor::createMember(const std::string& filename, TokenIterator token)
{
	std::string name;
	std::string type;
	std::string visibility;
	bool isConst = false;
	bool isFinal = false;
	bool isStatic = false;

	// look for the visibility token
	visibility = (*token++).content();
	// look for the type token
	type = (*token++).content();
	// look for the identifier token
	name = (*token++).content();

	if ( (*token).isOptional() ) {
		if ( (*token).content() == "const" ) {
			isConst = true;
		}
		else if ( (*token).content() == "final" ) {
			isFinal = true;
		}
		else if ( (*token).content() == "modify" ) {
			isConst = false;
		}
		else if ( (*token).content() == "static" ) {
			isStatic = true;
		}

		token++;
	}

	if ( (*token).type() != Token::Type::SEMICOLON ) {
		throw Utils::Exception("member initialization not allowed during declaration", token->position());
	}

	Object *o = mRepository->createObject(name, filename, type, "");
	o->setConst(isConst);
	o->setFinal(isFinal);
	o->setStatic(isStatic);
	o->setVisibility(Visibility::convert(visibility));
	return o;
}

Method* Preprocessor::createMethod(TokenIterator token)
{
	bool isConst = false;		// set to 'true' to make all methods const by default (this is the only way the 'modify' attribute makes sense)
	bool isFinal = false;
	bool isStatic = false;
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

	// look for the next opening parenthesis
	do { token++; } while ( (*token).type() != Token::Type::PARENTHESIS_OPEN );

	ParameterList params = parseParameters(token);

	// look at possible attributes (const, modify, static, etc.)
	// look for the next opening curly bracket
	do {
		token++;

		if ( token->type() == Token::Type::LANGUAGEFEATURE ) {
			if ( token->content() == "const" ) {
				isConst = true;
			}
			else if ( token->content() == "final" ) {
				isFinal = false;
			}
			else if ( token->content() == "modify" ) {
				isConst = false;
			}
			else if ( token->content() == "static" ) {
				isStatic = true;
			}
		}
	} while ( token->type() != Token::Type::BRACKET_CURLY_OPEN );

	if ( (isConst || isFinal) && isStatic ) {
		throw Utils::Exception("static methods can not be const!");
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

	// create a new Method with the corresponding return value
	Method *m = new Method(mObject, name, type);
	m->setConst(isConst);
	m->setFinal(isFinal);
	m->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	m->setSignature(params);
	m->setStatic(isStatic);
	m->setTokens(tokens);
	m->visibility(Visibility::convert(visibility));

	return m;
}

void Preprocessor::generateObject()
{
	assert(mObject);

	typedef std::list<TokenIterator> TokenList;
	TokenList visList;

	// find all visibility keywords which we use
	// as starting point for our interpreter
	for ( TokenIterator it = mTokens.begin(); it != mTokens.end(); ++it ) {
		if ( it->type() == Token::Type::VISIBILITY ) {
			visList.push_back(it);
		}
	}

	// loop over all visibility declarations and check
	// if we have a member declaration or a method declaration
	for ( TokenList::const_iterator it = visList.begin(); it != visList.end(); ++it ) {
		if ( isMemberDeclaration((*it)) ) {
			mObject->addMember(createMember(mObject->Filename(), (*it)));
		}
		else if ( isMethodDeclaration((*it)) ) {
			mObject->addMethod(createMethod((*it)));
		}
	}
}

void Preprocessor::generateTokens(const std::string& content)
{
	Tokenizer t(content);
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
			throw Utils::SyntaxError("could not parse parameter declaration!", token->position());
		}

		Parameter::AccessMode::E accessmode = Parameter::AccessMode::ByValue;
		bool hasDefaultValue = false;
		bool isConst = false;
		std::string value;

		std::string type = token->content();
		token++;

		std::string name = token->content();
		token++;

		if ( token->content() == "const" ) {
			isConst = true;
			token++;
		}

		if ( token->content() == "ref" ) {
			accessmode = Parameter::AccessMode::ByReference;
			token++;
		}
		else if ( token->content() == "val" ) {
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

void Preprocessor::process(Object *object)
{
	//OSdebug("process('" + object->name() + "')");

	mObject = object;
	mTokens = mObject->getTokens();

	// build object from tokens
	generateObject();
}


}
