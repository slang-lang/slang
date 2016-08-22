
#ifndef ObjectiveScript_Runtime_Exceptions_h
#define ObjectiveScript_Runtime_Exceptions_h


// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class SizeException : public ObjectiveScript::Utils::Exceptions::Exception
{
public:
	SizeException(const std::string& text, const Utils::Position& position = Utils::Position())
	: Exception("Exception.SizeException: " + text, position)
	{ }

	virtual ~SizeException() throw() { }
};



}
}


#endif
