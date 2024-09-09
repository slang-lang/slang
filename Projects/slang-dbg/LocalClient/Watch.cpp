
// Header
#include "Watch.h"

#include <utility>

// Library includes

// Project includes

// Namespace declarations


namespace Slang {


Watch::Watch(std::string symbol)
: mSymbol(std::move(symbol))
{
}

const std::string& Watch::symbol() const
{
	return mSymbol;
}

std::string Watch::toString() const
{
	return mSymbol + ": " + mValue;
}

const std::string& Watch::value() const
{
	return mValue;
}

void Watch::value(const std::string& v)
{
	mValue = v;
}

bool Watch::operator<(const Watch& other) const
{
	return mSymbol < other.mSymbol;
}

bool Watch::operator==(const Watch& other) const
{
	return mSymbol == other.mSymbol;
}


}
