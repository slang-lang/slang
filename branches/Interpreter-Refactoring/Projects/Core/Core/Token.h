
#ifndef ObjectiveScript_Core_Token_h
#define ObjectiveScript_Core_Token_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Common/Position.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


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
			ReservedWord,
			Operator
		};
	};

	class Type
	{
	public:
		enum E {
			AND,
			ASSIGN,
			ASSIGN_ADDITION,
			ASSIGN_BITCOMPLEMENT,
			ASSIGN_DIVIDE,
			ASSIGN_MODULO,
			ASSIGN_MULTIPLY,
			ASSIGN_SUBTRACT,
			BACKSLASH,
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
			COMPARE_LESS,
			COMPARE_LESS_EQUAL,
			COMPARE_GREATER,
			COMPARE_GREATER_EQUAL,
			COMPARE_UNEQUAL,
			CONST_BOOLEAN,
			CONST_DOUBLE,
			CONST_FLOAT,
			CONST_INTEGER,
			CONST_LITERAL,
			CONST_NUMBER,
			DASH,
			ENDOFFILE,
			GREATER,
			IDENTIFER,
			KEYWORD,
			LABEL,
			LANGUAGEFEATURE,
			LESS,
			MATH_ADDITION,
			MATH_DIVIDE,
			MATH_MODULO,
			MATH_MULTIPLY,
			MATH_SUBTRACT,
			MODIFIER,
			NAND,
			NIL,
			NOR,
			OPERATOR_DECREMENT,
			OPERATOR_INCREMENT,
			OPERATOR_IS,
			OPERATOR_NOT,
			OR,
			PARENTHESIS_CLOSE,
			PARENTHESIS_OPEN,
			PROTOTYPE,
			QUOTATION_DOUBLE,
			QUOTATION_SINGLE,
			RESERVED_WORD,
			SCOPE,
			SEMICOLON,
			SLASH,
			TILDE,
			TYPE,
			UNKNOWN,
			VISIBILITY,
			WHITESPACE
		};
	};

public:
	Token();
	Token(Type::E type, bool isOptional = false);
	Token(Type::E type, const std::string& content);
	Token(Category::E category, Type::E type, const std::string& content, const Common::Position& pos);

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
