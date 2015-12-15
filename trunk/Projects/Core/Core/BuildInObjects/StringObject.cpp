
// Header
#include "StringObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "BoolObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "NumberObject.h"
#include "UserObject.h"
#include "VoidObject.h"

// Namespace declarations


namespace ObjectiveScript {


std::string StringObject::TYPENAME = "string";


StringObject::StringObject(const std::string& value)
: Object("", SYSTEM_LIBRARY, TYPENAME, value),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

StringObject::StringObject(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, object.getValue()),
  mValue(object.getValue())
{
}

StringObject::operator bool() const
{
	return !getValue().empty();
}

std::string StringObject::getNativeValue() const
{
	return mValue;
}

std::string StringObject::getValue() const
{
	return mValue;
}

void StringObject::operator_assign(BoolObject *other)
{
	mValue = other->getValue();
}

void StringObject::operator_assign(FloatObject *other)
{
	mValue = other->getValue();
}

void StringObject::operator_assign(NumberObject *other)
{
	mValue = other->getValue();
}

void StringObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		StringObject tmp(other->getValue());

		operator_assign(&tmp);
	}
	else {
		throw Utils::Exceptions::NotImplemented("operator=: conversion from " + target + " to " + Typename() + " not supported");
	}
}

void StringObject::operator_assign(StringObject *other)
{
	mValue = other->getNativeValue();
}

bool StringObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

/*
	if ( target == Bool::TYPENAME ) {
		StringObject tmp(other->getValue());

		return operator_equal(&tmp);
	}
	else if ( target == NumberObject::TYPENAME ) {
		StringObject tmp(other->getValue());

		return operator_equal(&tmp);
	}
	else
*/
	if ( target == StringObject::TYPENAME ) {
		StringObject tmp(other->getValue());

		return operator_equal(&tmp);
	}

	throw Utils::Exceptions::NotImplemented("operator==: conversion from " + target + " to " + Typename() + " not supported");
}

bool StringObject::operator_equal(StringObject *other)
{
	return (mValue == other->getNativeValue());
}

void StringObject::operator_plus(BoolObject *other)
{
	mValue += other->getValue();
}

void StringObject::operator_plus(FloatObject *other)
{
	mValue += other->getValue();
}

void StringObject::operator_plus(NumberObject *other)
{
	mValue += other->getValue();
}

void StringObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		StringObject tmp(other->getValue());

		operator_plus(&tmp);
	}
	else {
		throw Utils::Exceptions::NotImplemented("operator+: conversion from " + target + " to " + Typename() + " not supported");
	}
}

void StringObject::operator_plus(StringObject *other)
{
	mValue += other->getNativeValue();
}

void StringObject::setNativeValue(const std::string& value)
{
	mValue = value;
}

void StringObject::setValue(const std::string& value)
{
	mValue = value;
}

std::string StringObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
