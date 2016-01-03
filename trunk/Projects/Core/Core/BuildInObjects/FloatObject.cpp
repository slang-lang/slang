
// Header
#include "FloatObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


std::string FloatObject::TYPENAME = "float";


FloatObject::FloatObject(float value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, ""),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

FloatObject::FloatObject(const std::string& name, float value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, Tools::floatToString(value)),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

FloatObject::FloatObject(const std::string& name, const std::string& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value),
  mValue(Tools::stringToFloat(value))
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

FloatObject::FloatObject(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, object.getValue()),
  mValue(0.f)
{
}

FloatObject::operator bool() const
{
	return mValue != 0.f;
}

float FloatObject::getNativeValue() const
{
	return mValue;
}

const std::string& FloatObject::getTypeName() const
{
	return TYPENAME;
}

std::string FloatObject::getValue() const
{
	return Tools::floatToString(mValue);
}

bool FloatObject::isValid() const
{
	return true;
}

void FloatObject::operator_assign(FloatObject *other)
{
	mValue = other->getNativeValue();
}

void FloatObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

void FloatObject::operator_divide(FloatObject *other)
{
	mValue /= other->getNativeValue();
}

void FloatObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		operator_divide(&tmp);
	}
	else {
		Object::operator_divide(other);
	}
}

bool FloatObject::operator_equal(FloatObject *other)
{
	return (mValue == other->getNativeValue());
}

bool FloatObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool FloatObject::operator_greater(FloatObject *other)
{
	return (mValue > other->getNativeValue());
}

bool FloatObject::operator_greater(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_greater(&tmp);
	}

	return Object::operator_greater(other);
}

bool FloatObject::operator_greater_equal(FloatObject *other)
{
	return (mValue >= other->getNativeValue());
}

bool FloatObject::operator_greater_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_greater_equal(&tmp);
	}

	return Object::operator_greater_equal(other);
}

bool FloatObject::operator_less(FloatObject *other)
{
	return (mValue < other->getNativeValue());
}

bool FloatObject::operator_less(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_less(&tmp);
	}

	return Object::operator_less(other);
}

bool FloatObject::operator_less_equal(FloatObject *other)
{
	return (mValue <= other->getNativeValue());
}

bool FloatObject::operator_less_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_less_equal(&tmp);
	}

	return Object::operator_less_equal(other);
}

void FloatObject::operator_multiply(FloatObject *other)
{
	mValue *= other->getNativeValue();
}

void FloatObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		operator_multiply(&tmp);
	}
	else {
		Object::operator_multiply(other);
	}
}

void FloatObject::operator_plus(FloatObject *other)
{
	mValue += other->getNativeValue();
}

void FloatObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		operator_plus(&tmp);
	}
	else {
		Object::operator_plus(other);
	}
}

void FloatObject::operator_subtract(FloatObject *other)
{
	mValue -= other->getNativeValue();
}

void FloatObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		operator_subtract(&tmp);
	}
	else {
		Object::operator_subtract(other);
	}
}

void FloatObject::setNativeValue(float value)
{
	mValue = value;
}

void FloatObject::setValue(const std::string& value)
{
	mValue = Tools::stringToFloat(value);
}

std::string FloatObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
