
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

Valueizer::Valueizer(const std::string& s, const std::string& delimiters)
: Tokenizer(s, delimiters)
{
}

const Value Valueizer::getTokenAsValue() const
{
	return Value("", "", mToken);
}


}

