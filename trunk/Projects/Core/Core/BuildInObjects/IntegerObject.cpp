
// Header
#include "IntegerObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "FloatObject.h"
#include "NumberObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


int IntegerObject::DEFAULTVALUE = 0;
std::string IntegerObject::TYPENAME = "int";


IntegerObject::IntegerObject(int value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

IntegerObject::IntegerObject(const std::string& name, int value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

IntegerObject::IntegerObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;

	std::string source = other.Typename();

	if ( source == BoolObject::TYPENAME ) {
		setNativeValue(other.isValid());
	}
	else if ( source == DoubleObject::TYPENAME ||
		 source == FloatObject::TYPENAME ||
		 source == IntegerObject::TYPENAME ||
		 source == NumberObject::TYPENAME ||
		 source == StringObject::TYPENAME ) {
		setValue(other.getValue());
	}
	else {
		throw Utils::Exceptions::InvalidTypeCast("from " + source + " to " + TYPENAME);
	}
}

IntegerObject::operator bool() const
{
	return mNativeValue != 0.f;
}

int IntegerObject::getNativeValue() const
{
	return mNativeValue;
}

const std::string& IntegerObject::getTypeName() const
{
	return TYPENAME;
}

std::string IntegerObject::getValue() const
{
	return mValue;
}

bool IntegerObject::isValid() const
{
	return mNativeValue != 0;
}

void IntegerObject::operator_assign(IntegerObject *other)
{
	setNativeValue(other->getNativeValue());
}

void IntegerObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

void IntegerObject::operator_divide(IntegerObject *other)
{
	setNativeValue(mNativeValue / other->getNativeValue());
}

void IntegerObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		operator_divide(&tmp);
	}
	else {
		Object::operator_divide(other);
	}
}

bool IntegerObject::operator_equal(IntegerObject *other)
{
	return (mNativeValue == other->getNativeValue());
}

bool IntegerObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool IntegerObject::operator_greater(IntegerObject *other)
{
	return (mNativeValue > other->getNativeValue());
}

bool IntegerObject::operator_greater(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		return operator_greater(&tmp);
	}

	return Object::operator_greater(other);
}

bool IntegerObject::operator_greater_equal(IntegerObject *other)
{
	return (mNativeValue >= other->getNativeValue());
}

bool IntegerObject::operator_greater_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		return operator_greater_equal(&tmp);
	}

	return Object::operator_greater_equal(other);
}

bool IntegerObject::operator_less(IntegerObject *other)
{
	return (mNativeValue < other->getNativeValue());
}

bool IntegerObject::operator_less(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		return operator_less(&tmp);
	}

	return Object::operator_less(other);
}

bool IntegerObject::operator_less_equal(IntegerObject *other)
{
	return (mNativeValue <= other->getNativeValue());
}

bool IntegerObject::operator_less_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		return operator_less_equal(&tmp);
	}

	return Object::operator_less_equal(other);
}

void IntegerObject::operator_modulo(IntegerObject *other)
{
	setNativeValue(mNativeValue % other->getNativeValue());
}

void IntegerObject::operator_modulo(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		operator_modulo(&tmp);
	}
	else {
		Object::operator_modulo(other);
	}
}

void IntegerObject::operator_multiply(IntegerObject *other)
{
	setNativeValue(mNativeValue * other->getNativeValue());
}

void IntegerObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		operator_multiply(&tmp);
	}
	else {
		Object::operator_multiply(other);
	}
}

void IntegerObject::operator_plus(IntegerObject *other)
{
	setNativeValue(mNativeValue + other->getNativeValue());
}

void IntegerObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		operator_plus(&tmp);
	}
	else {
		Object::operator_plus(other);
	}
}

void IntegerObject::operator_subtract(IntegerObject *other)
{
	setNativeValue(mNativeValue - other->getNativeValue());
}

void IntegerObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME) {
		IntegerObject tmp(Tools::stringToInt(other->getValue()));

		operator_subtract(&tmp);
	}
	else {
		Object::operator_subtract(other);
	}
}

void IntegerObject::operator_unary_decrement()
{
	setNativeValue(mNativeValue - 1);
}

void IntegerObject::operator_unary_increment()
{
	setNativeValue(mNativeValue + 1);
}

void IntegerObject::operator_unary_minus()
{
	setNativeValue(mNativeValue * -1);
}

void IntegerObject::operator_unary_not()
{
	setNativeValue(!mNativeValue);
}

void IntegerObject::setNativeValue(int value)
{
	mNativeValue = value;
	mValue = Tools::toString(value);
}

void IntegerObject::setValue(const std::string& value)
{
	mNativeValue = Tools::stringToInt(value);
	mValue = Tools::toString(mNativeValue);		// this conversion is necessary because these two values could drift apart because std::string can also hold floating point values
}

std::string IntegerObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
}
