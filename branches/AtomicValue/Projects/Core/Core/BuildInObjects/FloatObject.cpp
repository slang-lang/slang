
// Header
#include "FloatObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "IntegerObject.h"
#include "NumberObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


float FloatObject::DEFAULTVALUE = 0.f;
AtomicValue FloatObject::ATOMIC_DEFAULTVALUE = 0.f;
std::string FloatObject::TYPENAME = "float";


FloatObject::FloatObject(float value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

FloatObject::FloatObject(AtomicValue value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value.value.float_);
}

FloatObject::FloatObject(const std::string& name, float value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

FloatObject::FloatObject(const Object& other)
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

float FloatObject::getNativeValue() const
{
	return mNativeValue;
}

const std::string& FloatObject::getTypeName() const
{
	return TYPENAME;
}

bool FloatObject::isValid() const
{
	return mIsConstructed;
}

void FloatObject::operator_assign(FloatObject *other)
{
	setNativeValue(other->getNativeValue());
}

void FloatObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ) {
		setNativeValue(other->isValid());
	}
	else if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		FloatObject tmp(other->getValue());

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

bool FloatObject::operator_bool() const
{
	return mNativeValue != 0.f;
}

void FloatObject::operator_divide(FloatObject *other)
{
	setNativeValue(mNativeValue / other->getNativeValue());
}

void FloatObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		FloatObject tmp(other->getValue());

		operator_divide(&tmp);
	}
	else {
		Object::operator_divide(other);
	}
}

bool FloatObject::operator_equal(FloatObject *other) const
{
	return (mNativeValue == other->getNativeValue());
}

bool FloatObject::operator_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		FloatObject tmp(other->getValue());

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool FloatObject::operator_greater(FloatObject *other) const
{
	return (mNativeValue > other->getNativeValue());
}

bool FloatObject::operator_greater(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		FloatObject tmp(other->getValue());

		return operator_greater(&tmp);
	}

	return Object::operator_greater(other);
}

bool FloatObject::operator_greater_equal(FloatObject *other) const
{
	return (mNativeValue >= other->getNativeValue());
}

bool FloatObject::operator_greater_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		FloatObject tmp(other->getValue());

		return operator_greater_equal(&tmp);
	}

	return Object::operator_greater_equal(other);
}

bool FloatObject::operator_less(FloatObject *other) const
{
	return (mNativeValue < other->getNativeValue());
}

bool FloatObject::operator_less(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		FloatObject tmp(other->getValue());

		return operator_less(&tmp);
	}

	return Object::operator_less(other);
}

bool FloatObject::operator_less_equal(FloatObject *other) const
{
	return (mNativeValue <= other->getNativeValue());
}

bool FloatObject::operator_less_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		FloatObject tmp(other->getValue());

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

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		FloatObject tmp(other->getValue());

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

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		FloatObject tmp(other->getValue());

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

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		FloatObject tmp(other->getValue());

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
	//mValue = Tools::toString(value);
}

std::string FloatObject::ToString() const
{
	return Typename() + " " + getName() + " = " + Tools::ConvertToString(getValue().value.float_);
}


}
}
