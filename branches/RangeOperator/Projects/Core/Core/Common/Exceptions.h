
#ifndef ObjectiveScript_Core_Common_Exceptions_h
#define ObjectiveScript_Core_Common_Exceptions_h


// Library includes
#include <exception>
#include <string>

// Project includes
#include "Position.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Common {
namespace Exceptions {


class Exception : public std::exception
{
public:
#ifdef _WIN32
	explicit Exception(const std::string& text, const Position& position = Position())
	: mMessage(text),
	  mPosition(position)
	{
		if ( !mPosition.toString().empty() ) {
			mMessage += " in " + mPosition.toString();
		}
	}
	virtual ~Exception() { }
#else
	explicit Exception(const std::string& text, const Position& position = Position()) noexcept
	: mMessage(text),
	  mPosition(position)
	{
		if ( !mPosition.toString().empty() ) {
			mMessage += " in " + mPosition.toString();
		}
	}
	virtual ~Exception() noexcept { }
#endif

public:
#ifdef _WIN32
	const char* what() const {
		return mMessage.c_str();
	}
#elif defined __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
    // Other kinds of Mac OS X
    const char* what() const noexcept override {
    	return mMessage.c_str();
    }
#else
    // Unsupported platform
#endif
#elif defined __linux
	virtual const char* what() const noexcept {
		return mMessage.c_str();
	}
#endif

protected:

private:
	std::string mMessage;
	Position mPosition;
};


class AbstractException : public Exception
{
public:
	explicit AbstractException(const std::string& text, const Position& position = Position())
	: Exception("AbstractException: " + text, position)
	{ }
};


class AccessMode : public Exception
{
public:
	explicit AccessMode(const std::string& text, const Position& position = Position())
	: Exception("AccessModeException: " + text, position)
	{ }
};


class ControlFlowException : public Exception
{
public:
	explicit ControlFlowException(const std::string& text, const Position& position = Position())
	: Exception("ControlFlowException: " + text, position)
	{ }
};


class ConstCorrectnessViolated : public Exception
{
public:
	explicit ConstCorrectnessViolated(const std::string& text, const Position& position = Position())
	: Exception("ConstCorrectnessViolated: " + text, position)
	{ }
};


class DuplicateIdentifier : public Exception
{
public:
	explicit DuplicateIdentifier(const std::string& text, const Position& position = Position())
	: Exception("DuplicateIdentifier: " + text, position)
	{ }
};


class InvalidSymbol : public Exception
{
public:
	explicit InvalidSymbol(const std::string& text, const Position& position = Position())
	: Exception("InvalidSymbol: " + text, position)
	{ }
};


class NotImplemented : public Exception
{
public:
	explicit NotImplemented(const std::string& text, const Position& position = Position())
	: Exception("NotImplemented: " + text, position)
	{ }
};


class NotSupported : public Exception
{
public:
	explicit NotSupported(const std::string& text, const Position& position = Position())
	: Exception("NotSupported: " + text, position)
	{ }
};


class ParameterCountMissmatch : public Exception
{
public:
	explicit ParameterCountMissmatch(const std::string& text, const Position& position = Position())
	: Exception("ParameterCountMissmatch: " + text, position)
	{ }
};


class StaticException : public Exception
{
public:
	explicit StaticException(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("StaticException: " + text, position)
	{ }
};


class TypeMismatch : public Exception
{
public:
	explicit TypeMismatch(const std::string& text, const Position& position = Position())
	: Exception("TypeMismatch: " + text, position)
	{ }
};


class UnknownIdentifer : public Exception
{
public:
	explicit UnknownIdentifer(const std::string& text, const Position& position = Position())
	: Exception("UnknownIdentifer: " + text, position)
	{ }
};


class UnknownOperation : public Exception
{
public:
	explicit UnknownOperation(const std::string& text, const Position& position = Position())
	: Exception("UnknownOperation: " + text, position)
	{ }
};


class VisibilityError : public Exception
{
public:
	explicit VisibilityError(const std::string& text, const Position& position = Position())
	: Exception("VisibilityError: " + text, position)
	{ }
};


}
}
}


#endif
