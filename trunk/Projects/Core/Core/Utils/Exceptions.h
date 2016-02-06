
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
namespace Exceptions {


class Exception : public std::exception
{
public:
	Exception(const std::string& text, const Utils::Position& position = Utils::Position())
	: mMessage(text),
	  mPosition(position)
	{
		if ( !mPosition.toString().empty() ) {
			mMessage += " in " + mPosition.toString();
		}
	}
	virtual ~Exception() throw() { }

public:
#ifdef _WIN32
	const char* what() const {
		return mMessage.c_str();
	}
#elif defined __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
    // iOS Simulator
#elif TARGET_OS_IPHONE
    // iOS device
    const char* what() const throw() {
        return mMessage.c_str();
    }
#elif TARGET_OS_MAC
    // Other kinds of Mac OS X
    const char* what() const _NOEXCEPT {
    	return mMessage.c_str();
    }
#else
    // Unsupported platform
#endif
#elif defined __linux
	virtual const char* what() const throw() {
		return mMessage.c_str();
	}
#endif

protected:

private:
	std::string mMessage;
	Utils::Position mPosition;
};


class AbstractException : public Exception
{
public:
	AbstractException(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.AbstractException: " + text, position)
	{ }

	virtual ~AbstractException() throw() { }
};


class AccessMode : public Exception
{
public:
	AccessMode(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.AccessMode: " + text, position)
	{ }

	virtual ~AccessMode() throw() { }
};


class AssertionFailed : public Exception
{
public:
	AssertionFailed(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.AssertionFailed: " + text, position)
	{ }

	virtual ~AssertionFailed() throw() { }
};


class ConstCorrectnessViolated : public Exception
{
public:
	ConstCorrectnessViolated(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.ConstCorrectnessViolated: " + text, position)
	{ }

	virtual ~ConstCorrectnessViolated() throw() { }
};


class DuplicateIdentifer : public Exception
{
public:
	DuplicateIdentifer(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.DuplicateIdentifer: " + text, position)
	{ }

	virtual ~DuplicateIdentifer() throw() { }
};


class InvalidTypeCast : public Exception
{
public:
	InvalidTypeCast(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.InvalidTypeCast: " + text, position)
	{ }

	virtual ~InvalidTypeCast() throw() { }
};


class NotImplemented : public Exception
{
public:
	NotImplemented(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.NotImplemented: " + text, position)
	{ }

	virtual ~NotImplemented() throw() { }
};


class NotSupported : public Exception
{
public:
	NotSupported(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.NotSupported: " + text, position)
	{ }

	virtual ~NotSupported() throw() { }
};


class NullPointer : public Exception
{
public:
	NullPointer(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.NullPointer: " + text, position)
	{ }

	virtual ~NullPointer() throw() { }
};


class ParameterCountMissmatch : public Exception
{
public:
	ParameterCountMissmatch(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.ParameterCountMissmatch: " + text, position)
	{ }

	virtual ~ParameterCountMissmatch() throw() { }
};


class SyntaxError : public Exception
{
public:
	SyntaxError(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.SyntaxError: " + text, position)
	{ }

	virtual ~SyntaxError() throw() { }
};


class TypeMismatch : public Exception
{
public:
	TypeMismatch(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.TypeMismatch: " + text, position)
	{ }

	virtual ~TypeMismatch() throw() { }
};


class UnknownIdentifer : public Exception
{
public:
	UnknownIdentifer(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.UnknownIdentifer: " + text, position)
	{ }

	virtual ~UnknownIdentifer() throw() { }
};


class VisibilityError : public Exception
{
public:
	VisibilityError(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.Visibility: " + text, position)
	{ }

	virtual ~VisibilityError() throw() { }
};


}
}
}


#endif
