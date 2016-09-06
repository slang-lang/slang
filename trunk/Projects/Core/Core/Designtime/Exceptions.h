
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
	DesigntimeException(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("Exception.Designtime: " + text, position)
	{ }

	virtual ~DesigntimeException() throw() { }
};



class LawOfDemeterViolated : public DesigntimeException
{
public:
	LawOfDemeterViolated(const std::string& text, const Common::Position& position = Common::Position())
	: DesigntimeException("Exception.Designtime.LawOfDemeterViolated: " + text, position)
	{ }

	virtual ~LawOfDemeterViolated() throw() { }
};


}
}
}


#endif
