
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


NumberObject::NumberObject(AtomicValue value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value.toDouble())
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

NumberObject::NumberObject(const std::string& name, double value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

NumberObject::NumberObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE)
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;

	std::string source = other.Typename();

	if ( source == DoubleObject::TYPENAME ||
		 source == BoolObject::TYPENAME ||
		 source == FloatObject::TYPENAME ||
		 source == IntegerObject::TYPENAME ||
		 source == NumberObject::TYPENAME ||
		 source == StringObject::TYPENAME ) {
		mValue = other.getValue().toDouble();
	}
	else {
		throw Utils::Exceptions::InvalidTypeCast("from " + source + " to " + TYPENAME);
	}
}

const std::string& NumberObject::getTypeName() const
{
	return TYPENAME;
}

bool NumberObject::isValid() const
{
	return mIsConstructed;
}

void NumberObject::operator_assign(NumberObject *other)
{
	mValue = other->getValue().toDouble();
}

void NumberObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = other->getValue().toDouble();
	}
	else {
		Object::operator_assign(other);
	}
}

bool NumberObject::operator_bool() const
{
	return mValue.toDouble() != 0.0;
}

void NumberObject::operator_divide(NumberObject *other)
{
	mValue = mValue.toDouble() / other->getValue().toDouble();
}

void NumberObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = mValue.toDouble() / other->getValue().toDouble();
	}
	else {
		Object::operator_divide(other);
	}
}

bool NumberObject::operator_equal(NumberObject *other) const
{
	return mValue.toDouble() == other->getValue().toDouble();
}

bool NumberObject::operator_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		return mValue.toDouble() == other->getValue().toDouble();
	}

	return Object::operator_equal(other);
}

bool NumberObject::operator_greater(NumberObject *other) const
{
	return mValue.toDouble() > other->getValue().toDouble();
}

bool NumberObject::operator_greater(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		return mValue.toDouble() > other->getValue().toDouble();
	}

	return Object::operator_greater(other);
}

bool NumberObject::operator_greater_equal(NumberObject *other) const
{
	return mValue.toDouble() >= other->getValue().toDouble();
}

bool NumberObject::operator_greater_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		return mValue.toDouble() >= other->getValue().toDouble();
	}

	return Object::operator_greater_equal(other);
}

bool NumberObject::operator_less(NumberObject *other) const
{
	return mValue.toDouble() < other->getValue().toDouble();
}

bool NumberObject::operator_less(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		return mValue.toDouble() < other->getValue().toDouble();
	}

	return Object::operator_less(other);
}

bool NumberObject::operator_less_equal(NumberObject *other) const
{
	return mValue.toDouble() <= other->getValue().toDouble();
}

bool NumberObject::operator_less_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		return mValue.toDouble() <= other->getValue().toDouble();
	}

	return Object::operator_less_equal(other);
}

void NumberObject::operator_multiply(NumberObject *other)
{
	mValue = mValue.toDouble() * other->getValue().toDouble();
}

void NumberObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = mValue.toDouble() * other->getValue().toDouble();
	}
	else {
		Object::operator_multiply(other);
	}
}

void NumberObject::operator_plus(NumberObject *other)
{
	mValue = mValue.toDouble() + other->getValue().toDouble();
}

void NumberObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = mValue.toDouble() + other->getValue().toDouble();
	}
	else {
		Object::operator_plus(other);
	}
}

void NumberObject::operator_subtract(NumberObject *other)
{
	mValue = mValue.toDouble() - other->getValue().toDouble();
}

void NumberObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = mValue.toDouble() - other->getValue().toDouble();
	}
	else {
		Object::operator_subtract(other);
	}
}

void NumberObject::operator_unary_decrement()
{
	mValue = mValue.toDouble() - 1.0;
}

void NumberObject::operator_unary_increment()
{
	mValue = mValue.toDouble() + 1.0;
}

void NumberObject::operator_unary_minus()
{
	mValue = mValue.toDouble() * -1.0;
}

void NumberObject::operator_unary_not()
{
	mValue = (double)!mValue.toDouble();
}

std::string NumberObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue().toStdString();
}


}
}
