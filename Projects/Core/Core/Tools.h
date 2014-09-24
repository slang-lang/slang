
#ifndef ObjectiveScript_Tools_h
#define ObjectiveScript_Tools_h


// Library includes
#include <iostream>
#include <sstream>
#include <string>

// Project includes
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


#define os_debug(message) std::cout << "[DEBUG] " << message << std::endl;
#define os_error(message) std::cout << "[ERROR] " << message << std::endl;
#define os_info(message) std::cout << "[INFO ] " << message << std::endl;
#define os_warn(message) std::cout << "[WARN ] " << message << std::endl;


namespace Tools {

std::string getFirstSubString(const std::string& str);
std::string getLastSubString(const std::string& str);
void split(const std::string& str, std::string& p, std::string& c);

float stringToFloat(const std::string &str);

template <class T>
inline std::string toString(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

}

bool checkSynthax(TokenIterator start, const TokenList& expected);
TokenIterator findNext(TokenIterator start, Token::Type::E type, Token::Type::E end = Token::Type::NIL);
TokenIterator findNextBalancedBracket(TokenIterator start, int generateErrorAfter = 0, Token::Type::E end = Token::Type::NIL);
TokenIterator findNextBalancedCurlyBracket(TokenIterator start, int generateErrorAfter = 0, Token::Type::E end = Token::Type::NIL);
TokenIterator findNextBalancedParenthesis(TokenIterator start, int generateErrorAfter = 0, Token::Type::E end = Token::Type::NIL);


}


#endif
