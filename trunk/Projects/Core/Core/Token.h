
#ifndef ObjectiveScript_Token_h
#define ObjectiveScript_Token_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Utils/Position.h>

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
			Modifier,
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
			COMPARE_EQUAL,
			COMPARE_LESS,
			COMPARE_LESS_EQUAL,
			COMPARE_GREATER,
			COMPARE_GREATER_EQUAL,
			COMPARE_UNEQUAL,
			CONST_BOOLEAN,
			CONST_FLOAT,
			CONST_INTEGER,
			CONST_LITERAL,
			CONST_NUMBER,
			DASH,
			DECREMENT,
			DOT,
			ENDOFFILE,
			GREATER,
			IDENTIFER,
			INCREMENT,
			KEYWORD,
			LABEL,
			LANGUAGEFEATURE,
			LESS,
			MATH_ADDITION,
			MATH_DIVIDE,
			MATH_MODULO,
			MATH_MULTIPLY,
			MATH_SUBTRACT,
			NIL,
			NOT,
			OR,
			PARENTHESIS_CLOSE,
			PARENTHESIS_OPEN,
			PROTOTYPE,
			QUOTATION_DOUBLE,
			QUOTATION_SINGLE,
			RESERVED,
			SEMICOLON,
			SLASH,
			STRING,
			TYPE,
			UNKNOWN,
			VISIBILITY,
			WHITESPACE
		};

		static std::string convert(E e) {
			switch ( e ) {
				case AND: return "&&";
				case ASSIGN: return "=";
				case ASSIGN_ADDITION: return "+=";
				case ASSIGN_BITCOMPLEMENT: return "~=";
				case ASSIGN_DIVIDE: return "/=";
				case ASSIGN_MODULO: return "%=";
				case ASSIGN_MULTIPLY: return "*=";
				case ASSIGN_SUBTRACT: return "-=";
				case BACKSLASH: return "\\";
				case BRACKET_CLOSE: return "]";
				case BRACKET_CURLY_CLOSE: return "}";
				case BRACKET_CURLY_OPEN: return "{";
				case BRACKET_OPEN: return "[";
				case BITAND: return "&";
				case BITCOMPLEMENT: return "~";
				case BITOR: return "|";
				case CASE: return "CASE";
				case COLON: return ",";
				case COMPARE_EQUAL: return "==";
				case COMPARE_LESS: return "<";
				case COMPARE_LESS_EQUAL: return "<=";
				case COMPARE_GREATER: return ">";
				case COMPARE_GREATER_EQUAL: return ">=";
				case COMPARE_UNEQUAL: return "!=";
				case CONST_BOOLEAN: return "CONST_BOOLEAN";
				case CONST_FLOAT: return "CONST_FLOAT";
				case CONST_INTEGER: return "CONST_INTEGER";
				case CONST_LITERAL: return "CONST_LITERAL";
				case CONST_NUMBER: return "CONST_NUMBER";
				case DASH: return "-";
				case DECREMENT: return "--";
				case DOT: return ".";
				case ENDOFFILE: return "<EOF>";
				case GREATER: return ">";
				case IDENTIFER: return "IDENTIFER";
				case INCREMENT: return "++";
				case LABEL: return "LABEL";
				case LANGUAGEFEATURE: return "LANGUAGEFEATURE";
				case KEYWORD: return "KEYWORD";
				case LESS: return "<";
				case MATH_ADDITION: return "+";
				case MATH_DIVIDE: return "/";
				case MATH_MODULO: return "%";
				case MATH_MULTIPLY: return "*";
				case MATH_SUBTRACT: return "-";
				case NIL: return "NIL";
				case NOT: return "!";
				case OR: return "||";
				case PARENTHESIS_CLOSE: return ")";
				case PARENTHESIS_OPEN: return "(";
				case PROTOTYPE: return "PROTOTYPE";
				case QUOTATION_DOUBLE: return "\"";
				case QUOTATION_SINGLE: return "'";
				case RESERVED: return "RESERVED";
				case SEMICOLON: return ";";
				case SLASH: return "/";
				case STRING: return "STRING";
				case TYPE: return "TYPE";
				case UNKNOWN: return "UNKNOWN";
				case VISIBILITY: return "VISIBILITY";
				case WHITESPACE: return "WHITESPACE";
			}

			return "unknown token type";
		}
	};

public:
	Token(Type::E type, bool isOptional = false);
	Token(Type::E type, const std::string& content);
	Token(Category::E category, Type::E type, const std::string& content, const Utils::Position& pos);

public:
	Category::E category() const;
	void category(Category::E category);

	const std::string& content() const;
	const Utils::Position& position() const;
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
	Utils::Position mPosition;
	Type::E mType;
};


typedef std::list<Token> TokenList;
typedef TokenList::const_iterator TokenIterator;
typedef TokenList::iterator TokenIteratorMutable;


}


#endif
