
#ifndef ObjectiveScript_Tokenizer_h
#define ObjectiveScript_Tokenizer_h


// Library includes

// Project includes
#include <Core/Utils/Position.h>
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Tokenizer
{
public:
	Tokenizer(const std::string& filename, const std::string& content);

public:
	void process();

	const TokenList& tokens() const;

protected:

private:	// Tokenizer
	void addIdentifier(const std::string& identifier);
	void addToken(const Token& token);
	void addType(const std::string& type);

	void classify();
	Token createToken(const std::string& con, const Utils::Position& position);
	void mergeBooleanOperators();
	void mergeInfixPostfixOperators();
	void removeWhiteSpaces();
	void replaceAssignments();
	void replaceOperators();
	void replacePrototypes();

	bool isBoolean(const std::string& token) const;
	bool isFloat(const std::string& token) const;
	bool isIdentifer(const std::string& token) const;
	bool isInteger(const std::string& token) const;
	bool isKeyword(const std::string& token) const;
	bool isLanguageFeature(const std::string& token) const;
	bool isLiteral(const std::string& token) const;
	bool isModifier(const std::string& token) const;
	bool isNumber(const std::string& token) const;
	bool isReservedWord(const std::string& token) const;
	bool isType(const std::string& token) const;
	bool isVisibility(const std::string& token) const;
	bool isWhiteSpace(const std::string& token) const;

private:	// Preprocessor
	bool isDefined(const std::string& token) const;
	bool isPrototype(TokenIterator token) const;

private:
	std::string	mContent;
	StringList mDefines;
	std::string mFilename;
	StringList mIdentifiers;
	StringList mLanguageFeatures;
	StringList mKeywords;
	StringList mModifiers;
	StringList mReservedWords;
	TokenList mTokens;
	StringList mTypes;
};


}


#endif
