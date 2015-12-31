
#ifndef ObjectiveScript_Tools_h
#define ObjectiveScript_Tools_h


// Library includes
#include <iostream>
#include <sstream>
#include <string>

// Project includes
#include "Object.h"
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Tools {


	std::string getFirstSubString(const std::string& str);
	std::string getLastSubString(const std::string& str);
	void split(const std::string& str, std::string& p, std::string& c);

	std::string boolToString(bool value);
	std::string floatToString(float value);
	std::string intToString(int value);
	bool stringToBool(const std::string &value);
	float stringToFloat(const std::string &value);
	int stringToInt(const std::string &value);

	template <class T>
	inline std::string toString(const T& t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}


}


bool checkSynthax(TokenIterator start, const TokenList& expected);
TokenIterator findNext(TokenIterator start, Token::Type::E type, Token::Type::E terminator = Token::Type::NIL);
TokenIterator findNextBalancedBracket(TokenIterator start, int generateErrorAfter = 0, Token::Type::E terminator = Token::Type::NIL);
TokenIterator findNextBalancedCurlyBracket(TokenIterator start, TokenIterator end, int generateErrorAfter = 0, Token::Type::E terminator = Token::Type::NIL);
TokenIterator findNextBalancedParenthesis(TokenIterator start, int generateErrorAfter = 0, Token::Type::E terminator = Token::Type::NIL);

bool isBooleanConst(const std::string& value);
bool isFalse(const std::string& value);
bool isFalse(const Object& object);
bool isTrue(const std::string& value);
bool isTrue(const Object& object);

}


#endif
