
#ifndef ObjectiveScript_Tokenizer_h
#define ObjectiveScript_Tokenizer_h


// Library includes

// Project includes
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Tokenizer
{
public:
	Tokenizer(const std::string& content);

public:
	void process();

	const TokenList& tokens() const;

protected:

private:	// Tokenizer
	void addIdentifier(const std::string& identifier);
	void addToken(const Token& token);
	void addType(const std::string& type);

	void classify();
	Token createToken(const std::string& con, const Token::Position& pos);
	void removeWhiteSpaces();
	void replace();

	bool isBoolean(const std::string& token) const;
	bool isDigit(const std::string& token) const;
	bool isIdentifer(const std::string& token) const;
	bool isKeyword(const std::string& token) const;
	bool isLiteral(const std::string& token) const;
	bool isReservedWord(const std::string& token) const;
	bool isType(const std::string& token) const;
	bool isVisibility(const std::string& token) const;
	bool isWhiteSpace(const std::string& token) const;

private:	// Preprocessor
	bool isDefined(const std::string& token) const;

private:
	std::string	mContent;
	StringList	mDefines;
	StringList	mIdentifiers;
	StringList	mKeywords;
	StringList	mReservedWords;
	TokenList	mTokens;
	StringList	mTypes;
};


}


#endif
