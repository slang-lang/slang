
#ifndef ObjectiveScript_Designtime_Exceptions_h
#define ObjectiveScript_Designtime_Exceptions_h


// Library includes

// Project includes
#include <Common/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {
namespace Exceptions {


class DesigntimeException : public ObjectiveScript::Common::Exceptions::Exception
{
public:
	DesignTimeException(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("Designtime.Exception: " + text, position)
	{ }

	virtual ~DesigntimeException() throw() { }
};


}
}
}


#endif
