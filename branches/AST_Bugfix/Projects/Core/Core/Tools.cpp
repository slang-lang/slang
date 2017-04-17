
// Header
#include "Tools.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include "Object.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Tools {


void split(const std::string& str, std::string& p, std::string& c)
{
	c = "";

	unsigned long pos = str.find_first_of('.');

	p = str.substr(0, pos);
	if ( p.size() != str.size() ) {
		c = str.substr(pos + 1, str.size());
	}
}

void splitBy(const std::string& str, char splitter, std::string& p, std::string& c)
{
	c = "";

	unsigned long pos = str.find_first_of(splitter);

	p = str.substr(0, pos);
	if ( p.size() != str.size() ) {
		c = str.substr(pos + 1, str.size());
	}
}

bool stringToBool(const std::string& value)
{
	return !(value.empty() || value == "\n" || value == BOOL_FALSE);
}

double stringToDouble(const std::string& value)
{
	if ( value.empty() ) {
		return 0.0;
	}

	std::stringstream stream;
	stream << value;
	double result;
	stream >> result;

	return result;
}

float stringToFloat(const std::string& value)
{
	if ( value.empty() ) {
		return 0.f;
	}

	std::stringstream stream;
	stream << value;
	float result;
	stream >> result;

	return result;
}

int stringToInt(const std::string& value)
{
	if ( value.empty() ) {
		return 0;
	}

	std::stringstream stream;
	stream << value;
	int result;
	stream >> result;

	return result;
}


}


void expect(Token::Type::E expected, TokenIterator found)
{
	if ( found->type() != expected ) {
		throw Common::Exceptions::SyntaxError("unexpected token '" + found->content() + "' found", found->position());
	}
}

TokenIterator findNext(TokenIterator start, Token::Type::E type, Token::Type::E terminator)
{
	TokenIterator tmp = start;

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
	TokenIterator tmp = start;
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
			throw Common::Exceptions::SyntaxError("Closed bracket expected, but not found after " + Tools::toString(count) + " iteration(s)", start->position());
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
			throw Common::Exceptions::SyntaxError("Closed curly bracket expected, but not found after " + Tools::toString(count) + " iteration(s)", start->position());
		}

		++count;
		++start;
	}

	return start;
}

TokenIterator findNextBalancedParenthesis(TokenIterator start, int generateErrorAfter, Token::Type::E terminator)
{
	int count = 0;
	TokenIterator tmp = start;
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
			throw Common::Exceptions::SyntaxError("closed parenthesis expected, but not found after " + Tools::toString(count) + " iteration(s)", start->position());
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
