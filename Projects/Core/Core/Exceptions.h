
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
	: mPosition(position),
	  mText(text)
	{ }
	virtual ~Exception() throw() { }

public:
#ifdef __WIN32
	const char* what() const {
		return mText.c_str();
	}
#elif defined __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
    // iOS Simulator
#elif TARGET_OS_IPHONE
    // iOS device
    const char* what() const throw() {
        return mText.c_str();
    }
#elif TARGET_OS_MAC
    // Other kinds of Mac OS
    const char* what() const _NOEXCEPT {
		//if ( mPosition.line != 0 ) {
		//	result += " at line " + Tools::toString(mPosition.line);// + ", " + Tools::toString(mPosition.column);
		//}

        return mText.c_str();
    }
#else
    // Unsupported platform
#endif
#elif defined __linux
	virtual const char* what() const throw () {
		return mText.c_str();
	}
#endif

protected:

private:
	Token::Position mPosition;
	std::string mText;
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
