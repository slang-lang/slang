
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


class Exception : public ObjectiveScript::Common::Exceptions::Exception
{
public:
	Exception(const std::string& text, const ObjectiveScript::Common::Position& position = ObjectiveScript::Common::Position())
	: ObjectiveScript::Common::Exceptions::Exception("Runtime." + text, position)
	{ }

	virtual ~Exception() throw() { }
};



class AccessViolation : public Exception
{
public:
	AccessViolation(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("AccessViolationException: " + text, position)
	{ }

	virtual ~AccessViolation() throw() { }
};


class AssertionFailed : public Exception
{
public:
	AssertionFailed(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("AssertionFailedException: " + text, position)
	{ }

	virtual ~AssertionFailed() throw() { }
};


class ExplicitCastRequired : public Exception
{
public:
	ExplicitCastRequired(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("ExplicitCastRequiredException: " + text, position)
	{ }

	virtual ~ExplicitCastRequired() throw() { }
};


class InvalidAssignment : public Exception
{
public:
	InvalidAssignment(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("InvalidAssignment: " + text, position)
	{ }

	virtual ~InvalidAssignment() throw() { }
};


class InvalidTypeCast : public Exception
{
public:
	InvalidTypeCast(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("InvalidTypeCastException: " + text, position)
	{ }

	virtual ~InvalidTypeCast() throw() { }
};


class NullPointerException : public Exception
{
public:
	NullPointerException(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("NullPointerException: " + text, position)
	{ }

	virtual ~NullPointerException() throw() { }
};


	class SizeException : public Exception
{
public:
	SizeException(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("SizeException: " + text, position)
	{ }

	virtual ~SizeException() throw() { }
};


}
}
}


#endif
