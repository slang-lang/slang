
// Header
#include "BoolObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


Bool::Bool(bool value)
: Object("", "SYSTEM.OS", "Bool", ""),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

Bool::Bool(const std::string& value)
: Object("", "SYSTEM.OS", "Bool", value),
  mValue(Tools::stringToBool(value))
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

Bool::Bool(const Object& object)
: Object(object.getName(), "SYSTEM.OS", "Bool", object.getValue()),
  mValue(Tools::stringToBool(object.getValue()))
{
}

Bool::operator bool() const
{
	return mValue;
}

bool Bool::getNativeValue() const
{
	return mValue;
}

std::string Bool::getValue() const
{
	return Tools::boolToString(mValue);
}

bool Bool::isValid() const
{
	return true;
}

void Bool::operator_assign(Bool *other)
{
	mValue = other->getNativeValue();
}

void Bool::operator_assign(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Bool" ) {
		Bool tmp(other->getValue());

		operator_assign(&tmp);
	}
	else {
		throw Utils::NotImplemented("operator_assign: conversion from " + target + " to Number not supported");
	}
}

bool Bool::operator_equal(Bool *other)
{
	return (mValue == other->getNativeValue());
}

bool Bool::operator_equal(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Bool" ) {
		Bool tmp(other->getValue());

		return operator_equal(&tmp);
	}

	throw Utils::NotImplemented("operator_equal: conversion from " + target + " to Number not supported");
}

void Bool::setNativeValue(bool value)
{
	mValue = value;
}

void Bool::setValue(const std::string& value)
{
	mValue = Tools::stringToBool(value);
}

std::string Bool::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
