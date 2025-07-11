
#ifndef Slang_Core_Core_Designtime_Parser_Tokenizer_h
#define Slang_Core_Core_Designtime_Parser_Tokenizer_h


// Library includes

// Project includes
#include <Core/Common/Token.h>
#include <Core/Common/Types.h>

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
	void replaceConstDataTypesPatternMatching();
	void replaceOperators();

	inline bool isAccessMode(const std::string& token) const;
	static inline bool isBoolean(const std::string& token) ;
	static inline bool isDouble(const std::string& token) ;
	static inline bool isFloat(const std::string& token) ;
	static inline bool isInteger(const std::string& token) ;
	static inline bool isIntegerWithType(const std::string& token) ;
	inline bool isKeyword(const std::string& token) const;
	inline bool isLanguageFeature(const std::string& token) const;
	static inline bool isLiteral(const std::string& token) ;
	inline bool isMemoryLayout(const std::string& token) const;
	inline bool isModifier(const std::string& token) const;
	inline bool isMutability(const std::string& token) const;
	inline bool isReservedWord(const std::string& token) const;
	static inline bool isVisibility(const std::string& token) ;
	static inline bool isWhiteSpace(const std::string& token) ;

private:
	StringSet mAccessMode;
	std::string mContent;
	std::string mFilename;
	StringSet mLanguageFeatureState;
	StringSet mKeyword;
	StringSet mMemoryLayout;
	StringSet mModifier;
	StringSet mMutability;
	StringSet mReservedWord;
	TokenList mTokens;
	StringSet mType;
};


}


#endif

