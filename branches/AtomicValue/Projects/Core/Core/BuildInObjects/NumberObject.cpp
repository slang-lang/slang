
// Header
#include "NumberObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


double NumberObject::DEFAULTVALUE = 0.0;
std::string NumberObject::TYPENAME = "number";


NumberObject::NumberObject(double value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

NumberObject::NumberObject(const std::string& name, double value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

NumberObject::NumberObject(const Object& other)
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

double NumberObject::getNativeValue() const
{
	return mNativeValue;
}

const std::string& NumberObject::getTypeName() const
{
	return TYPENAME;
}

std::string NumberObject::getValue() const
{
	//return mValue;
	return Tools::toString(mNativeValue);
}

bool NumberObject::isValid() const
{
	return mIsConstructed;
}

void NumberObject::operator_assign(NumberObject *other)
{
	setNativeValue(other->getNativeValue());
}

void NumberObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ) {
		setNativeValue(other->isValid());
	}
	else if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToNumber(other->getValue()));

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

bool NumberObject::operator_bool() const
{
	return mNativeValue != 0.0;
}

void NumberObject::operator_divide(NumberObject *other)
{
	setNativeValue(mNativeValue / other->getNativeValue());
}

void NumberObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToNumber(other->getValue()));

		operator_divide(&tmp);
	}
	else {
		Object::operator_divide(other);
	}
}

bool NumberObject::operator_equal(NumberObject *other) const
{
	return (mNativeValue == other->getNativeValue());
}

bool NumberObject::operator_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToNumber(other->getValue()));

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool NumberObject::operator_greater(NumberObject *other) const
{
	return (mNativeValue > other->getNativeValue());
}

bool NumberObject::operator_greater(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToNumber(other->getValue()));

		return operator_greater(&tmp);
	}

	return Object::operator_greater(other);
}

bool NumberObject::operator_greater_equal(NumberObject *other) const
{
	return (mNativeValue >= other->getNativeValue());
}

bool NumberObject::operator_greater_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToNumber(other->getValue()));

		return operator_greater_equal(&tmp);
	}

	return Object::operator_greater_equal(other);
}

bool NumberObject::operator_less(NumberObject *other) const
{
	return (mNativeValue < other->getNativeValue());
}

bool NumberObject::operator_less(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToNumber(other->getValue()));

		return operator_less(&tmp);
	}

	return Object::operator_less(other);
}

bool NumberObject::operator_less_equal(NumberObject *other) const
{
	return (mNativeValue <= other->getNativeValue());
}

bool NumberObject::operator_less_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToNumber(other->getValue()));

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

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToNumber(other->getValue()));

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

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToNumber(other->getValue()));

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

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToNumber(other->getValue()));

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

void NumberObject::setNativeValue(double value)
{
	mNativeValue = value;
	//mValue = Tools::toString(value);
}

void NumberObject::setValue(const std::string& value)
{
	mNativeValue = Tools::stringToNumber(value);
	//mValue = Tools::toString(mNativeValue);		// this conversion is necessary because these two values could drift apart because std::string can also hold floating point values
}

std::string NumberObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
}
