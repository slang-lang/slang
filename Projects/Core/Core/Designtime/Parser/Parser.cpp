
// Header
#include "Parser.h"

// Library includes

// Project includes
#include <Core/Common/Types.h>
#include <Core/Common/Utils.h>
#include <Core/Consts.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Interfaces/IScope.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace Slang {
namespace Designtime {


bool checkSyntax(TokenIterator foundIt, const TokenList& expected)
{
	if ( expected.empty() ) {
		return false;
	}

	for ( auto expectedIt = expected.begin(); expectedIt != expected.end(); ++expectedIt, ++foundIt ) {
		if ( expectedIt->isOptional() ) {
			// optional tokens have to be skipped during syntax check
			++expectedIt;
		}
		if ( foundIt->isOptional() ) {
			// optional tokens have to be skipped during syntax check
			++foundIt;
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

PrototypeConstraints mergeConstraints(const PrototypeConstraints& designtime, const PrototypeConstraints& runtime)
{
	PrototypeConstraints result;

	if ( designtime.size() != runtime.size() ) {
		throw Exceptions::SyntaxError("prototype constraint size mismatch");
	}

	auto designIt = designtime.begin();
	auto runIt = runtime.begin();

	while ( designIt != designtime.end() ) {
		result.push_back(
			PrototypeConstraint(designIt->mIndex, designIt->mDesignType, runIt->mRunType, designIt->mConstraint)
		);

		++designIt;
		++runIt;
	}

	return result;
}


std::string Parser::buildDesigntimeConstraintTypename(const std::string& name, const PrototypeConstraints& constraints)
{
	if ( constraints.empty() ) {
		return name;
	}

	std::string type = name;
	type += "<";
	for ( auto it = constraints.cbegin(); it != constraints.cend(); ++it ) {
		type += it->mDesignType;

		if ( std::distance(it, constraints.end()) > 1 ) {
			type += ",";
		}
	}
	type += ">";

	return type;
}

std::string Parser::buildRuntimeConstraintTypename(const std::string& name, const PrototypeConstraints& constraints)
{
	if ( constraints.empty() ) {
		return name;
	}

	std::string type = name;
	type += "<";
	for ( auto it = constraints.cbegin(); it != constraints.cend(); ++it ) {
		type += it->mRunType.empty() ? _object : it->mRunType;

		if ( std::distance(it, constraints.end()) > 1 ) {
			type += ",";
		}
	}
	type += ">";

	return type;
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
				throw Exceptions::SyntaxError("combinations with 'replicates' are not allowed");
			}

			++token;	// consume token

			inheritance = Ancestor::Type::Extends;
		}
		else if ( token->content() == RESERVED_WORD_IMPLEMENTS ) {
			if ( replicates ) {
				throw Exceptions::SyntaxError("combinations with 'replicates' are not allowed");
			}

			++token;	// consume token

			inheritance = Ancestor::Type::Implements;
		}
		else if ( token->content() == RESERVED_WORD_REPLICATES ) {
			if ( replicates ) {
				throw Exceptions::SyntaxError("combinations with 'replicates' are not allowed");
			}

			++token;	// consume token

			replicates = true;
			inheritance = Ancestor::Type::Replicates;
		}
		else if ( token->type() == Token::Type::COMMA ) {
			++token;	// consume token

			continue;
		}

		if ( token->type() != Token::Type::IDENTIFIER ) {
			break;
		}

		auto type = identify(token);

		auto constraints = collectDesigntimePrototypeConstraints(token);

/*
		// extending prototypes is not supported right now
		if ( inheritance == Ancestor::Type::Extends && !constraints.empty() ) {
			throw Common::Exceptions::NotSupported("extending prototypes is not supported right now", token->position());
		}
*/

		ancestors.insert(
			Ancestor(Common::TypeDeclaration(type, constraints), inheritance, visibility)
		);
	}

	return ancestors;
}

PrototypeConstraints Parser::collectDesigntimePrototypeConstraints(TokenIterator& token)
{
	PrototypeConstraints constraints;

	if ( token->type() != Token::Type::COMPARE_LESS ) {
		// no '<' token, no constraints
		return constraints;
	}

	++token;

	std::string constraint;
	unsigned int index = 0;

	while ( token->type() != Token::Type::COMPARE_GREATER ) {
		auto designType = token->content();
		auto runType    = token->content();	// hack to prevent runtime type to be empty

		++token;

		if ( token->type() == Token::Type::COLON ) {	// constraint
			++token;

			if ( token->type() == Token::Type::IDENTIFIER ) {
				constraint = token->content();
			}
			else {
				throw Exceptions::SyntaxError("unexpected token '" + token->content() + "' found", token->position());
			}

			++token;
		}

		constraints.push_back(
			PrototypeConstraint(index, designType, runType, constraint)
		);

		// prepare next iteration
		constraint = "";
		++index;

		if ( token->type() == Token::Type::COMMA ) {
			++token;
		}
	}

	expect(Token::Type::COMPARE_GREATER, token);
	++token;

	return constraints;
}

PrototypeConstraints Parser::collectRuntimePrototypeConstraints(TokenIterator& token)
{
	PrototypeConstraints constraints;

	if ( token->type() != Token::Type::COMPARE_LESS ) {
		// no '<' token, no constraints
		return constraints;
	}

	++token;

	std::string constraint;
	std::string designType;
	unsigned int index = 0;

	while ( token->type() != Token::Type::COMPARE_GREATER ) {
		auto runType = token->content();

		++token;

		if ( token->type() == Token::Type::COLON ) {	// constraint
			++token;
		}

		constraints.push_back(
			PrototypeConstraint(index, designType, runType, constraint)
		);

		// prepare next iteration
		constraint = "";
		designType = "";
		++index;

		if ( token->type() == Token::Type::COMMA ) {
			++token;
		}
	}

	expect(Token::Type::COMPARE_GREATER, token);
	++token;

	return constraints;
}

TokenList Parser::collectScopeTokens(TokenIterator& token)
{
	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	int scope = 0;
	TokenList tokens;

	// look for the corresponding closing curly bracket
	while ( (++token)->type() != Token::Type::BRACKET_CURLY_CLOSE || scope > 0 ) {
		if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
			++scope;
		}
		if ( token->type() == Token::Type::BRACKET_CURLY_CLOSE ) {
			--scope;
		}

		tokens.push_back((*token));
	}

