
// Header
#include "BluePrintEnum.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintEnum::BluePrintEnum()
: EnumSymbol(ANONYMOUS_OBJECT),
  mFilename(ANONYMOUS_OBJECT),
  mParent(0),
  mQualifiedTypeName(ANONYMOUS_OBJECT),
  mTypename(ANONYMOUS_OBJECT),
  mVisibility(Visibility::Public)
{
	mName = ANONYMOUS_OBJECT;
}

BluePrintEnum::BluePrintEnum(const std::string& type, const std::string& filename, const std::string& name)
: EnumSymbol(type),
  mFilename(filename),
  mParent(0),
  mQualifiedTypeName(type),
  mTypename(type),
  mVisibility(Visibility::Public)
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

const TokenList& BluePrintEnum::getTokens() const
{
	return mTokens;
}

void BluePrintEnum::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}

Runtime::AtomicValue BluePrintEnum::getValue() const
{
	return mValue;
}

Visibility::E BluePrintEnum::getVisibility() const
{
	return mVisibility;
}

void BluePrintEnum::setParent(IScope* parent)
{
	mParent = parent;
}

void BluePrintEnum::setQualifiedTypename(const std::string& name)
{
	mQualifiedTypeName = name;
}

void BluePrintEnum::setValue(Runtime::AtomicValue value)
{
	mValue = value;
}

void BluePrintEnum::setVisibility(Visibility::E v)
{
	mVisibility = v;
}

std::string BluePrintEnum::ToString() const
{
	return Typename() + " " + getName();
}



}
}
