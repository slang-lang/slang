
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
		Object::operator_assign(&other);
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

void NumberObject::operator_assign(const NumberObject *other)
{
	mValue = other->getValue().toDouble();
}

void NumberObject::operator_assign(const Object *other)
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

void NumberObject::operator_divide(const NumberObject *other)
{
	mValue = mValue.toDouble() / other->getValue().toDouble();
}

void NumberObject::operator_divide(const Object *other)
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

bool NumberObject::operator_equal(const NumberObject *other)
{
	return mValue.toDouble() == other->getValue().toDouble();
}

bool NumberObject::operator_equal(const Object *other)
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

bool NumberObject::operator_greater(const NumberObject *other)
{
	return mValue.toDouble() > other->getValue().toDouble();
}

bool NumberObject::operator_greater(const Object *other)
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

bool NumberObject::operator_greater_equal(const NumberObject *other)
{
	return mValue.toDouble() >= other->getValue().toDouble();
}

bool NumberObject::operator_greater_equal(const Object *other)
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

bool NumberObject::operator_less(const NumberObject *other)
{
	return mValue.toDouble() < other->getValue().toDouble();
}

bool NumberObject::operator_less(const Object *other)
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

bool NumberObject::operator_less_equal(const NumberObject *other)
{
	return mValue.toDouble() <= other->getValue().toDouble();
}

bool NumberObject::operator_less_equal(const Object *other)
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

void NumberObject::operator_multiply(const NumberObject *other)
{
	mValue = mValue.toDouble() * other->getValue().toDouble();
}

void NumberObject::operator_multiply(const Object *other)
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

void NumberObject::operator_plus(const NumberObject *other)
{
	mValue = mValue.toDouble() + other->getValue().toDouble();
}

void NumberObject::operator_plus(const Object *other)
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

void NumberObject::operator_subtract(const NumberObject *other)
{
	mValue = mValue.toDouble() - other->getValue().toDouble();
}

void NumberObject::operator_subtract(const Object *other)
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
