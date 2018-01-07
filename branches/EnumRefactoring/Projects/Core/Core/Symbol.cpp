
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

Symbol::~Symbol()
{
}

bool Symbol::operator< (const Symbol& other) const
{
	return getName() < other.getName();
}

bool Symbol::operator< (const Symbol* other) const
{
	return getName() < other->getName();
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
