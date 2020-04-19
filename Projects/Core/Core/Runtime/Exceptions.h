
#ifndef ObjectiveScript_Runtime_Exceptions_h
#define ObjectiveScript_Runtime_Exceptions_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {
namespace Exceptions {


class RuntimeException : public ::Slang::Common::Exceptions::Exception
{
public:
#ifdef _WIN32
	explicit RuntimeException(const std::string& text, const Slang::Common::Position& position = Slang::Common::Position())
	: ::Slang::Common::Exceptions::Exception(text, position)
	{ }
#else
	explicit RuntimeException(const std::string& text, const Slang::Common::Position& position = Slang::Common::Position()) noexcept
	: ::Slang::Common::Exceptions::Exception(text, position)
	{ }
#endif
};


class AccessViolation : public RuntimeException
{
public:
	explicit AccessViolation(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("Access violation: " + text, position)
	{ }
};


class AssertionFailed : public RuntimeException
{
public:
	explicit AssertionFailed(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("Assertion failed: " + text, position)
	{ }
};


class ExplicitCastRequired : public RuntimeException
{
public:
	explicit ExplicitCastRequired(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("Explicit cast required: " + text, position)
	{ }
};


class InvalidAssignment : public RuntimeException
{
public:
	explicit InvalidAssignment(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("Invalid assignment: " + text, position)
	{ }
};


class InvalidOperation : public RuntimeException
{
public:
	explicit InvalidOperation(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("Invalid operation: " + text, position)
	{ }
};


class InvalidSymbol : public RuntimeException
{
public:
	explicit InvalidSymbol(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("Invalid symbol: " + text, position)
	{ }
};


class NullPointerException : public RuntimeException
{
public:
	explicit NullPointerException(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("NullPointerException: " + text, position)
	{ }
};


class SizeException : public RuntimeException
{
public:
	explicit SizeException(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("SizeException: " + text, position)
	{ }
};


class TypecastException : public RuntimeException
{
public:
	explicit TypecastException(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("TypecastException: " + text, position)
	{ }
};



}
}
}


#endif
