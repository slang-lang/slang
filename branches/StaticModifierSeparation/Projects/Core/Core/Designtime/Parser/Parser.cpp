
// Header
#include "Parser.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Consts.h>
#include <Core/Interfaces/IScope.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
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
		throw Common::Exceptions::Exception("prototype constraint size mismatch");
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


std::string Parser::buildDesigntimeConstraintTypename(const std::string &name, const PrototypeConstraints &constraints)
{
	if ( constraints.empty() ) {
		return name;
	}

	std::string type = name;
	type += "<";
	for ( PrototypeConstraints::const_iterator it = constraints.begin(); it != constraints.end(); ++it ) {
		type += it->mDesignType;

		if ( std::distance(it, constraints.end()) > 1 ) {
			type += ",";
		}
	}
	type += ">";

	return type;
}

std::string Parser::buildRuntimeConstraintTypename(const std::string &name, const PrototypeConstraints &constraints)
{
	if ( constraints.empty() ) {
		return name;
	}

	std::string type = name;
	type += "<";
	for ( PrototypeConstraints::const_iterator it = constraints.begin(); it != constraints.end(); ++it ) {
		type += it->mRunType;

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
				throw Common::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			++token;	// consume token

			inheritance = Ancestor::Type::Extends;
		}
		else if ( token->content() == RESERVED_WORD_IMPLEMENTS ) {
			if ( replicates ) {
				throw Common::Exceptions::Exception("combinations with 'replicates' are not allowed");
			}

			++token;	// consume token

			inheritance = Ancestor::Type::Implements;
		}
		else if ( token->content() == RESERVED_WORD_REPLICATES ) {
			if ( replicates ) {
				throw Common::Exceptions::Exception("combinations with 'replicates' are not allowed");
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

		ancestors.insert(
			Ancestor(Common::TypeDeclaration(type, constraints), inheritance, visibility)
		);
	}

	return ancestors;
}

PrototypeConstraints Parser::collectDesigntimePrototypeConstraints(TokenIterator &token)
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
				throw Common::Exceptions::SyntaxError("unexpected token '" + token->content() + "' found", token->position());
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
		if ( token->type() != Token::Type::SCOPE ) {
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
// [<visibility>] [language feature] interface <identifier> { ... }
bool Parser::isInterfaceDeclaration(TokenIterator token)
{
	TokenList tokens;

	tokens.push_back(Token(Token::Type::VISIBILITY, true));
	tokens.push_back(Token(Token::Type::RESERVED_WORD, std::string(RESERVED_WORD_INTERFACE)));
	tokens.push_back(Token(Token::Type::IDENTIFIER));

	return checkSyntax(token, tokens);
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
// [<visibility>] [language feature] <identifier> <identifier> = || ;
bool Parser::isMemberDeclaration(TokenIterator token)
{
	if ( token->type() == Token::Type::VISIBILITY ) {
		// visibility token is okay
		++token;
	}

	if ( token->isOptional() ) {
		// language feature is okay
		++token;
	}

	while ( token->type() == Token::Type::IDENTIFIER ) {
		// identifier token is okay
		++token;

		if ( token->type() == Token::Type::SCOPE ) {
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
		// language feature is okay
		++token;
	}

	while ( token->type() == Token::Type::IDENTIFIER ) {
		++token;

		if ( token->type() == Token::Type::SCOPE ) {
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

	if ( token->type() != Token::Type::RESERVED_WORD || token->content() != std::string(RESERVED_WORD_NAMESPACE) ) {
		return false;
	}

	return true;
}

// object declaration:
// [<visibility>] [language feature] object <identifier> [extends <identifier>] [implements <identifier>, ...] { ... }
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

	if ( token->type() != Token::Type::RESERVED_WORD || token->content() != std::string(RESERVED_WORD_OBJECT) ) {
		return false;
	}

	return true;
}

AccessMode::E Parser::parseAccessMode(TokenIterator& token, AccessMode::E defaultValue)
{
	AccessMode::E result = defaultValue;

	if ( token->type() == Token::Type::RESERVED_WORD ) {
		result = AccessMode::convert(token->content());

		if ( result == AccessMode::Unspecified ) {
			// invalid type
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}

	return result;
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

	if ( token->isOptional() && token->category() == Token::Category::Attribute && token->type() == Token::Type::LANGUAGEFEATURE ) {
		LanguageFeatureState::E value = LanguageFeatureState::convert((*token++).content());

		if ( value != LanguageFeatureState::Unknown ) {
			result = value;
		}
	}

	return result;
}

MemoryLayout::E Parser::parseMemoryLayout(TokenIterator& token, MemoryLayout::E defaultValue)
{
	MemoryLayout::E result = defaultValue;

	if ( token->type() == Token::Type::MODIFIER ) {
		result = MemoryLayout::convert((*token++).content());

		if ( result == MemoryLayout::Unknown ) {
			result = defaultValue;
		}
	}

	return result;
}

Mutability::E Parser::parseMutability(TokenIterator& token, Mutability::E defaultValue)
{
	Mutability::E result = defaultValue;

	if ( token->isOptional() && token->category() == Token::Category::Modifier && token->type() == Token::Type::MODIFIER ) {
		Mutability::E value = Mutability::convert((*token++).content());

		if ( value != Mutability::Unknown ) {
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
	ParameterList params;

	expect(Token::Type::PARENTHESIS_OPEN, token);

	while ( (*++token).type() != Token::Type::PARENTHESIS_CLOSE ) {
		AccessMode::E accessMode;
		bool hasDefaultValue = false;
		Mutability::E mutability = Mutability::Modify;
		Runtime::AtomicValue value;

		if ( token->type() == Token::Type::IDENTIFIER ) {
			// set default access mode for complex types
			accessMode = AccessMode::ByReference;
		}
		else if ( token->type() == Token::Type::TYPE ) {
			// set default access mode for atomic parameters
			accessMode = AccessMode::ByValue;
		}
		else {
			throw Common::Exceptions::SyntaxError("unexpected token '" + token->content() + "' found", token->position());
		}

		Common::TypeDeclaration type = parseTypeDeclaration(token, scope);

		std::string name = token->content();
		++token;

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
				throw Common::Exceptions::SyntaxError("unexpected modifier '" + token->content() + "' found", token->position());
			}
		}

		if ( token->content() == RESERVED_WORD_BY_REFERENCE ) {
			accessMode = AccessMode::ByReference;
			++token;
		}
		else if ( token->content() == RESERVED_WORD_BY_VALUE ) {
			accessMode = AccessMode::ByValue;
			++token;
		}

		if ( token->type() == Token::Type::ASSIGN ) {
			hasDefaultValue = true;
			++token;

			value = parseValueInitialization(token);

			++token;
		}

		if ( hasDefaultValue && accessMode == AccessMode::ByReference ) {
			// parameters with default values cannot be accessed by reference
			throw Common::Exceptions::SyntaxError("default parameters are not allowed to be accessed by reference");
		}

		params.push_back(
			Parameter::CreateDesigntime(name, Common::TypeDeclaration(type.mName, type.mConstraints), value, hasDefaultValue, mutability, accessMode)
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

	return result;
}

Runtime::AtomicValue Parser::parseValueInitialization(TokenIterator& token)
{
	Runtime::AtomicValue value;
	std::string sign;

	if ( token->type() == Token::Type::MATH_SUBTRACT ) {
		sign += "-";
		++token;
	}

	switch ( token->type() ) {
		case Token::Type::CONST_BOOLEAN:
			if ( !sign.empty() ) {
				throw Common::Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}

			value = Utils::Tools::stringToBool(token->content());
			break;
		case Token::Type::CONST_DOUBLE:
			value = Utils::Tools::stringToDouble(sign + token->content());
			break;
		case Token::Type::CONST_FLOAT:
			value = Utils::Tools::stringToFloat(sign + token->content());
			break;
		case Token::Type::CONST_INTEGER:
			value = Utils::Tools::stringToInt(sign + token->content());
			break;
		case Token::Type::CONST_LITERAL:
			if ( !sign.empty() ) {
				throw Common::Exceptions::SyntaxError("unexpected token '" + token->content() + "'", token->position());
			}

			value = token->content();
			break;
		default:
			throw Common::Exceptions::NotSupported("only atomic data types are allowed as default parameters", token->position());
	}

	return value;
}

Virtuality::E Parser::parseVirtuality(TokenIterator& token, Virtuality::E defaultValue)
{
	Virtuality::E result = defaultValue;

	if ( token->type() == Token::Type::MODIFIER ) {
		result = Virtuality::convert((*token++).content());

		if ( result == Virtuality::Unknown ) {
			result = defaultValue;
		}
	}

	return result;
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
