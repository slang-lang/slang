
// Header
#include "NumberObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "FloatObject.h"
#include "IntegerObject.h"

// Namespace declarations


namespace ObjectiveScript {


std::string NumberObject::TYPENAME = "number";


NumberObject::NumberObject(float value)
: Object(UNNAMED_OBJECT, SYSTEM_LIBRARY, TYPENAME, Tools::floatToString(value)),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

NumberObject::NumberObject(const std::string& value)
: Object(UNNAMED_OBJECT, SYSTEM_LIBRARY, TYPENAME, value),
  mValue(Tools::stringToFloat(value))
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

NumberObject::NumberObject(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, object.getValue()),
  mValue(0.f)
{
}

NumberObject::operator bool() const
{
	return mValue != 0.f;
}

float NumberObject::getNativeValue() const
{
	return mValue;
}

std::string NumberObject::getValue() const
{
	return Tools::floatToString(mValue);
}

bool NumberObject::isValid() const
{
	return true;
}

void NumberObject::operator_assign(NumberObject *other)
{
	mValue = other->getNativeValue();
}

void NumberObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(other->getValue());

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

void NumberObject::operator_divide(NumberObject *other)
{
	mValue /= other->getNativeValue();
}

void NumberObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(other->getValue());

		operator_divide(&tmp);
	}
	else {
		Object::operator_divide(other);
	}
}

bool NumberObject::operator_equal(NumberObject *other)
{
	return (mValue == other->getNativeValue());
}

bool NumberObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(other->getValue());

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool NumberObject::operator_greater(NumberObject *other)
{
	return (mValue > other->getNativeValue());
}

bool NumberObject::operator_greater(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(other->getValue());

		return operator_greater(&tmp);
	}

	return Object::operator_greater(other);
}

bool NumberObject::operator_greater_equal(NumberObject *other)
{
	return (mValue >= other->getNativeValue());
}

bool NumberObject::operator_greater_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(other->getValue());

		return operator_greater_equal(&tmp);
	}

	return Object::operator_greater_equal(other);
}

bool NumberObject::operator_less(NumberObject *other)
{
	return (mValue < other->getNativeValue());
}

bool NumberObject::operator_less(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(other->getValue());

		return operator_less(&tmp);
	}

	return Object::operator_less(other);
}

bool NumberObject::operator_less_equal(NumberObject *other)
{
	return (mValue <= other->getNativeValue());
}

bool NumberObject::operator_less_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(other->getValue());

		return operator_less_equal(&tmp);
	}

	return Object::operator_less_equal(other);
}

void NumberObject::operator_multiply(NumberObject *other)
{
	mValue *= other->getNativeValue();
}

void NumberObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(other->getValue());

		operator_multiply(&tmp);
	}
	else {
		Object::operator_multiply(other);
	}
}

void NumberObject::operator_plus(NumberObject *other)
{
	mValue += other->getNativeValue();
}

void NumberObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(other->getValue());

		operator_plus(&tmp);
	}
	else {
		Object::operator_plus(other);
	}
}

void NumberObject::operator_subtract(NumberObject *other)
{
	mValue -= other->getNativeValue();
}

void NumberObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(other->getValue());

		operator_subtract(&tmp);
	}
	else {
		Object::operator_subtract(other);
	}
}

void NumberObject::setNativeValue(float value)
{
	mValue = value;
}

void NumberObject::setValue(const std::string& value)
{
	mValue = Tools::stringToFloat(value);
}

std::string NumberObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
