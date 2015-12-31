
// Header
#include "IntegerObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "FloatObject.h"
#include "NumberObject.h"

// Namespace declarations


namespace ObjectiveScript {


std::string IntegerObject::TYPENAME = "int";


IntegerObject::IntegerObject(int value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, ""),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

IntegerObject::IntegerObject(const std::string& value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value),
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

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

void IntegerObject::operator_divide(IntegerObject *other)
{
	mValue /= other->getNativeValue();
}

void IntegerObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		operator_divide(&tmp);
	}
	else {
		Object::operator_divide(other);
	}
}

bool IntegerObject::operator_equal(IntegerObject *other)
{
	return (mValue == other->getNativeValue());
}

bool IntegerObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool IntegerObject::operator_greater(IntegerObject *other)
{
	return (mValue > other->getNativeValue());
}

bool IntegerObject::operator_greater(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		return operator_greater(&tmp);
	}

	return Object::operator_greater(other);
}

bool IntegerObject::operator_greater_equal(IntegerObject *other)
{
	return (mValue >= other->getNativeValue());
}

bool IntegerObject::operator_greater_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		return operator_greater_equal(&tmp);
	}

	return Object::operator_greater_equal(other);
}

bool IntegerObject::operator_less(IntegerObject *other)
{
	return (mValue < other->getNativeValue());
}

bool IntegerObject::operator_less(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		return operator_less(&tmp);
	}

	return Object::operator_less(other);
}

bool IntegerObject::operator_less_equal(IntegerObject *other)
{
	return (mValue <= other->getNativeValue());
}

bool IntegerObject::operator_less_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		return operator_less_equal(&tmp);
	}

	return Object::operator_less_equal(other);
}

void IntegerObject::operator_modulo(IntegerObject *other)
{
	mValue %= other->getNativeValue();
}

void IntegerObject::operator_modulo(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		operator_modulo(&tmp);
	}
	else {
		Object::operator_modulo(other);
	}
}

void IntegerObject::operator_multiply(IntegerObject *other)
{
	mValue *= other->getNativeValue();
}

void IntegerObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		operator_multiply(&tmp);
	}
	else {
		Object::operator_multiply(other);
	}
}

void IntegerObject::operator_plus(IntegerObject *other)
{
	mValue += other->getNativeValue();
}

void IntegerObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		operator_plus(&tmp);
	}
	else {
		Object::operator_plus(other);
	}
}

void IntegerObject::operator_subtract(IntegerObject *other)
{
	mValue -= other->getNativeValue();
}

void IntegerObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(other->getValue());

		operator_subtract(&tmp);
	}
	else {
		Object::operator_subtract(other);
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
