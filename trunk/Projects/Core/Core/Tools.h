
#ifndef ObjectiveScript_Core_Tools_h
#define ObjectiveScript_Core_Tools_h


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

	bool stringToBool(const std::string &value);
	double stringToDouble(const std::string &value);
	float stringToFloat(const std::string &value);
	int stringToInt(const std::string &value);
	double stringToNumber(const std::string &value);

	std::string toString(bool value);
	std::string toString(double value);
	std::string toString(float value);
	std::string toString(int value);
	std::string toString(const std::string& value);

	template <class T> inline std::string ConvertToStdString(const T &t) {
		std::stringstream ss; ss << t; return ss.str();
	}


}


void expect(Token::Type::E expected, TokenIterator found);

inline TokenIterator lookahead(TokenIterator token, int numLooks = 1) {
	do { ++token; --numLooks; } while ( numLooks > 0 ); return token;
}

TokenIterator findNext(TokenIterator start, Token::Type::E type, Token::Type::E terminator = Token::Type::NIL);
TokenIterator findNextBalancedBracket(TokenIterator start, int generateErrorAfter = 0, Token::Type::E terminator = Token::Type::NIL);
TokenIterator findNextBalancedCurlyBracket(TokenIterator start, TokenIterator end, int generateErrorAfter = 0, Token::Type::E terminator = Token::Type::NIL);
TokenIterator findNextBalancedParenthesis(TokenIterator start, int generateErrorAfter = 0, Token::Type::E terminator = Token::Type::NIL);

bool isTrue(const Runtime::Object& object);
bool isTrue(const Runtime::Object* object);

}


#endif
