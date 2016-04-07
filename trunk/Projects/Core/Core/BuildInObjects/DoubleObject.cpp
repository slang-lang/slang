
// Header
#include "DoubleObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "BoolObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "NumberObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


double DoubleObject::DEFAULTVALUE = 0.0;
std::string DoubleObject::TYPENAME = "double";


DoubleObject::DoubleObject(double value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

DoubleObject::DoubleObject(const std::string& name, double value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

DoubleObject::DoubleObject(const Object& other)
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

DoubleObject::operator bool() const
{
	return mNativeValue != 0.0;
}

double DoubleObject::getNativeValue() const
{
	return mNativeValue;
}

const std::string& DoubleObject::getTypeName() const
{
	return TYPENAME;
}

std::string DoubleObject::getValue() const
{
	return mValue;
}

bool DoubleObject::isValid() const
{
	return mNativeValue != 0.0;
}

void DoubleObject::operator_assign(DoubleObject *other)
{
	setNativeValue(other->getNativeValue());
}

void DoubleObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		DoubleObject tmp(Tools::stringToDouble(other->getValue()));

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

void DoubleObject::operator_divide(DoubleObject *other)
{
	setNativeValue(mNativeValue / other->getNativeValue());
}

void DoubleObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		DoubleObject tmp(Tools::stringToDouble(other->getValue()));

		operator_divide(&tmp);
	}
	else {
		Object::operator_divide(other);
	}
}

bool DoubleObject::operator_equal(DoubleObject *other)
{
	return (mNativeValue == other->getNativeValue());
}

bool DoubleObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		DoubleObject tmp(Tools::stringToDouble(other->getValue()));

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool DoubleObject::operator_greater(DoubleObject *other)
{
	return (mNativeValue > other->getNativeValue());
}

bool DoubleObject::operator_greater(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		DoubleObject tmp(Tools::stringToDouble(other->getValue()));

		return operator_greater(&tmp);
	}

	return Object::operator_greater(other);
}

bool DoubleObject::operator_greater_equal(DoubleObject *other)
{
	return (mNativeValue >= other->getNativeValue());
}

bool DoubleObject::operator_greater_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		DoubleObject tmp(Tools::stringToDouble(other->getValue()));

		return operator_greater_equal(&tmp);
	}

	return Object::operator_greater_equal(other);
}

bool DoubleObject::operator_less(DoubleObject *other)
{
	return (mNativeValue < other->getNativeValue());
}

bool DoubleObject::operator_less(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		DoubleObject tmp(Tools::stringToDouble(other->getValue()));

		return operator_less(&tmp);
	}

	return Object::operator_less(other);
}

bool DoubleObject::operator_less_equal(DoubleObject *other)
{
	return (mNativeValue <= other->getNativeValue());
}

bool DoubleObject::operator_less_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		DoubleObject tmp(Tools::stringToDouble(other->getValue()));

		return operator_less_equal(&tmp);
	}

	return Object::operator_less_equal(other);
}

void DoubleObject::operator_multiply(DoubleObject *other)
{
	setNativeValue(mNativeValue * other->getNativeValue());
}

void DoubleObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		DoubleObject tmp(Tools::stringToDouble(other->getValue()));

		operator_multiply(&tmp);
	}
	else {
		Object::operator_multiply(other);
	}
}

void DoubleObject::operator_plus(DoubleObject *other)
{
	setNativeValue(mNativeValue + other->getNativeValue());
}

void DoubleObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		DoubleObject tmp(Tools::stringToDouble(other->getValue()));

		operator_plus(&tmp);
	}
	else {
		Object::operator_plus(other);
	}
}

void DoubleObject::operator_subtract(DoubleObject *other)
{
	setNativeValue(mNativeValue - other->getNativeValue());
}

void DoubleObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		DoubleObject tmp(Tools::stringToDouble(other->getValue()));

		operator_subtract(&tmp);
	}
	else {
		Object::operator_subtract(other);
	}
}

void DoubleObject::operator_unary_decrement()
{
	setNativeValue(mNativeValue - 1);
}

void DoubleObject::operator_unary_increment()
{
	setNativeValue(mNativeValue + 1);
}

void DoubleObject::operator_unary_minus()
{
	setNativeValue(mNativeValue * -1);
}

void DoubleObject::operator_unary_not()
{
	setNativeValue(!mNativeValue);
}

void DoubleObject::setNativeValue(double value)
{
	mNativeValue = value;
	mValue = Tools::toString(value);
}

void DoubleObject::setValue(const std::string& value)
{
	mNativeValue = Tools::stringToDouble(value);
	mValue = Tools::toString(mNativeValue);		// this conversion is necessary because these two values could drift apart because std::string can also hold floating point values
}

std::string DoubleObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
}
