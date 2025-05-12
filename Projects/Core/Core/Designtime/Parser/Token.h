
#ifndef Slang_Core_Core_Designtime_Parser_Token_h
#define Slang_Core_Core_Designtime_Parser_Token_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Common/Position.h>

// Forward declarations

// Namespace declarations


namespace Slang {


class Token
{
public:
	class Category
	{
	public:
		enum E {
			None,
			Assignment,
			Comparator,
			Constant,
			Ignorable,
			Identifier,
			Keyword,
			Modifier,
			Operator,
			ReservedWord
		};
	};

	class Type
	{
	public:
		enum E {
			ACCESS_MODE,
			AND,
			ARRAY_SUBSCRIPT,
			ASSIGN,
			ASSIGN_ADDITION,
			ASSIGN_BITAND,
			ASSIGN_BITCOMPLEMENT,
			ASSIGN_BITOR,
			ASSIGN_DIVIDE,
			ASSIGN_MODULO,
			ASSIGN_MULTIPLY,
			ASSIGN_SUBTRACT,
			BRACKET_CLOSE,
			BRACKET_CURLY_CLOSE,
			BRACKET_CURLY_OPEN,
			BRACKET_OPEN,
			BITAND,
			BITCOMPLEMENT,
			BITOR,
			CASE,
			COLON,
			COMMA,
			COMPARE_EQUAL,
			COMPARE_EQUAL_CONTENT,
			COMPARE_LESS,
			COMPARE_LESS_EQUAL,
			COMPARE_GREATER,
			COMPARE_GREATER_EQUAL,
			COMPARE_UNEQUAL,
			COMPARE_UNEQUAL_CONTENT,
			CONST_BOOLEAN,
			CONST_DOUBLE,
			CONST_FLOAT,
			CONST_INTEGER,
			CONST_LITERAL,
			CONST_NULL,
			ENDOFFILE,
			GREATER,
			IDENTIFIER,
			KEYWORD,
			LANGUAGE_FEATURE_STATE,
			LESS,
			MATH_ADDITION,
			MATH_DIVIDE,
			MATH_MODULO,
			MATH_MULTIPLY,
			MATH_SUBTRACT,
			MEMORY_LAYOUT,
			MODIFIER,
			MUTABILITY,
			NAND,
			NIL,
			NOR,
			OPERATOR_DECREMENT,
			OPERATOR_INCREMENT,
			OPERATOR_IS,
			OPERATOR_NOT,
			OPERATOR_RANGE,
			OPERATOR_SCOPE,
			OPERATOR_SHIFT_LEFT,
			OPERATOR_SHIFT_RIGHT,
			OPERATOR_VALIDATE,
			OR,
			PARENTHESIS_CLOSE,
			PARENTHESIS_OPEN,
			QUESTION_MARK,
			QUOTATION_DOUBLE,
			RESERVED_WORD,
			SEMICOLON,
			TILDE,
			TYPECAST,
			UNKNOWN,
			VISIBILITY,
			WHITESPACE
		};
	};

public:
	Token();
	explicit Token(Type::E type, bool isOptional = false);
	Token(Type::E type, const char* content);
	Token(Type::E type, std::string content);
	Token(Category::E category, Type::E type, std::string content, Common::Position pos, bool isOptional = false);

public:
	Category::E category() const;
	void category(Category::E category);

	const std::string& content() const;
	const Common::Position& position() const;
	Type::E type() const;

public:
	bool isOptional() const;
	void setOptional(bool state);

	void resetContentTo(const std::string& c);
	void resetTypeTo(Type::E type);

	std::string toString() const;

protected:

private:
	Category::E mCategory;
	std::string mContent;
	bool mIsOptional;
	Common::Position mPosition;
	Type::E mType;
};


typedef std::list<Token> TokenList;
typedef std::list<TokenList> TokenStack;
typedef TokenList::const_iterator TokenIterator;
typedef TokenList::iterator TokenIteratorMutable;


}


#endif
