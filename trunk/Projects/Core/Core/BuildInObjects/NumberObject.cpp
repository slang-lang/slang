
// Header
#include "NumberObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "BoolObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


float NumberObject::DEFAULTVALUE = 0.f;
std::string NumberObject::TYPENAME = "number";


NumberObject::NumberObject(float value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

NumberObject::NumberObject(const std::string& name, float value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

NumberObject::NumberObject(const std::string& name, const std::string& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setValue(value);
}

NumberObject::NumberObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;

	std::string source = other.Typename();

	if ( source == FloatObject::TYPENAME ||
		 source == IntegerObject::TYPENAME ||
		 source == NumberObject::TYPENAME ||
		 source == StringObject::TYPENAME ) {
		setValue(other.getValue());
	}
	else {
		throw Utils::Exceptions::InvalidTypeCast("from " + source + " to " + TYPENAME);
	}
}

NumberObject::operator bool() const
{
	return mNativeValue != 0.0;
}

float NumberObject::getNativeValue() const
{
	return mNativeValue;
}

const std::string& NumberObject::getTypeName() const
{
	return TYPENAME;
}

std::string NumberObject::getValue() const
{
	return mValue;
}

bool NumberObject::isValid() const
{
	return mNativeValue != 0.0;
}

void NumberObject::operator_assign(NumberObject *other)
{
	setNativeValue(other->getNativeValue());
}

void NumberObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(other->getValue()));

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

void NumberObject::operator_divide(NumberObject *other)
{
	setNativeValue(mNativeValue / other->getNativeValue());
}

void NumberObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(other->getValue()));

		operator_divide(&tmp);
	}
	else {
		Object::operator_divide(other);
	}
}

bool NumberObject::operator_equal(NumberObject *other)
{
	return (mNativeValue == other->getNativeValue());
}

bool NumberObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool NumberObject::operator_greater(NumberObject *other)
{
	return (mNativeValue > other->getNativeValue());
}

bool NumberObject::operator_greater(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_greater(&tmp);
	}

	return Object::operator_greater(other);
}

bool NumberObject::operator_greater_equal(NumberObject *other)
{
	return (mNativeValue >= other->getNativeValue());
}

bool NumberObject::operator_greater_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_greater_equal(&tmp);
	}

	return Object::operator_greater_equal(other);
}

bool NumberObject::operator_less(NumberObject *other)
{
	return (mNativeValue < other->getNativeValue());
}

bool NumberObject::operator_less(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_less(&tmp);
	}

	return Object::operator_less(other);
}

bool NumberObject::operator_less_equal(NumberObject *other)
{
	return (mNativeValue <= other->getNativeValue());
}

bool NumberObject::operator_less_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_less_equal(&tmp);
	}

	return Object::operator_less_equal(other);
}

void NumberObject::operator_multiply(NumberObject *other)
{
	setNativeValue(mNativeValue * other->getNativeValue());
}

void NumberObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(other->getValue()));

		operator_multiply(&tmp);
	}
	else {
		Object::operator_multiply(other);
	}
}

void NumberObject::operator_plus(NumberObject *other)
{
	setNativeValue(mNativeValue + other->getNativeValue());
}

void NumberObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(other->getValue()));

		operator_plus(&tmp);
	}
	else {
		Object::operator_plus(other);
	}
}

void NumberObject::operator_subtract(NumberObject *other)
{
	setNativeValue(mNativeValue - other->getNativeValue());
}

void NumberObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(other->getValue()));

		operator_subtract(&tmp);
	}
	else {
		Object::operator_subtract(other);
	}
}

void NumberObject::operator_unary_decrement()
{
	setNativeValue(mNativeValue - 1);
}

void NumberObject::operator_unary_increment()
{
	setNativeValue(mNativeValue + 1);
}

void NumberObject::operator_unary_minus()
{
	setNativeValue(mNativeValue * -1);
}

void NumberObject::operator_unary_not()
{
	setNativeValue(!mNativeValue);
}

void NumberObject::setNativeValue(float value)
{
	mNativeValue = value;
	mValue = Tools::toString(value);
}

void NumberObject::setValue(const std::string& value)
{
	mNativeValue = Tools::stringToFloat(value);
	mValue = value;
}

std::string NumberObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
}
