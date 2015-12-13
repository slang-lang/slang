
// Header
#include "NumberObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


Number::Number(float value)
: Object("", "SYSTEM.OS", "Number", ""),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

Number::Number(const std::string& value)
: Object("", "SYSTEM.OS", "Number", value),
  mValue(Tools::stringToFloat(value))
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

Number::Number(const Object& object)
: Object(object.getName(), "SYSTEM.OS", "Number", object.getValue()),
  mValue(0.f)
{
}

Number::operator bool() const
{
	return mValue != 0.f;
}

float Number::getNativeValue() const
{
	return mValue;
}

std::string Number::getValue() const
{
	return Tools::floatToString(mValue);
}

bool Number::isValid() const
{
	return true;
}

void Number::operator_assign(Number *other)
{
	mValue = other->getNativeValue();
}

void Number::operator_assign(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Number" ) {
		Number tmp(other->getValue());

		operator_assign(&tmp);
	}
	else {
		throw Utils::NotImplemented("operator_assign: conversion from " + target + " to Number not supported");
	}
}

void Number::operator_divide(Number *other)
{
	mValue /= other->getNativeValue();
}

void Number::operator_divide(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Number" ) {
		Number tmp(other->getValue());

		operator_divide(&tmp);
	}
	else {
		throw Utils::NotImplemented("operator_divide: conversion from " + target + " to Number not supported");
	}
}

bool Number::operator_equal(Number *other)
{
	return (mValue == other->getNativeValue());
}

bool Number::operator_equal(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Number" ) {
		Number tmp(other->getValue());

		return operator_equal(&tmp);
	}

	throw Utils::NotImplemented("operator_equal: conversion from " + target + " to Number not supported");
}

bool Number::operator_greater(Number *other)
{
	return (mValue > other->getNativeValue());
}

bool Number::operator_greater(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Number" ) {
		Number tmp(other->getValue());

		return operator_greater(&tmp);
	}

	throw Utils::NotImplemented("operator_greater: conversion from " + target + " to Number not supported");
}

bool Number::operator_greater_equal(Number *other)
{
	return (mValue >= other->getNativeValue());
}

bool Number::operator_greater_equal(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Number" ) {
		Number tmp(other->getValue());

		return operator_greater_equal(&tmp);
	}

	throw Utils::NotImplemented("operator_greater_equal: conversion from " + target + " to Number not supported");
}

bool Number::operator_less(Number *other)
{
	return (mValue < other->getNativeValue());
}

bool Number::operator_less(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Number" ) {
		Number tmp(other->getValue());

		return operator_less(&tmp);
	}

	throw Utils::NotImplemented("operator_less: conversion from " + target + " to Number not supported");
}

bool Number::operator_less_equal(Number *other)
{
	return (mValue <= other->getNativeValue());
}

bool Number::operator_less_equal(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Number" ) {
		Number tmp(other->getValue());

		return operator_less_equal(&tmp);
	}

	throw Utils::NotImplemented("operator_less_equal: conversion from " + target + " to Number not supported");
}

void Number::operator_multiply(Number *other)
{
	mValue *= other->getNativeValue();
}

void Number::operator_multiply(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Number" ) {
		Number tmp(other->getValue());

		operator_multiply(&tmp);
	}
	else {
		throw Utils::NotImplemented("operator_multiply: conversion from " + target + " to Number not supported");
	}
}

void Number::operator_plus(Number *other)
{
	mValue += other->getNativeValue();
}

void Number::operator_plus(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Number" ) {
		Number tmp(other->getValue());

		operator_plus(&tmp);
	}
	else {
		throw Utils::NotImplemented("operator_plus: conversion from " + target + " to Number not supported");
	}
}

void Number::operator_subtract(Number *other)
{
	mValue -= other->getNativeValue();
}

void Number::operator_subtract(Object *other)
{
	std::string target = other->Typename();
	if ( target == "Number" ) {
		Number tmp(other->getValue());

		operator_subtract(&tmp);
	}
	else {
		throw Utils::NotImplemented("operator_subtract: conversion from " + target + " to Number not supported");
	}
}

void Number::setNativeValue(float value)
{
	mValue = value;
}

void Number::setValue(const std::string& value)
{
	mValue = Tools::stringToFloat(value);
}

std::string Number::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
