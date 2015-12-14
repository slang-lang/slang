
// Header
#include "BoolObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "NumberObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {


std::string BoolObject::TYPENAME = "bool";


BoolObject::BoolObject(bool value)
: Object("", SYSTEM_LIBRARY, TYPENAME, ""),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

BoolObject::BoolObject(const std::string& value)
: Object("", SYSTEM_LIBRARY, TYPENAME, value),
  mValue(Tools::stringToBool(value))
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

BoolObject::BoolObject(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, object.getValue()),
  mValue(Tools::stringToBool(object.getValue()))
{
}

BoolObject::operator bool() const
{
	return mValue;
}

bool BoolObject::getNativeValue() const
{
	return mValue;
}

std::string BoolObject::getValue() const
{
	return Tools::boolToString(mValue);
}

bool BoolObject::isValid() const
{
	return true;
}

void BoolObject::operator_assign(BoolObject *other)
{
	mValue = other->getNativeValue();
}

void BoolObject::operator_assign(NumberObject *other)
{
	mValue = (other->getNativeValue() != 0.f);
}

void BoolObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp(other->getValue());

		operator_assign(&tmp);
	}
	else if ( target == NumberObject::TYPENAME ) {
		BoolObject tmp(other->getValue());

		operator_assign(&tmp);
	}
	else if ( target == StringObject::TYPENAME ) {
		BoolObject tmp(other->getValue());

		operator_assign(&tmp);
	}
	else {
		throw Utils::Exceptions::NotImplemented("operator_assign: conversion from " + target + " to " + Typename() + " not supported");
	}
}

void BoolObject::operator_assign(StringObject *other)
{
	mValue = !other->getNativeValue().empty();
}

bool BoolObject::operator_equal(BoolObject *other)
{
	return (mValue == other->getNativeValue());
}

bool BoolObject::operator_equal(NumberObject *other)
{
	return (mValue == (other->getNativeValue() != 0.f));
}

bool BoolObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp(other->getValue());

		return operator_equal(&tmp);
	}
	else if ( target == NumberObject::TYPENAME ) {
		BoolObject tmp(other->getValue());

		return operator_equal(&tmp);
	}
	else if ( target == StringObject::TYPENAME ) {
		BoolObject tmp(other->getValue());

		return operator_equal(&tmp);
	}

	throw Utils::Exceptions::NotImplemented("operator_equal: conversion from " + target + " to " + Typename() + " not supported");
}

bool BoolObject::operator_equal(StringObject *other)
{
	return (mValue == (!other->getNativeValue().empty()));
}

void BoolObject::setNativeValue(bool value)
{
	mValue = value;
}

void BoolObject::setValue(const std::string& value)
{
	mValue = Tools::stringToBool(value);
}

std::string BoolObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
