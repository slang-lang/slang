
#ifndef Slang_Core_Core_Designtime_Exceptions_h
#define Slang_Core_Core_Designtime_Exceptions_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {
namespace Exceptions {


class DesigntimeException : public Slang::Common::Exceptions::Exception
{
public:
#ifdef _WIN32
	explicit DesigntimeException(const std::string& text, const Common::Position& position = Common::Position())
	: Slang::Common::Exceptions::Exception("DesigntimeException: " + text, position)
	{ }

	virtual ~DesigntimeException() { }
#else
	explicit DesigntimeException(const std::string& text, const Common::Position& position = Common::Position()) noexcept
	: Slang::Common::Exceptions::Exception(text, position)
	{ }
#endif
};


class LawOfDemeterViolated : public DesigntimeException
{
public:
	explicit LawOfDemeterViolated(const std::string& text, const Common::Position& position = Common::Position())
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
