
// Header
#include "Parser.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Interfaces/IScope.h>
#include <Core/Tools.h>
#include <Core/Types.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace Slang {
namespace Designtime {


bool checkSyntax(TokenIterator foundIt, const TokenList& expected)
{
	if ( expected.empty() ) {
		return false;
	}

	for ( TokenIterator expectedIt = expected.begin(); expectedIt != expected.end(); ++expectedIt, ++foundIt ) {
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
		throw Designtime::Exceptions::SyntaxError("prototype constraint size mismatch");
	}

	PrototypeConstraints::const_iterator designIt = designtime.begin();
	PrototypeConstraints::const_iterator runIt = runtime.begin();

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
	for ( PrototypeConstraints::const_iterator it = constraints.cbegin(); it != constraints.cend(); ++it ) {
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
	for ( PrototypeConstraints::const_iterator it = constraints.cbegin(); it != constraints.cend(); ++it ) {
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
				throw Designtime::Exceptions::SyntaxError("combinations with 'replicates' are not allowed");
			}

			++token;	// consume token

			inheritance = Ancestor::Type::Extends;
		}
		else if ( token->content() == RESERVED_WORD_IMPLEMENTS ) {
			if ( replicates ) {
				throw Designtime::Exceptions::SyntaxError("combinations with 'replicates' are not allowed");
			}

			++token;	// consume token

			inheritance = Ancestor::Type::Implements;
		}
		else if ( token->content() == RESERVED_WORD_REPLICATES ) {
			if ( replicates ) {
				throw Designtime::Exceptions::SyntaxError("combinations with 'replicates' are not allowed");
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

		std::string type = Parser::identify(token);

		PrototypeConstraints constraints = collectDesigntimePrototypeConstraints(token);

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
	std::string designType;
	unsigned int index = 0;
	std::string runType;

	while ( token->type() != Token::Type::COMPARE_GREATER ) {
		designType = token->content();
		runType = token->content();	// hack to prevent runtime type to be empty
		++token;

		if ( token->type() == Token::Type::COLON ) {	// constraint
			++token;

			if ( token->type() == Token::Type::IDENTIFIER ) {
				constraint = token->content();
			}
			else if ( token->type() == Token::Type::TYPE ) {
				constraint = token->content();
			}
			else {
				throw Designtime::Exceptions::SyntaxError("unexpected token '" + token->content() + "' found", token->position());
			}

			++token;
		}

		constraints.push_back(
			PrototypeConstraint(index, designType, runType, constraint)
		);

		// prepare next iteration
		constraint = "";
		designType = "";
		++index;
		runType = "";

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
	std::string runType;

	while ( token->type() != Token::Type::COMPARE_GREATER ) {
		runType = token->content();
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
		runType = "";

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

	tokens.push_back(Token(Token::Type::VISIBILITY, true));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_ENUM)));
	tokens.push_back(Token(Token::Type::IDENTIFIER));

	return checkSyntax(token, tokens);
}

// interface declaration:
// [<visibility>] [language feature] interface <identifier> [modifier] { ... }
bool Parser::isInterfaceDeclaration(TokenIterator token)
{
	if ( token->isOptional() && token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		++token;
	}

	if ( token->isOptional() && token->category() == Token::Category::Attribute && token->type() == Token::Type::LANGUAGEFEATURE ) {
		// language feature is okay
		++token;
	}

	if ( token->isOptional() && token->type() == Token::Type::MODIFIER ) {
		// abstract is okay
		++token;
	}

	return !(token->type() != Token::Type::RESERVED_WORD || token->content() != std::string(RESERVED_WORD_INTERFACE));
}

// library declaration:
// import <identifier> ;
bool Parser::isLibraryReference(TokenIterator token)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_IMPORT)));
	tokens.push_back(Token(Token::Type::IDENTIFIER));

	return checkSyntax(token, tokens);
}

