
// Header
#include "Parser.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


TokenList Parser::collectScopeTokens(TokenIterator& token)
{
	if ( (*token).type() != Token::Type::BRACKET_CURLY_OPEN ) {
		throw Utils::Exceptions::Exception("collectScopeTokens: invalid start token found");
	}

	int scope = 0;
	TokenList tokens;

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

	return tokens;
}

// interface declaration:
// <visibility> [language feature] interface <identifier> { ... }
bool Parser::isInterfaceDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_INTERFACE)));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSynthax(start, tokens);
}

// library declaration:
// import <identifier> ;
bool Parser::isLibraryReference(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_IMPORT)));
	tokens.push_back(Token(Token::Type::IDENTIFER));
	//tokens.push_back(Token(Token::Type::SCOPE, true));
	//tokens.push_back(Token(Token::Type::IDENTIFER, true));
	//tokens.push_back(Token(Token::Type::SEMICOLON));

	return checkSynthax(start, tokens);
}

// syntax:
// <type> <identifier>
bool Parser::isLocalDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSynthax(start, tokens);
}

// syntax:
// <visibility> <type> <identifier> ;
bool Parser::isMemberDeclaration(TokenIterator start)
{
	// initialization is not allowed during member creation

	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::IDENTIFER));
	//tokens.push_back(Token(Token::Type::LANGUAGEFEATURE, true));
	//tokens.push_back(Token(Token::Type::ASSIGN, true));
	//tokens.push_back(Token(Token::Type::IDENTIFER, true));
	tokens.push_back(Token(Token::Type::SEMICOLON));

	return checkSynthax(start, tokens);
}

// syntax:
// <visibility> <type> <identifier> (
bool Parser::isMethodDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::IDENTIFER));
	tokens.push_back(Token(Token::Type::PARENTHESIS_OPEN));

	return checkSynthax(start, tokens);
}

// namespace declaration:
// <visibility> [language feature] namespace <identifier> { ... }
bool Parser::isNamespaceDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_NAMESPACE)));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSynthax(start, tokens);
}

// object declaration:
// <visibility> [language feature] object <identifier> [extends <identifier> [implements <identifier>, ...]] { ... }
bool Parser::isObjectDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_OBJECT)));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSynthax(start, tokens);
}

// syntax:
// <type> <identifier>
bool Parser::isParameterDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::IDENTIFER));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSynthax(start, tokens);
}

// prototype declaration:
// <visibility> [language feature] prototype <identifier> [extends <identifier> [implements <identifier>, ...]] { ... }
bool Parser::isPrototypeDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_PROTOTYPE)));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSynthax(start, tokens);
}

ParameterList Parser::parseParameters(TokenIterator &token)
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


}
