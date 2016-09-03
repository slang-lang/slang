
// Header
#include "BluePrintEnum.h"

// Library includes

// Project includes
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintEnum::BluePrintEnum()
: mParent(0)
{
	mName = ANONYMOUS_OBJECT;
	mType = Symbol::IType::BluePrintEnumSymbol;
}

BluePrintEnum::BluePrintEnum(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  mParent(0)
{
	mName = name;
	mType = Symbol::IType::BluePrintEnumSymbol;
}

BluePrintEnum::~BluePrintEnum()
{
}

IScope* BluePrintEnum::getParent() const
{
	return mParent;
}

void BluePrintEnum::setParent(IScope* parent)
{
	mParent = parent;
}

std::string BluePrintEnum::ToString(unsigned int indent) const
{
	return ::Utils::Tools::indent(indent) + Typename() + " " + getName();
}



}
}
