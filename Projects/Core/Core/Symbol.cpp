
// Header
#include "Symbol.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Symbol::Symbol(const std::string& name, IType::E type, Visibility::E visibility)
: mName(name),
  mType(type),
  mVisibility(visibility)
{
}

bool Symbol::operator==(const std::string& name) const
{
	return mName == name;
}

bool Symbol::operator< (const Symbol& other) const
{
	return mName < other.mName;
}

bool Symbol::operator< (const Symbol* other) const
{
	return mName < other->mName;
}

const std::string& Symbol::getName() const
{
	return mName;
}

Symbol::IType::E Symbol::getSymbolType() const
{
	return mType;
}

Visibility::E Symbol::getVisibility() const
{
	return mVisibility;
}

void Symbol::setVisibility(Visibility::E visibility)
{
	mVisibility = visibility;
}


}