	expect(Token::Type::BRACKET_CURLY_CLOSE, token);

	return tokens;
}

std::string Parser::identify(TokenIterator& token)
{
	std::string type = token->content();

	while ( (token++)->type() == Token::Type::IDENTIFIER ) {
		if ( token->type() != Token::Type::OPERATOR_SCOPE ) {
			break;
		}

		// add next token to type definition
		type += token->content();
		type += (++token)->content();
	}

	return type;
}

// enum declaration:
// [<visibility>] [language feature] enum <identifier> { ... }
bool Parser::isEnumDeclaration(TokenIterator token)
{
	TokenList tokens;

	tokens.emplace_back( Token::Type::VISIBILITY, true );
	tokens.emplace_back( Token::Type::RESERVED_WORD, std::string( RESERVED_WORD_ENUM ) );
	tokens.emplace_back( Token::Type::IDENTIFIER );

	return checkSyntax(token, tokens);
}

// interface declaration:
// [<visibility>] [language feature] interface <identifier> [modifier] { ... }
bool Parser::isInterfaceDeclaration(TokenIterator token)
{
	if ( token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		++token;
	}

	if ( token->type() == Token::Type::LANGUAGE_FEATURE_STATE ) {
		// language feature is okay
		++token;
	}

	return !(token->type() != Token::Type::RESERVED_WORD || token->content() != std::string(RESERVED_WORD_INTERFACE));
}

// library declaration:
// import <identifier> ;
bool Parser::isLibraryReference(TokenIterator token)
{
	TokenList tokens;

	tokens.emplace_back( Token::Type::RESERVED_WORD, std::string( RESERVED_WORD_IMPORT ) );
	tokens.emplace_back( Token::Type::IDENTIFIER );

	return checkSyntax(token, tokens);
}

