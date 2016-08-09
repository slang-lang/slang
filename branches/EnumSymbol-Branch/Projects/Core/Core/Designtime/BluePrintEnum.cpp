
// Header
#include "BluePrintEnum.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintEnum::BluePrintEnum()
: EnumSymbol(ANONYMOUS_OBJECT)
{
	mName = ANONYMOUS_OBJECT;
}

BluePrintEnum::BluePrintEnum(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  EnumSymbol(type)
{
	mName = name;
}

BluePrintEnum::~BluePrintEnum()
{
}

ISymbol::IType::E BluePrintEnum::getSymbolType() const
{
	return ISymbol::IType::EnumSymbol;
}

const std::string& BluePrintEnum::QualifiedTypename() const
{
	return mQualifiedTypename;
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
