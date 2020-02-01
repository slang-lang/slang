
// Header
#include "EnumerationObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


AtomicValue EnumerationObject::DEFAULTVALUE = AtomicValue(0);
std::string EnumerationObject::TYPENAME = _enum;


EnumerationObject::EnumerationObject(const std::string& name, const std::string& type, const AtomicValue& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mBluePrintType = BlueprintType::Enum;
	mIsAtomicType = true;
	mQualifiedOuterface = type;
	mQualifiedTypename = type;
}

const std::string& EnumerationObject::getTypeName() const
{
	return TYPENAME;
}

bool EnumerationObject::isValid() const
{
	return true;
}

void EnumerationObject::operator_assign(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		mValue = other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool EnumerationObject::operator_bool() const
{
	return mValue.toInt() != 0;
}

bool EnumerationObject::operator_equal(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		return mValue.toInt() == other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool EnumerationObject::operator_greater(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		return mValue.toInt() > other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool EnumerationObject::operator_greater_equal(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		return mValue.toInt() >= other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool EnumerationObject::operator_less(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		return mValue.toInt() < other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool EnumerationObject::operator_less_equal(const Object *other)
{
	if ( other->isEnumerationValue() && QualifiedTypename() == other->QualifiedTypename() ) {
		return mValue.toInt() <= other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}


}
}
