
#ifndef ObjectiveScript_SanityChecker_h
#define ObjectiveScript_SanityChecker_h


// Library includes

// Project includes
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class SanityChecker
{
public:
	SanityChecker();
	~SanityChecker();

public:
	bool process(const TokenList& tokens);

private:
	bool checkBalancedCurlyBrackets() const;
	bool checkBalancedParenthesis() const;
	bool checkBalancedQuotes() const;

private:
	TokenList mTokens;
};


}


#endif
