
// Header
#include "Valueizer.h"

// Library includes

// Project includes

// Namespace declarations


namespace Utils {


Valueizer::Valueizer(const std::string& s)
: Tokenizer(s)
{
}

Valueizer::Valueizer(const std::string& str, const std::string& delimiters)
: Tokenizer(str, delimiters)
{
}

Value Valueizer::getTokenAsValue() const
{
	return Value("", "", mToken);
}


} // namespace Utils

