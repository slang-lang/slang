
#ifndef ObjectiveScript_Utils_Exceptions_h
#define ObjectiveScript_Utils_Exceptions_h


// Library includes
#include <exception>
#include <string>

// Project includes
#include "Position.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Utils {


class Exception : public std::exception
{
public:
	Exception(const std::string& text, const Utils::Position& position = Utils::Position())
	: mPosition(position),
	  mText(text)
	{ }
	virtual ~Exception() throw() { }

public:
#ifdef _WIN32
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
    // Other kinds of Mac OS X
    const char* what() const _NOEXCEPT {
    	std::string result = mText;

		if ( mPosition.line != 0 ) {
			//result += " at line " + Tools::toString(mPosition.line) + ", " + Tools::toString(mPosition.column);
			//result += " ";
		}

        return result.c_str();
    }
#else
    // Unsupported platform
#endif
#elif defined __linux
	virtual const char* what() const throw() {
		return mText.c_str();
	}
#endif

protected:

private:
	Utils::Position mPosition;
	std::string mText;
};


class AssertionFailed : public Exception
{
public:
	AssertionFailed(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("assertion failed: " + text, position)
	{ }

	virtual ~AssertionFailed() throw() { }
};


class ConstCorrectnessViolated : public Exception
{
public:
	ConstCorrectnessViolated(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("const correctness violated: " + text, position)
	{ }

	virtual ~ConstCorrectnessViolated() throw() { }
};


class DuplicateIdentifer : public Exception
{
public:
	DuplicateIdentifer(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("duplicate identifier: " + text, position)
	{ }

	virtual ~DuplicateIdentifer() throw() { }
};


class NotImplemented : public Exception
{
public:
	NotImplemented(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("tried to execute not implemented feature: " + text, position)
	{ }

	virtual ~NotImplemented() throw() { }
};


class ParameterCountMissmatch : public Exception
{
public:
	ParameterCountMissmatch(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("parameter count missmatch: " + text, position)
	{ }

	virtual ~ParameterCountMissmatch() throw() { }
};


class SyntaxError : public Exception
{
public:
	SyntaxError(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("syntax error: " + text, position)
	{ }

	virtual ~SyntaxError() throw() { }
};


class TypeMismatch : public Exception
{
public:
	TypeMismatch(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("type mismatch: " + text, position)
	{ }

	virtual ~TypeMismatch() throw() { }
};


class UnknownIdentifer : public Exception
{
public:
	UnknownIdentifer(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("unknown identifier: " + text, position)
	{ }

	virtual ~UnknownIdentifer() throw() { }
};


class VisibilityError : public Exception
{
public:
	VisibilityError(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("visibility error: " + text, position)
	{ }

	virtual ~VisibilityError() throw() { }
};


}
}


#endif
