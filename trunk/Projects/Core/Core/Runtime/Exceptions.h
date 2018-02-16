
#ifndef ObjectiveScript_Runtime_Exceptions_h
#define ObjectiveScript_Runtime_Exceptions_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {
namespace Exceptions {


#ifdef _WIN32
class RuntimeException : public ::ObjectiveScript::Common::Exceptions::Exception
{
public:
	explicit RuntimeException(const std::string& text, const ObjectiveScript::Common::Position& position = ObjectiveScript::Common::Position())
	: ::ObjectiveScript::Common::Exceptions::Exception(text, position)
	{ }

	virtual ~RuntimeException() { }
};
#else
class RuntimeException : public ::ObjectiveScript::Common::Exceptions::Exception
{
public:
	explicit RuntimeException(const std::string& text, const ObjectiveScript::Common::Position& position = ObjectiveScript::Common::Position()) noexcept
	: ::ObjectiveScript::Common::Exceptions::Exception(text, position)
	{ }

	virtual ~RuntimeException() noexcept { }
};
#endif


class AccessViolation : public RuntimeException
{
public:
	explicit AccessViolation(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("AccessViolation: " + text, position)
	{ }

	virtual ~AccessViolation() { }
};


class AssertionFailed : public RuntimeException
{
public:
	explicit AssertionFailed(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("AssertionFailed: " + text, position)
	{ }

	virtual ~AssertionFailed() { }
};


class ExplicitCastRequired : public RuntimeException
{
public:
	explicit ExplicitCastRequired(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("ExplicitCastRequired: " + text, position)
	{ }

	virtual ~ExplicitCastRequired() { }
};


class InvalidAssignment : public RuntimeException
{
public:
	explicit InvalidAssignment(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("InvalidAssignment: " + text, position)
	{ }

	virtual ~InvalidAssignment() { }
};


class InvalidSymbol : public RuntimeException
{
public:
	explicit InvalidSymbol(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("InvalidSymbol: " + text, position)
	{ }

	virtual ~InvalidSymbol() { }
};


class NullPointerException : public RuntimeException
{
public:
	explicit NullPointerException(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("NullPointerException: " + text, position)
	{ }

	virtual ~NullPointerException() { }
};


class SizeException : public RuntimeException
{
public:
	explicit SizeException(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("SizeException: " + text, position)
	{ }

	virtual ~SizeException() { }
};


class TypecastException : public RuntimeException
{
public:
	explicit TypecastException(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("TypecastException: " + text, position)
	{ }

	virtual ~TypecastException() { }
};



}
}
}


#endif
