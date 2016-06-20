
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
AtomicValue DoubleObject::ATOMIC_DEFAULTVALUE = 0.0;
std::string DoubleObject::TYPENAME = "double";


DoubleObject::DoubleObject(AtomicValue value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value.toDouble())
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

DoubleObject::DoubleObject(const std::string& name, double value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

DoubleObject::DoubleObject(const Object& other)
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

const std::string& DoubleObject::getTypeName() const
{
	return TYPENAME;
}

bool DoubleObject::isValid() const
{
	return mIsConstructed;
}

void DoubleObject::operator_assign(const DoubleObject *other)
{
	mValue = other->getValue().toDouble();
}

void DoubleObject::operator_assign(const Object *other)
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

bool DoubleObject::operator_bool() const
{
	return mValue.toBool();
}

void DoubleObject::operator_divide(const DoubleObject *other)
{
	mValue = mValue.toDouble() / other->getValue().toDouble();
}

void DoubleObject::operator_divide(const Object *other)
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

bool DoubleObject::operator_equal(const DoubleObject *other)
{
	return mValue.toDouble() == other->getValue().toDouble();
}

bool DoubleObject::operator_equal(const Object *other)
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

bool DoubleObject::operator_greater(const DoubleObject *other)
{
	return mValue.toDouble() > other->getValue().toDouble();
}

bool DoubleObject::operator_greater(const Object *other)
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

bool DoubleObject::operator_greater_equal(const DoubleObject *other)
{
	return mValue.toDouble() >= other->getValue().toDouble();
}

bool DoubleObject::operator_greater_equal(const Object *other)
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

bool DoubleObject::operator_less(const DoubleObject *other)
{
	return mValue.toDouble() < other->getValue().toDouble();
}

bool DoubleObject::operator_less(const Object *other)
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

bool DoubleObject::operator_less_equal(const DoubleObject *other)
{
	return mValue.toDouble() <= other->getValue().toDouble();
}

bool DoubleObject::operator_less_equal(const Object *other)
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

void DoubleObject::operator_multiply(const DoubleObject *other)
{
	mValue = mValue.toDouble() * other->getValue().toDouble();
}

void DoubleObject::operator_multiply(const Object *other)
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

void DoubleObject::operator_plus(const DoubleObject *other)
{
	mValue = mValue.toDouble() + other->getValue().toDouble();
}

void DoubleObject::operator_plus(const Object *other)
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

void DoubleObject::operator_subtract(const DoubleObject *other)
{
	mValue = mValue.toDouble() - other->getValue().toDouble();
}

void DoubleObject::operator_subtract(const Object *other)
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

void DoubleObject::operator_unary_decrement()
{
	mValue = mValue.toDouble() - 1.0;
}

void DoubleObject::operator_unary_increment()
{
	mValue = mValue.toDouble() + 1.0;
}

void DoubleObject::operator_unary_minus()
{
	mValue = mValue.toDouble() * -1.0;
}

void DoubleObject::operator_unary_not()
{
	mValue = (double)!mValue.toDouble();
}

std::string DoubleObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue().toStdString();
}


}
}
