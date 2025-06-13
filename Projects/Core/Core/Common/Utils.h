
#ifndef Slang_Core_Core_Designtime_Parser_Utils_h
#define Slang_Core_Core_Designtime_Parser_Utils_h


// Library includes
#include <iostream>
#include <sstream>
#include <string>

// Project includes
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace Slang {


void expect(Token::Type::E expected, const TokenIterator& found);

TokenIterator findNext(TokenIterator start, Token::Type::E type, Token::Type::E terminator = Token::Type::NIL);
TokenIterator findNextBalancedBracket(TokenIterator start, int generateErrorAfter = 0, Token::Type::E terminator = Token::Type::NIL);
TokenIterator findNextBalancedCurlyBracket(TokenIterator start, TokenIterator end, int generateErrorAfter = 0, Token::Type::E terminator = Token::Type::NIL);
TokenIterator findNextBalancedParenthesis(TokenIterator start, int generateErrorAfter = 0, Token::Type::E terminator = Token::Type::NIL);

inline TokenIterator lookahead(TokenIterator token, int numLooks = 1)
{
	do { ++token; --numLooks; } while ( numLooks > 0 ); return token;
}

inline TokenList::iterator lookahead(TokenList::iterator token, int numLooks = 1)
{
	do { ++token; --numLooks; } while ( numLooks > 0 ); return token;
}


}


#endif

