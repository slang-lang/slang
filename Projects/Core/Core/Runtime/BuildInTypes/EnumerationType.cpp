
// Header
#include "EnumerationType.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue EnumerationType::DEFAULTVALUE = AtomicValue( static_cast<int64_t>( 0 ) );
std::string EnumerationType::TYPENAME = _enum;


EnumerationType::EnumerationType(const std::string& name, const std::string& type, const AtomicValue& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mBluePrintType = BlueprintType::Enum;
	mIsAtomicType = true;
	mQualifiedOuterface = type;
	mQualifiedTypename = type;
}

const std::string& EnumerationType::getTypeName() const
{
	return TYPENAME;
}

bool EnumerationType::isValid() const
{
	return true;
}

void EnumerationType::operator_assign(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		mValue = other->getValue().toInt();
	}

	throw Exceptions::InvalidOperation(QualifiedTypename() + ".operator=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool EnumerationType::operator_bool() const
{
	return mValue.toInt() != 0;
}

bool EnumerationType::operator_equal(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		return mValue.toInt() == other->getValue().toInt();
	}

	throw Exceptions::InvalidOperation(QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool EnumerationType::operator_greater(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		return mValue.toInt() > other->getValue().toInt();
	}

	throw Exceptions::InvalidOperation(QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool EnumerationType::operator_greater_equal(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		return mValue.toInt() >= other->getValue().toInt();
	}

	throw Exceptions::InvalidOperation(QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool EnumerationType::operator_less(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		return mValue.toInt() < other->getValue().toInt();
	}

	throw Exceptions::InvalidOperation(QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool EnumerationType::operator_less_equal(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		return mValue.toInt() <= other->getValue().toInt();
	}

	throw Exceptions::InvalidOperation(QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}


}
}
