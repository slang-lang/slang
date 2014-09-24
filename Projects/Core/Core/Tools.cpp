
// Header
#include "Tools.h"

// Library includes

// Project includes
#include "Exceptions.h"

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
	unsigned int pos = str.find_first_of('.');

	p = str.substr(0, pos);
	if ( p.size() != str.size() ) {
		c = str.substr(pos + 1, str.size());
	}
}

float stringToFloat(const std::string &str)
{
	if ( str.empty() ) {
		return 0.f;
	}

    std::stringstream stream;
    stream << str;
	float f;
    stream >> f;

	return f;
}


}


bool checkSynthax(TokenIterator start, const TokenList& expected)
{
	if ( expected.empty() ) {
		return false;
	}

	for ( TokenIterator it = expected.begin(); it != expected.end(); ++it, ++start ) {
		if ( it->type() != start->type() ) {
			return false;
		}
	}

	return true;
}

TokenIterator findNext(TokenIterator start, Token::Type::E type, Token::Type::E end)
{
	int count = 0;
	TokenIterator tmp = start;

	while ( tmp->type() != type ) {
		if ( tmp->type() == end ) {
			// we did not find a result before the defined end-token appeared
			return start;
		}

		count++;
		tmp++;
	}

	return tmp;
}

TokenIterator findNextBalancedBracket(TokenIterator start, int generateErrorAfter, Token::Type::E end)
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

		if ( start->type() == end ) {
			// we did not find a result before the defined end-token appeared
			return tmp;
		}
		if ( generateErrorAfter && count >= generateErrorAfter ) {
			throw SyntaxError("Closed bracket expected, but not found after " + Tools::toString(count) + " iteration(s)", start->position());
		}

		count++;
		start++;
	}

	return start;
}

TokenIterator findNextBalancedCurlyBracket(TokenIterator start, int generateErrorAfter, Token::Type::E end)
{
	int count = 0;
	TokenIterator tmp = start;
	int openCurlyBrackets = 0;

	while ( start->type() != Token::Type::BRACKET_CURLY_CLOSE || openCurlyBrackets ) {
		if ( start->type() == Token::Type::BRACKET_CURLY_OPEN ) {
			openCurlyBrackets++;
		}
		if ( start->type() == Token::Type::BRACKET_CURLY_CLOSE ) {
			openCurlyBrackets--;
		}

		//if ( start->type() == end ) {
		//	// we did not find a result before the defined end-token appeared
		//	return tmp;
		//}

		if ( openCurlyBrackets == 0 && start->type() == end ) {
			break;
		}

		if ( generateErrorAfter && count >= generateErrorAfter ) {
			throw SyntaxError("Closed curly bracket expected, but not found after " + Tools::toString(count) + " iteration(s)", start->position());
		}

		count++;
		start++;
	}

	return start;
}

TokenIterator findNextBalancedParenthesis(TokenIterator start, int generateErrorAfter, Token::Type::E end)
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

		if ( start->type() == end ) {
			// we did not find a result before the defined end-token appeared
			return tmp;
		}
		if ( generateErrorAfter && count >= generateErrorAfter ) {
			throw SyntaxError("Closed parenthesis expected, but not found after " + Tools::toString(count) + " iteration(s)", start->position());
		}

		count++;
		start++;
	}

	return start;
}


}
