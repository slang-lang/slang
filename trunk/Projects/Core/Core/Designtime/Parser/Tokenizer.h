
#ifndef ObjectiveScript_Core_Designtime_Parser_Tokenizer_h
#define ObjectiveScript_Core_Designtime_Parser_Tokenizer_h


// Library includes

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Types.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Common {
	class Position;
}

class Tokenizer
{
public:
	Tokenizer(const std::string& filename, const std::string& content);

public:
	void process();

	const TokenList& tokens() const;

private:	// Tokenizer
	inline void addToken(const std::string &con, const Common::Position &position);
	void addToken(const Token& token);

	void mergeBooleanOperators();
	void mergeInfixPostfixOperators();
	void mergeOtherOperators();
	void removeWhiteSpaces();
	void replaceAssignments();
	void replaceConstDataTypes();
	void replaceOperators();

	bool isBoolean(const std::string& token) const;
	bool isDouble(const std::string& token) const;
	bool isFloat(const std::string& token) const;
	bool isInteger(const std::string& token) const;
	bool isIntegerWithType(const std::string& token) const;
	bool isKeyword(const std::string& token) const;
	bool isLanguageFeature(const std::string& token) const;
	bool isLiteral(const std::string& token) const;
	bool isModifier(const std::string& token) const;
	bool isReservedWord(const std::string& token) const;
	bool isType(const std::string& token) const;
	bool isVisibility(const std::string& token) const;
	bool isWhiteSpace(const std::string& token) const;

private:
	std::string	mContent;
	std::string mFilename;
	StringSet mLanguageFeatures;
	StringSet mKeywords;
	StringSet mModifiers;
	StringSet mReservedWords;
	TokenList mTokens;
	StringSet mTypes;
};


}


#endif
