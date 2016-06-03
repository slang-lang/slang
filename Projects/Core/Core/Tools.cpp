
// Header
#include "Tools.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Tools {


std::string getFirstSubString(const std::string& str)
{
	return str.substr(0, str.find_first_of('.'));
}

std::string getLastSubString(const std::string& str)
{
	return str.substr(str.find_last_of('.'), str.size());
}

void split(const std::string& str, std::string& p, std::string& c)
{
	p = "";
	c = "";

	unsigned int pos = str.find_first_of('.');

	p = str.substr(0, pos);
	if ( p.size() != str.size() ) {
		c = str.substr(pos + 1, str.size());
	}
}

bool stringToBool(const std::string &value)
{
	if ( value.empty() || value == "false" ) {
		return false;
	}

    //std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    std::istringstream is(value);
    bool result;
    is >> std::boolalpha >> result;
    return result;
}

double stringToDouble(const std::string &value)
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

float stringToFloat(const std::string &value)
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

int stringToInt(const std::string &value)
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

double stringToNumber(const std::string &value)
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

std::string toString(bool value)
{
	if ( value ) {
		return BOOL_TRUE;
	}

	return BOOL_FALSE;
}

std::string toString(double value)
{
	return ConvertToString(value);
}

std::string toString(float value)
{
	return ConvertToString(value);
}

std::string toString(int value)
{
	return ConvertToString(value);
}

std::string toString(const std::string& value)
{
	return value;
}


}


void expect(Token::Type::E expected, TokenIterator found)
{
	if ( found->type() != expected ) {
		throw Utils::Exceptions::SyntaxError("unexpected token '" + found->content() + "' found", found->position());
	}
}

TokenIterator findNext(TokenIterator start, Token::Type::E type, Token::Type::E terminator)
{
	int count = 0;
	TokenIterator tmp = start;

	while ( tmp->type() != type ) {
		if ( tmp->type() == terminator ) {
			// we did not find a result before the defined end-token appeared
			return start;
		}

		count++;
		tmp++;
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
			openBrackets++;
		}
		if ( start->type() == Token::Type::BRACKET_CLOSE ) {
			openBrackets--;
		}

		if ( start->type() == terminator ) {
			// we did not find a result before the defined end-token appeared
			return tmp;
		}
		if ( generateErrorAfter && count >= generateErrorAfter ) {
			throw Utils::Exceptions::SyntaxError("Closed bracket expected, but not found after " + Tools::toString(count) + " iteration(s)", start->position());
		}

		count++;
		start++;
	}

	return start;
}

TokenIterator findNextBalancedCurlyBracket(TokenIterator start, TokenIterator end, int generateErrorAfter, Token::Type::E terminator)
{
	int count = 0;
	int openCurlyBrackets = 0;

	while ( ((start != end) && start->type() != Token::Type::BRACKET_CURLY_CLOSE) || openCurlyBrackets ) {
		if ( start->type() == Token::Type::BRACKET_CURLY_OPEN ) {
			openCurlyBrackets++;
		}
		if ( start->type() == Token::Type::BRACKET_CURLY_CLOSE ) {
			openCurlyBrackets--;
		}

		if ( openCurlyBrackets == 0 && start->type() == terminator ) {
			break;
		}

		if ( generateErrorAfter && count >= generateErrorAfter ) {
			throw Utils::Exceptions::SyntaxError("Closed curly bracket expected, but not found after " + Tools::toString(count) + " iteration(s)", start->position());
		}

		count++;
		start++;
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
			openParenthesis++;
		}
		if ( start->type() == Token::Type::PARENTHESIS_CLOSE ) {
			openParenthesis--;
		}

		if ( start->type() == terminator ) {
			// we did not find a result before the defined end-token appeared
			return tmp;
		}
		if ( generateErrorAfter && count >= generateErrorAfter ) {
			throw Utils::Exceptions::SyntaxError("closed parenthesis expected, but not found after " + Tools::toString(count) + " iteration(s)", start->position());
		}

		count++;
		start++;
	}

	return start;
}

bool isBooleanConst(const std::string& value)
{
	return ( value == BOOL_FALSE || value == BOOL_TRUE );
}

bool isTrue(const std::string& value)
{
	return ( value != BOOL_FALSE && value != "0" && value != "0.f" && value != "0.0" );
}

bool isTrue(const Runtime::Object& object)
{
	if ( !object.isValid() || !isTrue(object.getValue()) ) {
		return false;
	}

	// everything that's not false has to be true
	return true;
}

bool isTrue(const Runtime::Object* object)
{
	if ( !object || !object->isValid() || !isTrue(object->getValue()) ) {
		return false;
	}

	// everything that's not false has to be true
	return true;
}


}
