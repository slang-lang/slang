
#ifndef Slang_Core_Core_Common_Exceptions_h
#define Slang_Core_Core_Common_Exceptions_h


// Library includes
#include <exception>
#include <string>
#include <utility>

// Project includes
#include "Position.h"

// Forward declarations

// Namespace declarations


namespace Slang {
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
	explicit Exception(std::string text, Position position = Position()) noexcept
	: mMessage(std::move(text)),
	  mPosition(std::move(position))
	{
		if ( !mPosition.toString().empty() ) {
			mMessage += " in " + mPosition.toString();
		}
	}

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
	: Exception("Abstract error: " + text, position)
	{ }
};


class AccessMode : public Exception
{
public:
	explicit AccessMode(const std::string& text, const Position& position = Position())
	: Exception("Access mode error: " + text, position)
	{ }
};


class ControlFlowException : public Exception
{
public:
	explicit ControlFlowException(const std::string& text, const Position& position = Position())
	: Exception("Control flow error: " + text, position)
	{ }
};


class ConstCorrectnessViolated : public Exception
{
public:
	explicit ConstCorrectnessViolated(const std::string& text, const Position& position = Position())
	: Exception("Const correctness violated: " + text, position)
	{ }
};


class DuplicateIdentifier : public Exception
{
public:
	explicit DuplicateIdentifier(const std::string& text, const Position& position = Position())
	: Exception("Duplicate identifier defined: " + text, position)
	{ }
};


class InvalidSymbol : public Exception
{
public:
	explicit InvalidSymbol(const std::string& text, const Position& position = Position())
	: Exception("Invalid symbol: " + text, position)
	{ }
};


class MethodNotImplemented : public Exception
{
public:
	explicit MethodNotImplemented(const std::string& text, const Position& position = Position())
	: Exception("Method not implemented: " + text, position)
	{ }
};


class NotSupported : public Exception
{
public:
	explicit NotSupported(const std::string& text, const Position& position = Position())
	: Exception("Not supported: " + text, position)
	{ }
};


class ParameterCountMismatch : public Exception
{
public:
	explicit ParameterCountMismatch(const std::string& text, const Position& position = Position())
	: Exception("Parameter count mismatch: " + text, position)
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
	: Exception("Type mismatch: " + text, position)
	{ }
};


class UnknownIdentifier : public Exception
{
public:
	explicit UnknownIdentifier(const std::string& text, const Position& position = Position())
	: Exception("Unknown identifier: " + text, position)
	{ }
};


class UnknownOperation : public Exception
{
public:
	explicit UnknownOperation(const std::string& text, const Position& position = Position())
	: Exception("Unknown operation: " + text, position)
	{ }
};


class VisibilityError : public Exception
{
public:
	explicit VisibilityError(const std::string& text, const Position& position = Position())
	: Exception("Visibility error: " + text, position)
	{ }
};


}
}
}


#endif
