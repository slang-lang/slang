
// Header
#include "FloatObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "IntegerObject.h"
#include "NumberObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


float FloatObject::DEFAULTVALUE = 0.f;
std::string FloatObject::TYPENAME = "float";


FloatObject::FloatObject(float value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

FloatObject::FloatObject(const std::string& name, float value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

FloatObject::FloatObject(const std::string& name, const std::string& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setValue(value);
}

FloatObject::FloatObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;

	std::string source = other.Typename();

	if ( source == FloatObject::TYPENAME ||
		 source == IntegerObject::TYPENAME ||
		 source == NumberObject::TYPENAME ||
		 source == StringObject::TYPENAME) {
		setValue(other.getValue());
	}
	else {
		throw Utils::Exceptions::InvalidTypeCast("from " + source + " to " + TYPENAME);
	}
}

FloatObject::operator bool() const
{
	return mNativeValue != 0.f;
}

float FloatObject::getNativeValue() const
{
	return mNativeValue;
}

const std::string& FloatObject::getTypeName() const
{
	return TYPENAME;
}

std::string FloatObject::getValue() const
{
	return mValue;
}

bool FloatObject::isValid() const
{
	return mNativeValue != 0.f;
}

void FloatObject::operator_assign(FloatObject *other)
{
	setNativeValue(other->getNativeValue());
}

void FloatObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

void FloatObject::operator_divide(FloatObject *other)
{
	setNativeValue(mNativeValue / other->getNativeValue());
}

void FloatObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		operator_divide(&tmp);
	}
	else {
		Object::operator_divide(other);
	}
}

bool FloatObject::operator_equal(FloatObject *other)
{
	return (mNativeValue == other->getNativeValue());
}

bool FloatObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool FloatObject::operator_greater(FloatObject *other)
{
	return (mNativeValue > other->getNativeValue());
}

bool FloatObject::operator_greater(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_greater(&tmp);
	}

	return Object::operator_greater(other);
}

bool FloatObject::operator_greater_equal(FloatObject *other)
{
	return (mNativeValue >= other->getNativeValue());
}

bool FloatObject::operator_greater_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_greater_equal(&tmp);
	}

	return Object::operator_greater_equal(other);
}

bool FloatObject::operator_less(FloatObject *other)
{
	return (mNativeValue < other->getNativeValue());
}

bool FloatObject::operator_less(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_less(&tmp);
	}

	return Object::operator_less(other);
}

bool FloatObject::operator_less_equal(FloatObject *other)
{
	return (mNativeValue <= other->getNativeValue());
}

bool FloatObject::operator_less_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		return operator_less_equal(&tmp);
	}

	return Object::operator_less_equal(other);
}

void FloatObject::operator_multiply(FloatObject *other)
{
	setNativeValue(mNativeValue * other->getNativeValue());
}

void FloatObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		operator_multiply(&tmp);
	}
	else {
		Object::operator_multiply(other);
	}
}

void FloatObject::operator_plus(FloatObject *other)
{
	setNativeValue(mNativeValue + other->getNativeValue());
}

void FloatObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		operator_plus(&tmp);
	}
	else {
		Object::operator_plus(other);
	}
}

void FloatObject::operator_subtract(FloatObject *other)
{
	setNativeValue(mNativeValue - other->getNativeValue());
}

void FloatObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		FloatObject tmp(Tools::stringToFloat(other->getValue()));

		operator_subtract(&tmp);
	}
	else {
		Object::operator_subtract(other);
	}
}

void FloatObject::operator_unary_decrement()
{
	setNativeValue(mNativeValue - 1);
}

void FloatObject::operator_unary_increment()
{
	setNativeValue(mNativeValue + 1);
}

void FloatObject::operator_unary_minus()
{
	setNativeValue(mNativeValue * -1);
}

void FloatObject::operator_unary_not()
{
	setNativeValue(!mNativeValue);
}

void FloatObject::setNativeValue(float value)
{
	mNativeValue = value;
	mValue = Tools::toString(value);
}

void FloatObject::setValue(const std::string& value)
{
	mNativeValue = Tools::stringToFloat(value);
	mValue = Tools::toString(mNativeValue);		// this conversion is necessary because these two values could drift apart because std::string can also hold floating point values
}

std::string FloatObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
}