// namespace declaration:
// [<visibility>] [language feature] namespace <identifier> { ... }
bool Parser::isNamespaceDeclaration(TokenIterator token)
{
	if ( token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		++token;
	}

	if ( token->type() == Token::Type::LANGUAGE_FEATURE_STATE ) {
		// language feature is okay
		++token;
	}

	return !(token->type() != Token::Type::RESERVED_WORD || token->content() != std::string(RESERVED_WORD_NAMESPACE));
}

// object declaration:
// [<visibility>] [language feature] object <identifier> [modifier] [extends <identifier>] [implements <identifier>, ...] { ... }
bool Parser::isObjectDeclaration(TokenIterator token)
{
	if ( token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		++token;
	}

	if ( token->type() == Token::Type::LANGUAGE_FEATURE_STATE ) {
		// language feature is okay
		++token;
	}

	if ( token->type() == Token::Type::MEMORY_LAYOUT ) {
		// memory layout is okay
		++token;
	}

	return !(token->type() != Token::Type::RESERVED_WORD || token->content() != RESERVED_WORD_OBJECT);
}

AccessMode::E Parser::parseAccessMode(TokenIterator& token, AccessMode::E defaultValue)
{
	AccessMode::E result = defaultValue;

	if ( token->type() == Token::Type::ACCESS_MODE || token->content() == DEFAULT ) {
		result = AccessMode::convert((*token++).content());
	}

	return result;
}

BlueprintType::E Parser::parseBluePrintType(TokenIterator &token)
{
	return BlueprintType::convert((*token++).content());
}

CheckedExceptions::E Parser::parseExceptions(TokenIterator& token, CheckedExceptions::E defaultValue)
{
	CheckedExceptions::E result = CheckedExceptions::convert(token->content());

	if ( result != CheckedExceptions::Unspecified ) {
		// an exception modifier has been detected => increment the token iterator and return the found modifier
		++token;

		return result;
	}

	// no exception token found => return the default value without incrementing the token iterator
	return defaultValue;
}

LanguageFeatureState::E Parser::parseLanguageFeatureState(TokenIterator& token, LanguageFeatureState::E defaultValue)
{
	LanguageFeatureState::E result = defaultValue;

	if ( token->type() == Token::Type::LANGUAGE_FEATURE_STATE ) {
		result = LanguageFeatureState::convert((*token++).content());
	}

	return result;
}

MemoryLayout::E Parser::parseMemoryLayout(TokenIterator& token, MemoryLayout::E defaultValue)
{
	MemoryLayout::E result = defaultValue;

	if ( token->type() == Token::Type::MEMORY_LAYOUT ) {
		result = MemoryLayout::convert((*token++).content());
	}

	return result;
}

Mutability::E Parser::parseMutability(TokenIterator& token, Mutability::E defaultValue)
{
	Mutability::E result = defaultValue;

	if ( token->type() == Token::Type::MUTABILITY ) {
		result = Mutability::convert((*token++).content());
	}

	return result;
}

ParameterList Parser::parseParameters(TokenIterator& token, IScope* scope)
{
	ParameterList params;

	expect(Token::Type::PARENTHESIS_OPEN, token);

	while ( (*++token).type() != Token::Type::PARENTHESIS_CLOSE ) {
		Common::TypeDeclaration type = parseTypeDeclaration(token, scope);

		// this allows unnamed parameters that are not instantiated, just to satisfy an interface or similar
		// {
		std::string name;

		if ( token->type() == Token::Type::IDENTIFIER ) {
			name = token->content();
			++token;
		}
		// }

		Mutability::E mutability = parseMutability( token, Mutability::Modify );
		AccessMode::E accessMode = parseAccessMode( token, AccessMode::Unspecified );

		bool hasDefaultValue = false;
		Runtime::AtomicValue value;
		if ( token->type() == Token::Type::ASSIGN ) {
			if ( name.empty() ) {
				throw Exceptions::SyntaxError("cannot use default values for unnamed parameters", token->position());
			}

			hasDefaultValue = true;
			++token;

			value = parseValueInitialization(token, type.mName);

			++token;
		}

		if ( hasDefaultValue && accessMode == AccessMode::ByReference ) {
			// parameters with default values cannot be accessed by reference
			throw Exceptions::SyntaxError("parameters with default values are not allowed to be accessed by reference");
		}

		params.push_back(
			Parameter::CreateDesigntime(name, type, value, hasDefaultValue, mutability, accessMode)
		);

		if ( token->type() == Token::Type::PARENTHESIS_CLOSE ) {
			break;
		}
	}

	expect(Token::Type::PARENTHESIS_CLOSE, token);

	return params;
}

