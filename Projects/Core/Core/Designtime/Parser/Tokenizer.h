
#ifndef Slang_Core_Core_Designtime_Parser_Tokenizer_h
#define Slang_Core_Core_Designtime_Parser_Tokenizer_h


// Library includes

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Types.h>

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
namespace Common {
	class Position;
}

class Tokenizer
{
public:
	Tokenizer(std::string filename, std::string content);

public:
	void process();

	const TokenList& tokens() const;

private:	// Tokenizer
	inline void addToken(const std::string& con, const Common::Position& position);
	void addToken(const Token& token);

	void mergeAssignments();
	void mergeOperators();
	void replaceConstDataTypes();
	void replaceOperators();

	inline bool isBoolean(const std::string& token) const;
	inline bool isDouble(const std::string& token) const;
	inline bool isFloat(const std::string& token) const;
	inline bool isInteger(const std::string& token) const;
	inline bool isIntegerWithType(const std::string& token) const;
	inline bool isKeyword(const std::string& token) const;
	inline bool isLanguageFeature(const std::string& token) const;
	inline bool isLiteral(const std::string& token) const;
	inline bool isModifier(const std::string& token) const;
	inline bool isReservedWord(const std::string& token) const;
	inline bool isType(const std::string& token) const;
	inline bool isVisibility(const std::string& token) const;
	inline bool isWhiteSpace(const std::string& token) const;

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