// member declaration:
// [<visibility>] [language feature] <identifier> <identifier> [modifier] = || ;
bool Parser::isMemberDeclaration(TokenIterator token)
{
	if ( token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		++token;
	}

	if ( token->isOptional() ) {
		// memory layout is okay
		++token;
	}

	if ( token->isOptional() ) {
		// language feature is okay
		++token;
	}

	while ( token->type() == Token::Type::IDENTIFIER ) {
		// identifier token is okay
		++token;

		if ( token->type() == Token::Type::OPERATOR_SCOPE ) {
			// scope token is okay
			++token;
			continue;
		}
	}

	if ( token->type() == Token::Type::TYPE ) {
		// type is okay
		++token;
	}

	if ( token->type() == Token::Type::IDENTIFIER ) {
		// name is okay
		++token;
	}

	if ( token->isOptional() ) {
		// modifier is okay
		++token;
	}

	// check for an assignment or semicolon
	return token->type() == Token::Type::ASSIGN || token->type() == Token::Type::SEMICOLON;
}

// syntax:
// [<visibility>] <type> <identifier> (
// [<visibility>] <identifier> <identifier> (
bool Parser::isMethodDeclaration(TokenIterator token)
{
	if ( token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		++token;
	}

	if ( token->isOptional() ) {
		// memory layout is okay
		++token;
	}

	if ( token->isOptional() ) {
		// language feature is okay
		++token;
	}

	while ( token->type() == Token::Type::IDENTIFIER ) {
		++token;

		if ( token->type() == Token::Type::OPERATOR_SCOPE ) {
			++token;
			continue;
		}
	}

	if ( token->type() == Token::Type::TYPE ) {
		// type is okay
		++token;
	}

	if ( token->category() == Token::Category::Modifier ) {
		// modifier is okay
		++token;
	}

	if ( token->type() == Token::Type::IDENTIFIER ) {
		// name is okay
		++token;
	}

	// check for open parenthesis
	return token->type() == Token::Type::PARENTHESIS_OPEN;
}

// namespace declaration:
// [<visibility>] [language feature] namespace <identifier> { ... }
bool Parser::isNamespaceDeclaration(TokenIterator token)
{
	if ( token->isOptional() && token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		++token;
	}

	if ( token->isOptional() && token->type() == Token::Type::LANGUAGEFEATURE ) {
		// language feature is okay
		++token;
	}

	return !(token->type() != Token::Type::RESERVED_WORD || token->content() != std::string(RESERVED_WORD_NAMESPACE));
}

// object declaration:
// [<visibility>] [language feature] object <identifier> [modifier] [extends <identifier>] [implements <identifier>, ...] { ... }
bool Parser::isObjectDeclaration(TokenIterator token)
{
	if ( token->isOptional() && token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		++token;
	}

	if ( token->isOptional() && token->category() == Token::Category::Attribute && token->type() == Token::Type::LANGUAGEFEATURE ) {
		// language feature is okay
		++token;
	}

	if ( token->isOptional() && token->type() == Token::Type::MODIFIER ) {
		// abstract is okay
		++token;
	}

	return !(token->type() != Token::Type::RESERVED_WORD || token->content() != std::string(RESERVED_WORD_OBJECT));
}

