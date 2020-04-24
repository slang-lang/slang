
#ifndef Slang_Core_Core_Designtime_SanityChecker_h
#define Slang_Core_Core_Designtime_SanityChecker_h


// Library includes

// Project includes
#include <Core/Designtime/Parser/Token.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class SanityChecker
{
public:
	SanityChecker() = default;
	~SanityChecker() = default;

public:
	bool process(const TokenList &tokens);

private:
	bool checkBalancedBrackets() const;
	bool checkBalancedCurlyBrackets() const;
	bool checkBalancedParenthesis() const;
	bool checkBalancedQuotes() const;

private:
	TokenList mTokens;
};


}
}


#endif
