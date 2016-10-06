
// Header
#include "Watch.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Watch::Watch()
{
}

Watch::Watch(const std::string& symbol)
: mSymbol(symbol)
{
}

Watch::~Watch()
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
