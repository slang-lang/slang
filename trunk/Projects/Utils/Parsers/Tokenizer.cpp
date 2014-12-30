
// Header
#include "Tokenizer.h"

// Library includes

// Project includes
#include <Tools/Strings.h>

// Namespace declarations


namespace Utils {


const std::string Tokenizer::DELIMITERS(" \t\n\r;");


Tokenizer::Tokenizer(const std::string& s, const std::string& delimiters)
: mDelimiters( !delimiters.empty() ? delimiters : DELIMITERS ),
  mOffset(0),
  mString(s),
  mToken("")
{
}

const std::string Tokenizer::getRemainingString() const
{
	std::string result = Tools::stringTrim(mString.substr(mOffset, mString.length()));
	return result;
}

const std::string Tokenizer::getString() const
{
	return mString;
}

const std::string Tokenizer::getToken() const
{
	return mToken;
}

bool Tokenizer::hasNext() 
{
    return nextToken(mDelimiters);
}

bool Tokenizer::nextToken(const std::string& delimiters) 
{
    size_t i = mString.find_first_not_of(delimiters, mOffset);

	if ( std::string::npos == i ) {
        mOffset = mString.length();

        return false;
    }

    size_t j = mString.find_first_of(delimiters, i);

	if ( std::string::npos == j ) {
        mToken = mString.substr(i);
        mOffset = mString.length();

        return true;
    }

    mToken = mString.substr(i, j - i);
    mOffset = j;

    return true;
}

void Tokenizer::reset()
{
	mOffset = 0;
	mToken = "";
}


}
