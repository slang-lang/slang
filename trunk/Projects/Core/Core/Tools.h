
#ifndef ObjectiveScript_Core_Tools_h
#define ObjectiveScript_Core_Tools_h


// Library includes
#include <iostream>
#include <sstream>
#include <string>

// Project includes
#include <Core/Designtime/Parser/Token.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Runtime {
	class Object;
}


void expect(Token::Type::E expected, const TokenIterator& found);

inline TokenIterator lookahead(TokenIterator token, int numLooks = 1) {
	do { ++token; --numLooks; } while ( numLooks > 0 ); return token;
}

inline TokenList::iterator lookahead(TokenList::iterator token, int numLooks = 1) {
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
