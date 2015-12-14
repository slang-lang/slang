
// Header
#include "StringObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "BoolObject.h"
#include "NumberObject.h"
#include "UserObject.h"
#include "VoidObject.h"

// Namespace declarations


namespace ObjectiveScript {


std::string String::TYPENAME = "String";


String::String(const std::string& value)
: Object("", SYSTEM_LIBRARY, TYPENAME, value),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

String::String(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, object.getValue()),
  mValue(object.getValue())
{
}

String::operator bool() const
{
	return !getValue().empty();
}

std::string String::getNativeValue() const
{
	return mValue;
}

std::string String::getValue() const
{
	return mValue;
}

void String::operator_assign(BoolObject *other)
{
	mValue = other->getValue();
}

void String::operator_assign(Number *other)
{
	mValue = other->getValue();
}

void String::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ) {
		String tmp(other->getValue());

		operator_assign(&tmp);
	}
	else if ( target == Number::TYPENAME ) {
		String tmp(other->getValue());

		operator_assign(&tmp);
	}
	else if ( target == String::TYPENAME ) {
		String tmp(other->getValue());

		operator_assign(&tmp);
	}
	else {
		throw Utils::NotImplemented("operator_assign: conversion from " + target + " to " + Typename() + " not supported");
	}
}

void String::operator_assign(String *other)
{
	mValue = other->getNativeValue();
}

bool String::operator_equal(Object *other)
{
	std::string target = other->Typename();

/*
	if ( target == Bool::TYPENAME ) {
		String tmp(other->getValue());

		return operator_equal(&tmp);
	}
	else if ( target == Number::TYPENAME ) {
		String tmp(other->getValue());

		return operator_equal(&tmp);
	}
	else
*/
	if ( target == String::TYPENAME ) {
		String tmp(other->getValue());

		return operator_equal(&tmp);
	}

	throw Utils::NotImplemented("operator_equal: conversion from " + target + " to " + Typename() + " not supported");
}

bool String::operator_equal(String *other)
{
	return (mValue == other->getNativeValue());
}

void String::operator_plus(BoolObject *other)
{
	mValue += other->getValue();
}

void String::operator_plus(Number *other)
{
	mValue += other->getValue();
}

void String::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ) {
		String tmp(other->getValue());

		operator_plus(&tmp);
	}
	else if ( target == Number::TYPENAME ) {
		String tmp(other->getValue());

		operator_plus(&tmp);
	}
	else if ( target == String::TYPENAME ) {
		String tmp(other->getValue());

		operator_plus(&tmp);
	}
	else {
		throw Utils::NotImplemented("operator_assign: conversion from " + target + " to " + Typename() + " not supported");
	}
}

void String::operator_plus(String *other)
{
	mValue += other->getNativeValue();
}

void String::setNativeValue(const std::string& value)
{
	mValue = value;
}

void String::setValue(const std::string& value)
{
	mValue = value;
}

std::string String::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
