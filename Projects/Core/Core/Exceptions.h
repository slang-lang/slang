
#ifndef ObjectiveScript_Exceptions_h
#define ObjectiveScript_Exceptions_h


// Library includes
#include <exception>
#include <string>

// Project includes
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Exception : public std::exception
{
public:
	Exception(const std::string& text, const Token::Position& position = Token::Position())
	: std::exception(text.c_str()),
	  mPosition(position),
	  mText("Exception: " + text)
	{ }
	virtual ~Exception() { }

public:
	std::string what() {
		std::string result = mText;

		//if ( mPosition.line != 0 ) {
		//	result += " at line " + Tools::toString(mPosition.line);// + ", " + Tools::toString(mPosition.column);
		//}

		return result;
	}

protected:

private:
	Token::Position mPosition;
    std::string	mText;
};


class AssertionFailed : public Exception
{
public:
	AssertionFailed(const std::string& text, const Token::Position& position = Token::Position())
	: Exception("assertion failed: " + text, position)
	{ }
};


class DuplicateIdentifer : public Exception
{
public:
	DuplicateIdentifer(const std::string& text, const Token::Position& position = Token::Position())
	: Exception("duplicate identifier: " + text, position)
	{ }
};


class ParameterCountMissmatch : public Exception
{
public:
	ParameterCountMissmatch(const std::string& text, const Token::Position& position = Token::Position())
	: Exception("parameter count missmatch: " + text, position)
	{ }
};


class SyntaxError : public Exception
{
public:
	SyntaxError(const std::string& text, const Token::Position& position = Token::Position())
	: Exception("syntax error: " + text, position)
	{ }
};


class TypeMismatch : public Exception
{
public:
	TypeMismatch(const std::string& text, const Token::Position& position = Token::Position())
	: Exception("type mismatch: " + text, position)
	{ }
};


class UnknownIdentifer : public Exception
{
public:
	UnknownIdentifer(const std::string& text, const Token::Position& position = Token::Position())
	: Exception("unknown identifier: " + text, position)
	{ }
};


class VisibilityError : public Exception
{
public:
	VisibilityError(const std::string& text, const Token::Position& position = Token::Position())
	: Exception("visibility error: " + text, position)
	{ }
};


}


#endif
