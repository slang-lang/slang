
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


class RuntimeException : public ::ObjectiveScript::Common::Exceptions::Exception
{
public:
	RuntimeException(const std::string& text, const ObjectiveScript::Common::Position& position = ObjectiveScript::Common::Position())
	: ::ObjectiveScript::Common::Exceptions::Exception("Runtime." + text, position)
	{ }

	virtual ~RuntimeException() throw() { }
};



class AccessViolation : public RuntimeException
{
public:
	AccessViolation(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("AccessViolationException: " + text, position)
	{ }

	virtual ~AccessViolation() throw() { }
};


class AssertionFailed : public RuntimeException
{
public:
	AssertionFailed(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("AssertionFailedException: " + text, position)
	{ }

	virtual ~AssertionFailed() throw() { }
};


class ExplicitCastRequired : public RuntimeException
{
public:
	ExplicitCastRequired(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("ExplicitCastRequiredException: " + text, position)
	{ }

	virtual ~ExplicitCastRequired() throw() { }
};


class InvalidAssignment : public RuntimeException
{
public:
	InvalidAssignment(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("InvalidAssignment: " + text, position)
	{ }

	virtual ~InvalidAssignment() throw() { }
};


class InvalidSymbol : public RuntimeException
{
public:
	InvalidSymbol(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("InvalidSymbol: " + text, position)
	{ }

	virtual ~InvalidSymbol() throw() { }
};


class NullPointerException : public RuntimeException
{
public:
	NullPointerException(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("NullPointerException: " + text, position)
	{ }

	virtual ~NullPointerException() throw() { }
};


class SizeException : public RuntimeException
{
public:
	SizeException(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("SizeException: " + text, position)
	{ }

	virtual ~SizeException() throw() { }
};


class TypeCastException : public RuntimeException
{
public:
	TypeCastException(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("TypeCastException: " + text, position)
	{ }

	virtual ~TypeCastException() throw() { }
};



}
}
}


#endif
