
// Header
#include "Tools.h"

// Library includes

// Project includes
#include <Core/Designtime/Exceptions.h>
#include <Tools/Strings.h>
#include "Object.h"

// Namespace declarations


namespace Slang {


void expect(Token::Type::E expected, const TokenIterator& found)
{
	if ( found->type() != expected ) {
		throw Designtime::Exceptions::SyntaxError("unexpected token '" + found->content() + "' found", found->position());
	}
}

TokenIterator findNext(TokenIterator start, Token::Type::E type, Token::Type::E terminator)
{
	auto tmp = start;

	while ( tmp->type() != type ) {
		if ( tmp->type() == terminator ) {
			// we did not find a result before the defined end-token appeared
			return start;
		}

		++tmp;
	}

	return tmp;
}

TokenIterator findNextBalancedBracket(TokenIterator start, int generateErrorAfter, Token::Type::E terminator)
{
	int count = 0;
	auto tmp = start;
	int openBrackets = 0;

	while ( start->type() != Token::Type::BRACKET_CLOSE || openBrackets ) {
		if ( start->type() == Token::Type::BRACKET_OPEN ) {
			++openBrackets;
		}
		if ( start->type() == Token::Type::BRACKET_CLOSE ) {
			--openBrackets;
		}

		if ( start->type() == terminator ) {
			// we did not find a result before the defined end-token appeared
			return tmp;
		}
		if ( generateErrorAfter && count >= generateErrorAfter ) {
			throw Designtime::Exceptions::SyntaxError("Closed bracket expected, but none found after " + Utils::Tools::toString(count) + " iteration(s)", start->position());
		}

		++count;
		++start;
	}

	return start;
}

TokenIterator findNextBalancedCurlyBracket(TokenIterator start, TokenIterator end, int generateErrorAfter, Token::Type::E terminator)
{
	int count = 0;
	int openCurlyBrackets = 0;

	while ( ((start != end) && start->type() != Token::Type::BRACKET_CURLY_CLOSE) || openCurlyBrackets ) {
		if ( start->type() == Token::Type::BRACKET_CURLY_OPEN ) {
			++openCurlyBrackets;
		}
		if ( start->type() == Token::Type::BRACKET_CURLY_CLOSE ) {
			--openCurlyBrackets;
		}

		if ( openCurlyBrackets == 0 && start->type() == terminator ) {
			break;
		}

		if ( generateErrorAfter && count >= generateErrorAfter ) {
			throw Designtime::Exceptions::SyntaxError("Closed curly bracket expected, but none found after " + Utils::Tools::toString(count) + " iteration(s)", start->position());
		}

		++count;
		++start;
	}

	return start;
}

TokenIterator findNextBalancedParenthesis(TokenIterator start, int generateErrorAfter, Token::Type::E terminator)
{
	int count = 0;
	auto tmp = start;
	int openParenthesis = 0;

	while ( start->type() != Token::Type::PARENTHESIS_CLOSE || openParenthesis ) {
		if ( start->type() == Token::Type::PARENTHESIS_OPEN ) {
			++openParenthesis;
		}
		if ( start->type() == Token::Type::PARENTHESIS_CLOSE ) {
			--openParenthesis;
		}

		if ( start->type() == terminator ) {
			// we did not find a result before the defined end-token appeared
			return tmp;
		}
		if ( generateErrorAfter && count >= generateErrorAfter ) {
			throw Designtime::Exceptions::SyntaxError("closed parenthesis expected, but none found after " + Utils::Tools::toString(count) + " iteration(s)", start->position());
		}

		++count;
		++start;
	}

	return start;
}

bool isTrue(const Runtime::Object& object)
{
	if ( object.isAtomicType() ) {
		return object.getValue().toBool();
	}

	return object.isValid();
}

bool isTrue(const Runtime::Object* object)
{
	if ( object->isAtomicType() ) {
		return object->getValue().toBool();
	}

	return object->isValid();
}


}
