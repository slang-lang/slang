
// Header
#include "Parser.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Consts.h>
#include <Core/Interfaces/IScope.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


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



Ancestors Parser::collectInheritance(TokenIterator& token)
{
	Ancestors ancestors;

	if ( token->type() != Token::Type::RESERVED_WORD ) {
		// no reserved word, no ancestors
		return ancestors;
	}

	bool replicates = false;
	Ancestor::Type::E inheritance = Ancestor::Type::Unknown;
	Visibility::E visibility = Visibility::Public;

	for ( ; ; ) {
		if ( token->content() == RESERVED_WORD_EXTENDS ) {
			if ( replicates ) {
				throw Common::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			token++;	// consume token

			inheritance = Ancestor::Type::Extends;
		}
		else if ( token->content() == RESERVED_WORD_IMPLEMENTS ) {
			if ( replicates ) {
				throw Common::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			token++;	// consume token

			inheritance = Ancestor::Type::Implements;
		}
		else if ( token->content() == RESERVED_WORD_REPLICATES ) {
			if ( replicates ) {
				throw Common::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			token++;	// consume token

			replicates = true;
			inheritance = Ancestor::Type::Replicates;
		}
		else if ( token->type() == Token::Type::COMMA ) {
			token++;	// consume token

			continue;
		}

		if ( token->type() != Token::Type::IDENTIFER ) {
			break;
		}

		std::string type = Parser::identify(token);

		ancestors.insert(
			Ancestor(type, inheritance, visibility)
		);
	}

	return ancestors;
}

PrototypeConstraints Parser::collectPrototypeConstraints(TokenIterator& token)
{
	PrototypeConstraints constraints;
	
	if ( token->type() != Token::Type::COMPARE_LESS ) {
		// no '<' token, no constraints
		return constraints;
	}

	token++;

	std::string constraint;
	unsigned int index = 0;
	std::string type;

	while ( token->type() != Token::Type::COMPARE_GREATER ) {
		type = token->content();
		token++;

		if ( token->type() == Token::Type::COLON ) {	// constraint
			token++;

			if ( token->type() == Token::Type::IDENTIFER ) {
				constraint = token->content();
			}
			else if ( token->type() == Token::Type::TYPE ) {
				constraint = token->content();
			}
			else {
				throw Common::Exceptions::SyntaxError("unexpected token '" + token->content() + "' found", token->position());
			}

			token++;
		}

		constraints.push_back(
			PrototypeConstraint(index, type, constraint)
		);

		// cleanup for next iteration
		constraint = "";
		index++;
		type = "";

		if ( lookahead(token)->type() == Token::Type::COMMA ) {
			token++;
		}
	}

	token++;

	return constraints;
}

TokenList Parser::collectScopeTokens(TokenIterator& token)
{
	if ( token->type() != Token::Type::BRACKET_CURLY_OPEN ) {
		throw Common::Exceptions::Exception("collectScopeTokens: invalid start token found");
	}

	int scope = 0;
	TokenList tokens;

	// look for the corresponding closing curly bracket
	while ( (++token)->type() != Token::Type::BRACKET_CURLY_CLOSE || scope > 0 ) {
		if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
			scope++;
		}
		if ( token->type() == Token::Type::BRACKET_CURLY_CLOSE ) {
			scope--;
		}

		tokens.push_back((*token));
	}

	return tokens;
}

std::string Parser::identify(TokenIterator& token)
{
	std::string type = token->content();

	while ( (token++)->type() == Token::Type::IDENTIFER ) {
		if ( token->type() != Token::Type::SCOPE ) {
			break;
		}

		// add next token to type definition
		type += (token++)->content();
		type += token->content();
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
	if ( token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		token++;
	}

	if ( token->isOptional() ) {
		// language feature is okay
		token++;
	}

	while ( token->type() == Token::Type::IDENTIFER ) {
		// identifier token is okay
		token++;

		if ( token->type() == Token::Type::SCOPE ) {
			// scope token is okay
			token++;
			continue;
		}
	}

	if ( token->type() == Token::Type::TYPE ) {
		// type is okay
		token++;
	}

	if ( token->type() == Token::Type::IDENTIFER ) {
		// name is okay
		token++;
	}

	if ( token->isOptional() ) {
		// modifier is okay
		token++;
	}

	if ( token->type() != Token::Type::ASSIGN && token->type() != Token::Type::SEMICOLON ) {
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
	if ( token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		token++;
	}

	if ( token->isOptional() ) {
		// language feature is okay
		token++;
	}

	while ( token->type() == Token::Type::IDENTIFER ) {
		token++;

		if ( token->type() == Token::Type::SCOPE ) {
			token++;
			continue;
		}
	}

	if ( token->type() == Token::Type::TYPE ) {
		// type is okay
		token++;
	}

	if ( token->category() == Token::Category::Modifier ) {
		// modifier is okay
		token++;
	}

	if ( token->type() == Token::Type::IDENTIFER ) {
		// name is okay
		token++;
	}

	if ( token->type() != Token::Type::PARENTHESIS_OPEN ) {
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

ParameterList Parser::parseParameters(TokenIterator &token, IScope* scope)
{
(void)scope;	// scope would allow a namespace resolution

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
			// type has already been set
			// set default access mode for complex types
			accessmode = Parameter::AccessMode::ByReference;
		}
		else if ( token->type() == Token::Type::TYPE ) {
			// combine type with already gathered type
			type += token->content();
			// set default access mode for atomic parameters
			accessmode = Parameter::AccessMode::ByValue;
		}
		else {
			throw Common::Exceptions::SyntaxError("unexpected token '" + token->content() + "' found", token->position());
		}

		token++;

		// collect prototype constraints (if present)
		PrototypeConstraints constraints = Parser::collectPrototypeConstraints(token);

		std::string name = token->content();
		token++;

		if ( token->category() == Token::Category::Modifier ) {
			if ( token->content() == MODIFIER_CONST ) {
				isConst = true;
				token++;
			}
			else if ( token->content() == MODIFIER_MODIFY ) {
				isConst = false;
				token++;
			}
			else {
				throw Common::Exceptions::SyntaxError("unexpected modifier '" + token->content() + "' found", token->position());
			}
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

			value = parseValueInitialization(token);

			token++;
		}

		if ( hasDefaultValue && accessmode == Parameter::AccessMode::ByReference ) {
			// parameters with default values cannot be accessed by reference
			throw Common::Exceptions::SyntaxError("default parameters are not allowed to be accessed by reference");
		}

		params.push_back(
			Parameter(name, type, value, hasDefaultValue, isConst, accessmode, Reference())
		);

		type = "";	// reset type for next iteration

		if ( token->type() == Token::Type::PARENTHESIS_CLOSE ) {
			break;
		}
	}

	return params;
}

Runtime::AtomicValue Parser::parseValueInitialization(TokenIterator& token)
{
	Runtime::AtomicValue value;
	std::string sign;

	if ( token->type() == Token::Type::MATH_SUBTRACT ) {
		sign += "-";
		token++;
	}

	switch ( token->type() ) {
		case Token::Type::CONST_BOOLEAN:
			if ( !sign.empty() ) {
				throw Common::Exceptions::SyntaxError("unexpected token", token->position());
			}

			value = Tools::stringToBool(token->content());
			break;
		case Token::Type::CONST_DOUBLE:
			value = Tools::stringToDouble(sign + token->content());
			break;
		case Token::Type::CONST_FLOAT:
			value = Tools::stringToFloat(sign + token->content());
			break;
		case Token::Type::CONST_INTEGER:
			value = Tools::stringToInt(sign + token->content());
			break;
		case Token::Type::CONST_LITERAL:
			if ( !sign.empty() ) {
				throw Common::Exceptions::SyntaxError("unexpected token", token->position());
			}

			value = token->content();
			break;
		case Token::Type::CONST_NUMBER:
			return Tools::stringToNumber(sign + token->content());
			break;
		default:
			throw Common::Exceptions::NotSupported("only atomic data types are allowed as default parameters", token->position());
	}

	return value;
}


}
}