
// Header
#include "SanityChecker.h"

// Library includes

// Project includes
#include <Utils/Exceptions.h>
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


SanityChecker::SanityChecker()
{
}

SanityChecker::~SanityChecker()
{
}

bool SanityChecker::checkBalancedCurlyBrackets() const
{
	int openBrackets = 0;
	TokenIterator token = mTokens.begin();

	while ( token != mTokens.end() ) {
		if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
			openBrackets++;
		}
		if ( token->type() == Token::Type::BRACKET_CURLY_CLOSE ) {
			openBrackets--;
		}

		token++;
	}

	return (openBrackets == 0);
}

bool SanityChecker::checkBalancedParenthesis() const
{
	int openParenthesis = 0;
	TokenIterator token = mTokens.begin();

	while ( token != mTokens.end() ) {
		if ( token->type() == Token::Type::PARENTHESIS_OPEN ) {
			openParenthesis++;
		}
		if ( token->type() == Token::Type::PARENTHESIS_CLOSE ) {
			openParenthesis--;
		}

		token++;
	}

	return (openParenthesis == 0);
}

bool SanityChecker::checkBalancedQuotes() const
{
	bool openQuote = false;
	TokenIterator token = mTokens.begin();

	while ( token != mTokens.end() ) {
		if ( token->type() == Token::Type::QUOTATION_DOUBLE ) {
			openQuote = !openQuote;
		}

		token++;
	}

	return !openQuote;
}

bool SanityChecker::process(const TokenList& tokens)
{
	mTokens = tokens;

	if ( !checkBalancedCurlyBrackets() ) {
		throw Utils::Exceptions::SyntaxError("SanityCheck: unbalanced curly brackets found");
		return false;
	}
	if ( !checkBalancedParenthesis() ) {
		throw Utils::Exceptions::SyntaxError("SanityCheck: unbalanced parenthesis found");
		return false;
	}
	if ( !checkBalancedQuotes() ) {
		throw Utils::Exceptions::SyntaxError("SanityCheck: unbalanced quotes found");
		return false;
	}

	return true;
}

}
