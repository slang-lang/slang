
#ifndef ObjectiveScript_Token_h
#define ObjectiveScript_Token_h


// Library includes
#include <list>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Token
{
public:
	class Position
	{
	public:
		Position() : column(0), line(0) { }
		Position(size_t l, size_t c) : column(c), line(l) { }

	public:
		bool operator==(const Position& other) {
			return this->line == other.line && this->column == other.column;
		}

		bool operator<(const Position& other) {
			if ( this->line == other.line ) {
				return this->column < other.column;
			}
			return this->line < other.line;
		}

	public:
		size_t column;
		size_t line;
	};

	class Type
	{
	public:
		enum E {
			ASSIGN,
			ASSIGN_ADD,
			ASSIGN_DIVIDE,
			ASSIGN_MULTI,
			ASSIGN_SUBTRACT,
			BACKSLASH,
			BOOLEAN,
			BRACKET_CLOSE,
			BRACKET_CURLY_CLOSE,
			BRACKET_CURLY_OPEN,
			BRACKET_OPEN,
			CASE,
			COLON,
			COMPARE_EQUAL,
			COMPARE_LESS,
			COMPARE_LESS_EQUAL,
			COMPARE_GREATER,
			COMPARE_GREATER_EQUAL,
			COMPARE_UNEQUAL,
			CONSTANT,
			DASH,
			DOT,
			ENDOFFILE,
			EQUAL,
			GREATER,
			IDENTIFER,
			KEYWORD,
			LABEL,
			LESS,
			LITERAL,
			MATH_ADD,
			MATH_DIV,
			MATH_MULTI,
			MATH_SUBTRACT,
			NIL,
			PARENTHESIS_CLOSE,
			PARENTHESIS_OPEN,
			QUOTATION_DOUBLE,
			QUOTATION_SINGLE,
			RESERVED,
			SEMICOLON,
			SLASH,
			STRING,
			STRING_ADD,
			TYPE,
			UNKNOWN,
			VISIBILITY,
			WHITESPACE
		};

		static std::string convert(E e) {
			switch ( e ) {
				case ASSIGN: return "=";
				case ASSIGN_ADD: return "+=";
				case ASSIGN_DIVIDE: return "/=";
				case ASSIGN_MULTI: return "*=";
				case ASSIGN_SUBTRACT: return "-=";
				case BACKSLASH: return "\\";
				case BOOLEAN: return "boolean";
				case BRACKET_CLOSE: return "]";
				case BRACKET_CURLY_CLOSE: return "}";
				case BRACKET_CURLY_OPEN: return "{";
				case BRACKET_OPEN: return "[";
				case COLON: return ",";
				case COMPARE_EQUAL: return "==";
				case COMPARE_LESS: return "<";
				case COMPARE_LESS_EQUAL: return "<=";
				case COMPARE_GREATER: return ">";
				case COMPARE_GREATER_EQUAL: return ">=";
				case CONSTANT: return "number";
				case DASH: return "-";
				case DOT: return ".";
				case EQUAL: return "=";
				case GREATER: return ">";
				case IDENTIFER: return "identifier";
				case KEYWORD: return "KEYWORD";
				case LESS: return "<";
				case LITERAL: return "literal";
				case MATH_ADD: return "+";
				case MATH_DIV: return "/";
				case MATH_MULTI: return "*";
				case MATH_SUBTRACT: return "-";
				case NIL: return "NIL";
				case PARENTHESIS_CLOSE: return ")";
				case PARENTHESIS_OPEN: return "(";
				case QUOTATION_DOUBLE: return "\"";
				case QUOTATION_SINGLE: return "'";
				case RESERVED: return "reserved";
				case SEMICOLON: return ";";
				case SLASH: return "/";
				case STRING: return "STRING";
				case STRING_ADD: return "&";
				case TYPE: return "TYPE";
				case UNKNOWN: return "unknown";
				case VISIBILITY: return "visibility";
				case WHITESPACE: return "whitespace";
			}

			return "unknown type";
		}
	};

public:
	Token(Type::E type);
	Token(Type::E type, const std::string& content);
	Token(Type::E type, const std::string& content, const Position& pos);

public:
	const std::string& content() const;
	const Position& position() const;

	void resetTypeTo(Type::E type);
	Type::E type() const;

protected:

private:
	std::string	mContent;
	Position	mPosition;
	Type::E		mType;
};


typedef std::list<Token> TokenList;
typedef TokenList::const_iterator TokenIterator;
typedef TokenList::iterator TokenIteratorMutable;


}


#endif
