
// Header
#include "Parser.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Tools.h>
#include <Core/Common/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


bool checkSyntax(TokenIterator foundIt, const TokenList &expected)
{
	if ( expected.empty() ) {
		return false;
	}

	for ( TokenIterator expectedIt = expected.begin(); expectedIt != expected.end(); ++expectedIt, ++foundIt ) {
		if ( expectedIt->isOptional() ) {
			// optional tokens have to be skipped during syntax check
			expectedIt++;
		}
		if ( foundIt->isOptional() ) {
			// optional tokens have to be skipped during syntax check
			foundIt++;
		}

		if ( expectedIt->type() != foundIt->type() ) {
			return false;
		}
		if ( !expectedIt->content().empty() && expectedIt->content() != foundIt->content() ) {
			return false;
		}
	}

	return true;
}


TokenList Parser::collectScopeTokens(TokenIterator& token)
{
	if ( (*token).type() != Token::Type::BRACKET_CURLY_OPEN ) {
		throw Common::Exceptions::Exception("collectScopeTokens: invalid start token found");
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

std::string Parser::identify(TokenIterator& start)
{
	std::string type = start->content();

	while ( (start++)->type() == Token::Type::IDENTIFER ) {
		if ( lookahead(start)->type() != Token::Type::SCOPE ) {
			break;
		}

		// add next token to type definition
		type += (start++)->content();
		type += (start++)->content();
	}

	return type;
}

ImplementationType::E Parser::parseImplementationType(TokenIterator& token, ImplementationType::E defaultValue)
{
	ImplementationType::E result = defaultValue;

	if ( token->isOptional() && token->type() == Token::Type::MODIFIER ) {
		ImplementationType::E value = ImplementationType::convert((*token++).content());

		if ( value != ImplementationType::Unknown ) {
			result = value;
		}
	}

	return result;
}

LanguageFeatureState::E Parser::parseLanguageFeatureState(TokenIterator& token, LanguageFeatureState::E defaultValue)
{
	LanguageFeatureState::E result = defaultValue;

	if ( token->isOptional() && token->type() == Token::Type::LANGUAGEFEATURE ) {
		LanguageFeatureState::E value = LanguageFeatureState::convert((*token++).content());

		if ( value != LanguageFeatureState::Unknown ) {
			result = value;
		}
	}

	return result;
}

ObjectType::E Parser::parseObjectType(TokenIterator& token)
{
	return ObjectType::convert((*token++).content());
}

// enum declaration:
// <visibility> [language feature] enum <identifier> { ... }
bool Parser::isEnumDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_ENUM)));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSyntax(start, tokens);
}

// interface declaration:
// <visibility> [language feature] interface <identifier> { ... }
bool Parser::isInterfaceDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_INTERFACE)));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSyntax(start, tokens);
}

// library declaration:
// import <identifier> ;
bool Parser::isLibraryReference(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_IMPORT)));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSyntax(start, tokens);
}

// syntax:
// <type> <identifier>
bool Parser::isLocalDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSyntax(start, tokens);
}

// syntax:
// <visibility> <type> <identifier> ;
bool Parser::isMemberDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::IDENTIFER));
	tokens.push_back(Token(Token::Type::SEMICOLON));

	return checkSyntax(start, tokens);
}

bool Parser::isMemberDeclarationWithModifier(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::IDENTIFER));
	tokens.push_back(Token(Token::Type::ASSIGN));

	return checkSyntax(start, tokens);
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

	return checkSyntax(start, tokens);
}

// namespace declaration:
// <visibility> [language feature] namespace <identifier> { ... }
bool Parser::isNamespaceDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_NAMESPACE)));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSyntax(start, tokens);
}

// object declaration:
// <visibility> [language feature] object <identifier> [extends <identifier> [implements <identifier>, ...]] { ... }
bool Parser::isObjectDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_OBJECT)));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSyntax(start, tokens);
}

// prototype declaration:
// <visibility> [language feature] prototype <identifier> [extends <identifier> [implements <identifier>, ...]] { ... }
bool Parser::isPrototypeDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_PROTOTYPE)));
	tokens.push_back(Token(Token::Type::IDENTIFER));

	return checkSyntax(start, tokens);
}

// syntax:
// <visibility> <type> <type> (
// used to detect con- or destructor declarations
bool Parser::isStructorDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY));
	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::TYPE));
	tokens.push_back(Token(Token::Type::PARENTHESIS_OPEN));

	return checkSyntax(start, tokens);
}

ParameterList Parser::parseParameters(TokenIterator &token)
{
	ParameterList params;

	while ( (*++token).type() != Token::Type::PARENTHESIS_CLOSE ) {
		if ( !isLocalDeclaration(token) ) {
			throw Common::Exceptions::SyntaxError("could not parse parameter declaration", token->position());
		}

		Parameter::AccessMode::E accessmode = Parameter::AccessMode::ByValue;
		bool hasDefaultValue = false;
		bool isConst = false;
		Runtime::AtomicValue value;

		expect(Token::Type::TYPE, token);

		std::string type = token->content();
		token++;

		std::string name = token->content();
		token++;

		if ( token->content() == MODIFIER_CONST ) {
			isConst = true;
			token++;
		}

		if ( token->content() == RESERVED_WORD_BY_REFERENCE ) {
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

			switch ( token->type() ) {
				case Token::Type::CONST_BOOLEAN: value = Tools::stringToBool(token->content()); break;
				case Token::Type::CONST_DOUBLE: value = Tools::stringToDouble(token->content()); break;
				case Token::Type::CONST_FLOAT: value = Tools::stringToFloat(token->content()); break;
				case Token::Type::CONST_INTEGER: value = Tools::stringToInt(token->content()); break;
				case Token::Type::CONST_LITERAL: value = token->content(); break;
				case Token::Type::CONST_NUMBER: value = Tools::stringToNumber(token->content()); break;
				default: throw Common::Exceptions::NotSupported("only atomic data types are allowed as default parameters", token->position());
			}

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
