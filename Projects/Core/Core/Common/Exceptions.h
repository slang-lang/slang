
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
	explicit Exception(const std::string& text, const Position& position = Position())
	: mMessage(text),
	  mPosition(position)
	{
		if ( !mPosition.toString().empty() ) {
			mMessage += " in " + mPosition.toString();
		}
	}
	virtual ~Exception() noexcept override { }

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

	virtual ~AbstractException() { }
};


class AccessMode : public Exception
{
public:
	explicit AccessMode(const std::string& text, const Position& position = Position())
	: Exception("AccessModeException: " + text, position)
	{ }

	virtual ~AccessMode() { }
};


class ControlFlowException : public Exception
{
public:
	explicit ControlFlowException(const std::string& text, const Position& position = Position())
	: Exception("ControlFlowException: " + text, position)
	{ }

	virtual ~ControlFlowException() { }
};


class ConstCorrectnessViolated : public Exception
{
public:
	explicit ConstCorrectnessViolated(const std::string& text, const Position& position = Position())
	: Exception("ConstCorrectnessViolated: " + text, position)
	{ }

	virtual ~ConstCorrectnessViolated() { }
};


class DuplicateIdentifier : public Exception
{
public:
	explicit DuplicateIdentifier(const std::string& text, const Position& position = Position())
	: Exception("DuplicateIdentifier: " + text, position)
	{ }

	virtual ~DuplicateIdentifier() { }
};


class InvalidSymbol : public Exception
{
public:
	explicit InvalidSymbol(const std::string& text, const Position& position = Position())
	: Exception("InvalidSymbol: " + text, position)
	{ }

	virtual ~InvalidSymbol() { }
};


class NotImplemented : public Exception
{
public:
	explicit NotImplemented(const std::string& text, const Position& position = Position())
	: Exception("NotImplemented: " + text, position)
	{ }

	virtual ~NotImplemented() { }
};


class NotSupported : public Exception
{
public:
	explicit NotSupported(const std::string& text, const Position& position = Position())
	: Exception("NotSupported: " + text, position)
	{ }

	virtual ~NotSupported() { }
};


class ParameterCountMissmatch : public Exception
{
public:
	explicit ParameterCountMissmatch(const std::string& text, const Position& position = Position())
	: Exception("ParameterCountMissmatch: " + text, position)
	{ }

	virtual ~ParameterCountMissmatch() { }
};


class StaticException : public Exception
{
public:
	explicit StaticException(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("StaticException: " + text, position)
	{ }

	virtual ~StaticException() { }
};


class SyntaxError : public Exception
{
public:
	explicit SyntaxError(const std::string& text, const Position& position = Position())
	: Exception("SyntaxError: " + text, position)
	{ }

	virtual ~SyntaxError() { }
};


class TypeMismatch : public Exception
{
public:
	explicit TypeMismatch(const std::string& text, const Position& position = Position())
	: Exception("TypeMismatch: " + text, position)
	{ }

	virtual ~TypeMismatch() { }
};


class UnknownIdentifer : public Exception
{
public:
	explicit UnknownIdentifer(const std::string& text, const Position& position = Position())
	: Exception("UnknownIdentifer: " + text, position)
	{ }

	virtual ~UnknownIdentifer() { }
};


class UnknownOperation : public Exception
{
public:
	explicit UnknownOperation(const std::string& text, const Position& position = Position())
	: Exception("UnknownOperation: " + text, position)
	{ }

	virtual ~UnknownOperation() { }
};


class VisibilityError : public Exception
{
public:
	explicit VisibilityError(const std::string& text, const Position& position = Position())
	: Exception("VisibilityError: " + text, position)
	{ }

	virtual ~VisibilityError() { }
};


}
}
}


#endif
