
// Header
#include "IntegerObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


//std::string IntegerObject::TYPENAME = "int";
std::string IntegerObject::TYPENAME = "number";


IntegerObject::IntegerObject(int value)
: Object("", SYSTEM_LIBRARY, TYPENAME, ""),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

IntegerObject::IntegerObject(const std::string& value)
: Object("", SYSTEM_LIBRARY, TYPENAME, value),
  mValue(Tools::stringToInt(value))
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

IntegerObject::IntegerObject(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, object.getValue()),
  mValue(0)
{
}

IntegerObject::operator bool() const
{
	return mValue != 0.f;
}

int IntegerObject::getNativeValue() const
{
	return mValue;
}

std::string IntegerObject::getValue() const
{
	return Tools::intToString(mValue);
}

bool IntegerObject::isValid() const
{
	return true;
}

void IntegerObject::operator_assign(IntegerObject *other)
{
	mValue = other->getNativeValue();
}

void IntegerObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		operator_assign(&tmp);
	}
	else {
		throw Utils::Exceptions::NotImplemented("operator_assign: conversion from " + target + " to " + Typename() + " not supported");
	}
}

void IntegerObject::operator_divide(IntegerObject *other)
{
	mValue /= other->getNativeValue();
}

void IntegerObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		operator_divide(&tmp);
	}
	else {
		throw Utils::Exceptions::NotImplemented("operator_divide: conversion from " + target + " to " + Typename() + " not supported");
	}
}

bool IntegerObject::operator_equal(IntegerObject *other)
{
	return (mValue == other->getNativeValue());
}

bool IntegerObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		return operator_equal(&tmp);
	}

	throw Utils::Exceptions::NotImplemented("operator_equal: conversion from " + target + " to " + Typename() + " not supported");
}

bool IntegerObject::operator_greater(IntegerObject *other)
{
	return (mValue > other->getNativeValue());
}

bool IntegerObject::operator_greater(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		return operator_greater(&tmp);
	}

	throw Utils::Exceptions::NotImplemented("operator_greater: conversion from " + target + " to " + Typename() + " not supported");
}

bool IntegerObject::operator_greater_equal(IntegerObject *other)
{
	return (mValue >= other->getNativeValue());
}

bool IntegerObject::operator_greater_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		return operator_greater_equal(&tmp);
	}

	throw Utils::Exceptions::NotImplemented("operator_greater_equal: conversion from " + target + " to " + Typename() + " not supported");
}

bool IntegerObject::operator_less(IntegerObject *other)
{
	return (mValue < other->getNativeValue());
}

bool IntegerObject::operator_less(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		return operator_less(&tmp);
	}

	throw Utils::Exceptions::NotImplemented("operator_less: conversion from " + target + " to " + Typename() + " not supported");
}

bool IntegerObject::operator_less_equal(IntegerObject *other)
{
	return (mValue <= other->getNativeValue());
}

bool IntegerObject::operator_less_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		return operator_less_equal(&tmp);
	}

	throw Utils::Exceptions::NotImplemented("operator_less_equal: conversion from " + target + " to " + Typename() + " not supported");
}

void IntegerObject::operator_multiply(IntegerObject *other)
{
	mValue *= other->getNativeValue();
}

void IntegerObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		operator_multiply(&tmp);
	}
	else {
		throw Utils::Exceptions::NotImplemented("operator_multiply: conversion from " + target + " to " + Typename() + " not supported");
	}
}

void IntegerObject::operator_plus(IntegerObject *other)
{
	mValue += other->getNativeValue();
}

void IntegerObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		operator_plus(&tmp);
	}
	else {
		throw Utils::Exceptions::NotImplemented("operator_plus: conversion from " + target + " to " + Typename() + " not supported");
	}
}

void IntegerObject::operator_subtract(IntegerObject *other)
{
	mValue -= other->getNativeValue();
}

void IntegerObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		operator_subtract(&tmp);
	}
	else {
		throw Utils::Exceptions::NotImplemented("operator_subtract: conversion from " + target + " to " + Typename() + " not supported");
	}
}

void IntegerObject::setNativeValue(int value)
{
	mValue = value;
}

void IntegerObject::setValue(const std::string& value)
{
	mValue = Tools::stringToInt(value);
}

std::string IntegerObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
