
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
		if ( (start)->type() != Token::Type::SCOPE ) {
			break;
		}

		// add next token to type definition
		type += (start++)->content();
		type += (start)->content();
	}

	return type;
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

// member declaration:
// <visibility> [language feature] <identifier> <identifier> = || ;
bool Parser::isMemberDeclaration(TokenIterator token)
{
	if ( (token)->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		token++;
	}

	if ( (token)->isOptional() ) {
		// language feature is okay
		token++;
	}

	while ( (token)->type() == Token::Type::IDENTIFER ) {
		// identifier token is okay
		token++;

		if ( (token)->type() == Token::Type::SCOPE ) {
			// scope token is okay
			token++;
			continue;
		}
	}

	if ( (token)->type() == Token::Type::TYPE ) {
		// type is okay
		token++;
	}

	if ( (token)->type() == Token::Type::IDENTIFER ) {
		// name is okay
		token++;
	}

	if ( (token)->isOptional() ) {
		// modifier is okay
		token++;
	}

	if ( (token)->type() != Token::Type::ASSIGN && (token)->type() != Token::Type::SEMICOLON ) {
		// no assignment and no semicolon
		return false;
	}

	return true;
}

// syntax:
// <visibility> <type> <identifier> (
// <visibility> <identifier> <identifier> (
bool Parser::isMethodDeclaration(TokenIterator token)
{
	if ( (token)->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		token++;
	}

	if ( (token)->isOptional() ) {
		// language feature is okay
		token++;
	}

	while ( (token)->type() == Token::Type::IDENTIFER ) {
		token++;

		if ( (token)->type() == Token::Type::SCOPE ) {
			token++;
			continue;
		}
	}

	if ( (token)->type() == Token::Type::TYPE ) {
		// type is okay
		token++;
	}

	if ( (token)->type() == Token::Type::IDENTIFER ) {
		// name is okay
		token++;
	}

	if ( (token)->type() != Token::Type::PARENTHESIS_OPEN ) {
		// no open parenthesis
		return false;
	}

	return true;
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

// syntax:
// <identifier> <identifier>
bool Parser::isParameterDeclaration(TokenIterator start)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::IDENTIFER));
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

ParameterList Parser::parseParameters(TokenIterator &token)
{
	ParameterList params;

	std::string type;

	while ( (*++token).type() != Token::Type::PARENTHESIS_CLOSE ) {
		if ( token->type() == Token::Type::IDENTIFER ) {
			type += token->content();

			if ( lookahead(token)->type() == Token::Type::SCOPE ) {
				token++;
				type += ".";
				continue;
			}
		}

		if ( !isLocalDeclaration(token) && !isParameterDeclaration(token) ) {
			throw Common::Exceptions::SyntaxError("could not parse parameter declaration", token->position());
		}

		Parameter::AccessMode::E accessmode = Parameter::AccessMode::ByValue;
		bool hasDefaultValue = false;
		bool isConst = false;
		Runtime::AtomicValue value;

		if ( token->type() == Token::Type::IDENTIFER ) {
			// already set type
		}
		else if ( token->type() == Token::Type::TYPE ) {
			// combine type with already gathered type
			type += token->content();
		}
		else {
			throw Common::Exceptions::SyntaxError("unexpected token '" + token->content() + "' found", token->position());
		}

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

		Parameter param(name, type, value, hasDefaultValue, isConst, accessmode, Reference());
		params.push_back(param);

		type = "";	// reset type for next parameter

		if ( token->type() == Token::Type::PARENTHESIS_CLOSE ) {
			break;
		}
	}

	return params;
}


}
