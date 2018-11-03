
#ifndef ObjectiveScript_Designtime_Exceptions_h
#define ObjectiveScript_Designtime_Exceptions_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {
namespace Exceptions {


class DesigntimeException : public ObjectiveScript::Common::Exceptions::Exception
{
public:
	explicit DesigntimeException(const std::string& text, const Common::Position& position = Common::Position()) noexcept
	: ObjectiveScript::Common::Exceptions::Exception(text, position)
	{ }
};


class LawOfDemeterViolated : public DesigntimeException
{
public:
	explicit LawOfDemeterViolated(const std::string& text, const Common::Position& position = Common::Position()) noexcept
	: DesigntimeException("Law Of Demeter violated: " + text, position)
	{ }
};


class SanityCheckError : public DesigntimeException
{
public:
	explicit SanityCheckError(const std::string& text, const Common::Position& position = Common::Position())
	: DesigntimeException("Sanity check error: " + text, position)
	{ }
};


class SyntaxError : public DesigntimeException
{
public:
	explicit SyntaxError(const std::string& text, const Common::Position& position = Common::Position())
	: DesigntimeException("Syntax error: " + text, position)
	{ }
};


}
}
}


#endif
