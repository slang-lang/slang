
// Header
#include "BluePrintEnum.h"

// Library includes

// Project includes
#include <Core/Object.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintEnum::BluePrintEnum()
: MethodScope(ANONYMOUS_OBJECT, 0)
{
	mIsAtomicType = true;
	mName = ANONYMOUS_OBJECT;
	mType = Symbol::IType::BluePrintEnumSymbol;
}

BluePrintEnum::BluePrintEnum(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  MethodScope(type, 0)
{
	mIsAtomicType = true;
	mName = name;
	mType = Symbol::IType::BluePrintEnumSymbol;
}

BluePrintEnum::~BluePrintEnum()
{
}

bool BluePrintEnum::isIterable() const
{
	return false;
}

void BluePrintEnum::setParent(IScope* parent)
{
	mParent = parent;
}

BluePrintEnum::MethodCollection BluePrintEnum::provideMethods() const
{
	return mMethods;
}

Symbols BluePrintEnum::provideSymbols() const
{
	return mSymbols;
}

std::string BluePrintEnum::ToString(unsigned int indent) const
{
	return ::Utils::Tools::indent(indent) + QualifiedTypename() + " " + getName();
}



}
}
