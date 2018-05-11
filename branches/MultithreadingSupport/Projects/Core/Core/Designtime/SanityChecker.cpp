
// Header
#include "SanityChecker.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


SanityChecker::SanityChecker()
{
}

SanityChecker::~SanityChecker()
{
}

bool SanityChecker::checkBalancedBrackets() const
{
	int openBrackets = 0;
	TokenIterator token = mTokens.begin();

	while ( token != mTokens.end() ) {
		if ( token->type() == Token::Type::BRACKET_OPEN ) {
			openBrackets++;
		}
		if ( token->type() == Token::Type::BRACKET_CLOSE ) {
			openBrackets--;
		}

		token++;
	}

	return (openBrackets == 0);
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

bool SanityChecker::process(const TokenList &tokens)
{
	mTokens = tokens;

	if ( !checkBalancedBrackets() ) {
		throw Common::Exceptions::SyntaxError("SanityCheck: unbalanced brackets detected", mTokens.begin()->position());
	}
	if ( !checkBalancedCurlyBrackets() ) {
		throw Common::Exceptions::SyntaxError("SanityCheck: unbalanced curly brackets detected", mTokens.begin()->position());
	}
	if ( !checkBalancedParenthesis() ) {
		throw Common::Exceptions::SyntaxError("SanityCheck: unbalanced parenthesis detected", mTokens.begin()->position());
	}
	if ( !checkBalancedQuotes() ) {
		throw Common::Exceptions::SyntaxError("SanityCheck: unbalanced quotes detected", mTokens.begin()->position());
	}

	return true;
}


}
}
