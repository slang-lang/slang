
#ifndef ObjectiveScript_Runtime_Exceptions_h
#define ObjectiveScript_Runtime_Exceptions_h


// Library includes

// Project includes
#include <Common/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {
namespace Exceptions {


class RuntimeException : public ObjectiveScript::Common::Exceptions::Exception
{
public:
	RuntimeException(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("Runtime.Exception: " + text, position)
	{ }

	virtual ~RuntimeException() throw() { }
};



class ExplicitCastRequired : public RuntimeException
{
public:
	ExplicitCastRequired(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("Exception.ExplicitCastRequired: " + text, position)
	{ }

	virtual ~ExplicitCastRequired() throw() { }
};

class SizeException : public RuntimeException
{
public:
	SizeException(const std::string& text, const Common::Position& position = Common::Position())
	: RuntimeException("Exception.SizeException: " + text, position)
	{ }

	virtual ~SizeException() throw() { }
};


}
}
}


#endif
