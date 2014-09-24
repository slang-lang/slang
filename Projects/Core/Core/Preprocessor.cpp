
// Header
#include "Preprocessor.h"

// Library includes

// Project includes
#include "Exceptions.h"
#include "Object.h"
#include "Tokenizer.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Object Preprocessor::createMemberObject(const std::string& filename, TokenIterator token)
{
//	bool isConst = false;
//	bool isStatic = false;
	std::string name;
	std::string type;
	std::string value;
	std::string visibility;

	// look for the visibility token
	visibility = (*token++).content();
	// look for the type token
	type = (*token++).content();
	// look for the identifier token
	name = (*token++).content();

	if ( (*token).type() != Token::Type::SEMICOLON ) {
		throw Exception("Member initialisation not allowed at this point", token->position());
	}

	// create member variable
	Object o(name, filename, type, value);
//	o.setConst(isConst);
//	o.setStatic(isStatic);
	o.visibility(Visibility::convert(visibility));
	return o;
}

Method Preprocessor::createMethod(TokenIterator token)
{
	bool isConst = false;
	bool isStatic = false;
	std::string name;
	std::string type;
	std::string value;
	std::string visibility;

	// look for the visibility token
	visibility = (*token++).content();
	// look for the type token
	type = (*token++).content();
	// look for the identifier token
	name = (*token).content();

	// look for the next opening parenthesis
	do { token++; } while ( (*token).type() != Token::Type::PARENTHESIS_OPEN );

	VariablesList params;

	// look for the next closing parenthesis
	// and create parameters
	while ( (*++token).type() != Token::Type::PARENTHESIS_CLOSE ) {
		if ( isLocalDeclaration(token) ) {
			// try to create parameter objects
			bool isConst = false;
			std::string name;
			std::string type = token->content();

			do {
				token++;

				if ( token->type() == Token::Type::IDENTIFER ) {
					name = token->content();
				}
				else if ( token->type() == Token::Type::RESERVED ) {
					if ( token->content() == "const" ) {
						isConst = true;
					}
					else if ( token->content() == "static" ) {
						throw Exception("static parameter declarations not allowed", token->position());
					}
				}
			//} while ( token->type() != Token::Type::IDENTIFER );
			} while ( token->type() != Token::Type::COLON && token->type() != Token::Type::PARENTHESIS_CLOSE );

			Object o(name, "", type, "");
			//o.setConst(isConst);
			params.push_back(o);

			if ( token->type() == Token::Type::PARENTHESIS_CLOSE ) {
				break;
			}
		}
	}

	// collect all tokens of this method
	TokenList tokens;

	// look at possible attributes (const, static, etc.)
	// look for the next opening curly bracket
	do {
		token++;

		if ( token->type() == Token::Type::RESERVED ) {
			if ( token->content() == "const" ) {
				isConst = true;
			}
			else if ( token->content() == "static" ) {
				isStatic = true;
			}
		}
	} while ( token->type() != Token::Type::BRACKET_CURLY_OPEN );

	int scope = 0;
	// look for the corresponding closing curly bracket
	while ( (*++token).type() != Token::Type::BRACKET_CURLY_CLOSE || scope > 0 ) {
		if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
			scope++;
		}
		if ( token->type() == Token::Type::BRACKET_CURLY_CLOSE ) {
			scope--;
		}

		tokens.push_back((*token));
	}

	if ( isConst && isStatic ) {
		throw Exception("static methods can not be const!");
	}

	// create a new Method with the corresponding return value
	Method m(name, type);
	m.setConst(isConst);
	m.setSignature(params);
	m.setStatic(isStatic);
	m.setTokens(tokens);
	m.visibility(visibility);

	return m;
}

void Preprocessor::generateObject(Object *object)
{
	assert(object);

	typedef std::list<TokenIterator> TokenList;
	TokenList visList;

	// find all visibility keywords which we use
	// as starting point for our interpreter
	for ( TokenIterator it = mTokens.begin(); it != mTokens.end(); ++it ) {
		if ( (*it).type() == Token::Type::VISIBILITY ) {
			visList.push_back(it);
		}
	}

	// if we don't find anything our script file is invalid
	if ( visList.empty() ) {
		os_error("'" + object->name() + "' has no visibility declarations!");
		return;
	}

	// loop over all visibility declarations and check
	// if we have a member declaration or a method declaration
	for ( TokenList::const_iterator it = visList.begin(); it != visList.end(); ++it ) {
		if ( isMemberDeclaration((*it)) ) {
			object->addMember(createMemberObject(object->filename(), (*it)));
		}
		else if ( isMethodDeclaration((*it)) ) {
			object->addMethod(createMethod((*it)));
		}
/*
		else {
			os_error("synthax error: looks like a member or method declaration but is none");
			return;
		}
*/
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
	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::IDENTIFER));
	tokens.push_back(Token(Token::Type::PARENTHESIS_OPEN));

	return checkSynthax(start, tokens);
}

// syntax:
// <visibility> object <identifier> [extends <indentifier> [, <identifier>, ...]]
bool Preprocessor::isObjectDeclaration(TokenIterator start)
{
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}
	if ( (*start).type() != Token::Type::TYPE && (*start++).content() != "object" ) {
		return false;
	}
	if ( (*start++).type() != Token::Type::VISIBILITY ) {
		return false;
	}

	return true;
}

void Preprocessor::process(Object *object)
{
	os_debug("process('" + object->name() + "')");

	mTokens = object->getTokens();

	// build object from tokens
	generateObject(object);
}


}