AccessMode::E Parser::parseAccessMode(TokenIterator& token, AccessMode::E defaultValue)
{
	AccessMode::E result = defaultValue;

	if ( token->type() == Token::Type::RESERVED_WORD ) {
		result = AccessMode::convert(token->content());

		if ( result == AccessMode::Unspecified ) {
			// invalid type
			throw Designtime::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}

	return result;
}

BlueprintType::E Parser::parseBluePrintType(TokenIterator &token)
{
	return BlueprintType::convert((*token++).content());
}

CheckedExceptions::E Parser::parseExceptions(TokenIterator& token, CheckedExceptions::E defaultValue)
{
	CheckedExceptions::E result = CheckedExceptions::convert((*token).content());

	if ( result != CheckedExceptions::Unspecified ) {
		// an exception modifier has been detected => increment the token iterator and return the found modifier
		++token;

		return result;
	}

	// no exception token found => return the default value without incrementing the token iterator
	return defaultValue;
}

ImplementationType::E Parser::parseImplementationType(TokenIterator& token, ImplementationType::E defaultValue)
{
	ImplementationType::E result = defaultValue;

	if ( token->isOptional() && token->type() == Token::Type::MODIFIER ) {
		ImplementationType::E value = ImplementationType::convert((*token++).content());

		if ( value != ImplementationType::Unspecified ) {
			result = value;
		}
	}

	return result;
}

LanguageFeatureState::E Parser::parseLanguageFeatureState(TokenIterator& token, LanguageFeatureState::E defaultValue)
{
	LanguageFeatureState::E result = defaultValue;

	if ( token->isOptional() && token->category() == Token::Category::Attribute && token->type() == Token::Type::LANGUAGEFEATURE ) {
		LanguageFeatureState::E value = LanguageFeatureState::convert((*token++).content());

		if ( value != LanguageFeatureState::Unspecified ) {
			result = value;
		}
	}

	return result;
}

MemoryLayout::E Parser::parseMemoryLayout(TokenIterator& token, MemoryLayout::E defaultValue)
{
	MemoryLayout::E result = MemoryLayout::convert((*token).content());

	if ( result != MemoryLayout::Unspecified ) {
		// a memory layout modifier has been detected => increment the token iterator and return the found modifier
		++token;

		return result;
	}

	// no memory layout token found => return the default value without incrementing the token iterator
	return defaultValue;
}

Mutability::E Parser::parseMutability(TokenIterator& token, Mutability::E defaultValue)
{
	Mutability::E result = Mutability::convert((*token).content());

	if ( result != Mutability::Unknown ) {
		// a mutability modifier has been detected => increment the token iterator and return the found modifier
		++token;

		return result;
	}

	// no mutability token found => return the default value without incrementing the token iterator
	return defaultValue;
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

		Mutability::E mutability = Mutability::Modify;
		if ( token->category() == Token::Category::Modifier ) {
			if ( token->content() == MODIFIER_CONST ) {
				mutability = Mutability::Const;
				++token;
			}
			else if ( token->content() == MODIFIER_MODIFY ) {
				mutability = Mutability::Modify;
				++token;
			}
			else {
				throw Designtime::Exceptions::SyntaxError("unexpected modifier '" + token->content() + "' found", token->position());
			}
		}

		AccessMode::E accessMode = AccessMode::Unspecified;
		if ( token->category() == Token::Category::ReservedWord ) {
			if ( token->content() == RESERVED_WORD_BY_REFERENCE ) {
				accessMode = AccessMode::ByReference;
				++token;
			}
			else {
				throw Designtime::Exceptions::SyntaxError("unexpected modifier '" + token->content() + "' found", token->position());
			}
		}

		bool hasDefaultValue = false;
		Runtime::AtomicValue value;
		if ( token->type() == Token::Type::ASSIGN ) {
			if ( name.empty() ) {
				throw Designtime::Exceptions::SyntaxError("cannot use default values for unnamed parameters", token->position());
			}

			hasDefaultValue = true;
			++token;

			value = parseValueInitialization(token, type.mName);

			++token;
		}

		if ( hasDefaultValue && accessMode == AccessMode::ByReference ) {
			// parameters with default values cannot be accessed by reference
			throw Designtime::Exceptions::SyntaxError("default parameters are not allowed to be accessed by reference");
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
				throw Designtime::Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
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
			if ( type != _int ) {
				throw Exceptions::DesigntimeException("invalid initialization value type provided: " + type, token->position());
			}

			value = Utils::Tools::stringToInt(sign + token->content());
			break;
		case Token::Type::CONST_LITERAL:
			if ( type != _string ) {
				throw Exceptions::DesigntimeException("invalid initialization value type provided: " + type, token->position());
			}
			if ( !sign.empty() ) {
				throw Designtime::Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}

			value = token->content();
			break;
/* this is not yet usable, handling of "null" needs to be refactored before
		case Token::Type::CONST_NULL:
			if ( type != _object ) {
				throw Exceptions::DesigntimeException("invalid initialization value type provided: " + type, token->position());
			}
			if ( !sign.empty() ) {
				throw Designtime::Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
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
				throw Designtime::Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}
			if ( !sign.empty() ) {
				throw Designtime::Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}

			value = Runtime::null;
			break;
		default:
			if ( !sign.empty() ) {
				throw Designtime::Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}

			throw Common::Exceptions::NotSupported("only atomic data types are allowed as default parameters", token->position());
	}

	return value;
}

Virtuality::E Parser::parseVirtuality(TokenIterator& token, Virtuality::E defaultValue)
{
	Virtuality::E result = Virtuality::convert((*token).content());

	if ( result != Virtuality::Unknown ) {
		// a virtuality modifier has been detected => increment the token iterator and return the found modifier
		++token;

		return result;
	}

	// no virtuality token found => return the default value without incrementing the token iterator
	return defaultValue;
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
