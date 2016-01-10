
// Header
#include "Symbol.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Symbol::Symbol(const std::string& name, IType::E type)
: mName(name),
  mType(type)
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

Symbol::IType::E Symbol::getType() const
{
	return mType;
}


}
