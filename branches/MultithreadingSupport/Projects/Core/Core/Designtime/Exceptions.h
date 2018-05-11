
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

#ifdef _WIN32
class DesigntimeException : public ObjectiveScript::Common::Exceptions::Exception
{
public:
	explicit DesigntimeException(const std::string& text, const Common::Position& position = Common::Position())
	: Exception("DesigntimeException: " + text, position)
	{ }

	virtual ~DesigntimeException() { }
};
#else
class DesigntimeException : public ObjectiveScript::Common::Exceptions::Exception
{
public:
	explicit DesigntimeException(const std::string& text, const Common::Position& position = Common::Position()) noexcept
	: Exception("DesigntimeException: " + text, position)
	{ }

	virtual ~DesigntimeException() noexcept { }
};
#endif


#ifdef _WIN32
class LawOfDemeterViolated : public DesigntimeException
{
public:
	explicit LawOfDemeterViolated(const std::string& text, const Common::Position& position = Common::Position())
	: DesigntimeException("LawOfDemeterViolatedException: " + text, position)
	{ }

	virtual ~LawOfDemeterViolated() { }
};
#else
class LawOfDemeterViolated : public DesigntimeException
{
public:
	explicit LawOfDemeterViolated(const std::string& text, const Common::Position& position = Common::Position()) noexcept
	: DesigntimeException("LawOfDemeterViolatedException: " + text, position)
	{ }

	virtual ~LawOfDemeterViolated() noexcept { }
};
#endif


}
}
}


#endif