Common::TypeDeclaration Parser::parseTypeDeclaration(TokenIterator& token, IScope* scope)
{
	Common::TypeDeclaration result;
	result.mName = identify(token);

	// determine if we are called at "design time" or "run time"
	if ( scope && scope->getScopeType() == IScope::IType::NamedScope ) {
		result.mConstraints = collectRuntimePrototypeConstraints(token);
	}
	else {
		result.mConstraints = collectDesigntimePrototypeConstraints(token);
	}

	result.mMutability = parseMutability(token, Mutability::Modify);

	return result;
}

Runtime::AtomicValue Parser::parseValueInitialization(TokenIterator& token, const std::string& type)
{
	Runtime::AtomicValue value;
	std::string sign;

	if ( token->type() == Token::Type::MATH_SUBTRACT ) {
		sign += "-";
		++token;
	}

	switch ( token->type() ) {
		case Token::Type::CONST_BOOLEAN:
			if ( type != _bool ) {
				throw Exceptions::DesigntimeException("invalid initialization value type provided: " + type, token->position());
			}
			if ( !sign.empty() ) {
				throw Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}

			value = Utils::Tools::stringToBool(token->content());
			break;
		case Token::Type::CONST_DOUBLE:
			if ( type != _double ) {
				throw Exceptions::DesigntimeException("invalid initialization value type provided: " + type, token->position());
			}

			value = Utils::Tools::stringToDouble(sign + token->content());
			break;
		case Token::Type::CONST_FLOAT:
			if ( type != _float ) {
				throw Exceptions::DesigntimeException("invalid initialization value type provided: " + type, token->position());
			}

			value = Utils::Tools::stringToFloat(sign + token->content());
			break;
		case Token::Type::CONST_INTEGER:
			if ( type == _int16 ) {
				value = static_cast<int16_t>( Utils::Tools::stringToInt(sign + token->content()) );
			}
			else if ( type == _int32 ) {
				value = Utils::Tools::stringToInt( sign + token->content() );
			}
			else if ( type == _int64 ) {
				value = static_cast<int64_t>( Utils::Tools::stringToInt(sign + token->content()) );
			}
			else {
				throw Exceptions::DesigntimeException("invalid initialization value type provided: " + type, token->position());
			}
			break;
		case Token::Type::CONST_LITERAL:
			if ( type != _string ) {
				throw Exceptions::DesigntimeException("invalid initialization value type provided: " + type, token->position());
			}
			if ( !sign.empty() ) {
				throw Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}

			value = token->content();
			break;
/* this is not yet usable, handling of "null" needs to be refactored before
		case Token::Type::CONST_NULL:
			if ( type != _object ) {
				throw Exceptions::DesigntimeException("invalid initialization value type provided: " + type, token->position());
			}
			if ( !sign.empty() ) {
				throw Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}

			value = Runtime::null;
			break;
*/
		// this is a hack to support null as default value for parameters without completely refactoring handling of null values
		case Token::Type::IDENTIFIER:
			if ( isAtomicType(type) ) {
				throw Exceptions::DesigntimeException("invalid initialization value type provided: " + type, token->position());
			}
			if ( token->content() != VALUE_NULL ) {
				throw Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}
			if ( !sign.empty() ) {
				throw Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}

			value = Runtime::null;
			break;
		default:
			if ( !sign.empty() ) {
				throw Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}

			throw Common::Exceptions::NotSupported("only atomic data types are allowed as default parameters", token->position());
	}

	return value;
}

Visibility::E Parser::parseVisibility(TokenIterator& token, Visibility::E defaultValue)
{
	Visibility::E result = defaultValue;

	if ( token->type() == Token::Type::VISIBILITY ) {
		result = Visibility::convert((*token++).content());
	}

	return result;
}


}
}
