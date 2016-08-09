
// Header
#include "BluePrintEnum.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintEnum::BluePrintEnum()
: EnumSymbol(ANONYMOUS_OBJECT),
  mParent(0)
{
	mName = ANONYMOUS_OBJECT;
}

BluePrintEnum::BluePrintEnum(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  EnumSymbol(type),
  mParent(0)
{
	mName = name;
}

BluePrintEnum::~BluePrintEnum()
{
}

IScope* BluePrintEnum::getParent() const
{
	return mParent;
}

ISymbol::IType::E BluePrintEnum::getSymbolType() const
{
	return ISymbol::IType::EnumSymbol;
}

const std::string& BluePrintEnum::QualifiedTypename() const
{
	return mQualifiedTypename;
}

void BluePrintEnum::setParent(IScope* parent)
{
	mParent = parent;
}

const std::string& BluePrintEnum::Typename() const
{
	return mTypename;
}

std::string BluePrintEnum::ToString() const
{
	return Typename() + " " + getName();
}



}
}
