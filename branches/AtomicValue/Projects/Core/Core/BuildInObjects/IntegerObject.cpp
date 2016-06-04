
// Header
#include "IntegerObject.h"

// Library includes

// Project includes
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
AtomicValue IntegerObject::ATOMIC_DEFAULTVALUE = 0;
std::string IntegerObject::TYPENAME = "int";


IntegerObject::IntegerObject(AtomicValue value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

IntegerObject::IntegerObject(const std::string& name, int value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

IntegerObject::IntegerObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, other.getValue())
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;

	std::string target = other.Typename();

	if ( target == BoolObject::TYPENAME ) {
		mValue = other.getValue().toBool();
	}
	else if ( target == IntegerObject::TYPENAME ||
			  target == DoubleObject::TYPENAME ||
			  target == FloatObject::TYPENAME ||
			  target == NumberObject::TYPENAME ||
			  target == StringObject::TYPENAME ) {
		setValue(other.getValue());	// this could probably speed things up a litte
	}
	else {
		throw Utils::Exceptions::InvalidTypeCast("from " + target + " to " + TYPENAME);
	}
}

const std::string& IntegerObject::getTypeName() const
{
	return TYPENAME;
}

bool IntegerObject::isValid() const
{
	return mIsConstructed;
}

void IntegerObject::operator_assign(IntegerObject *other)
{
	mValue = other->getValue().toInt();
}

void IntegerObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ) {
		mValue = other->getValue().toBool();
	}
	else if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		setValue(other->getValue());	// this could probably speed things up a litte
	}
	else {
		Object::operator_assign(other);
	}
}

bool IntegerObject::operator_bool() const
{
	return mValue.toInt() != 0;
}

void IntegerObject::operator_divide(IntegerObject *other)
{
	mValue = mValue.toInt() / other->getValue().toInt();
}

void IntegerObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		operator_divide(&tmp);
	}
	else {
		Object::operator_divide(other);
	}
}

bool IntegerObject::operator_equal(IntegerObject *other) const
{
	return mValue.toInt() == other->getValue().toInt();
}

bool IntegerObject::operator_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool IntegerObject::operator_greater(IntegerObject *other) const
{
	return mValue.toInt() > other->getValue().toInt();
}

bool IntegerObject::operator_greater(Object *other) const
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		return operator_greater(&tmp);
	}

	return Object::operator_greater(other);
}

bool IntegerObject::operator_greater_equal(IntegerObject *other) const
{
	return mValue.toInt() >= other->getValue().toInt();
}

bool IntegerObject::operator_greater_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		return operator_greater_equal(&tmp);
	}

	return Object::operator_greater_equal(other);
}

bool IntegerObject::operator_less(IntegerObject *other) const
{
	return mValue.toInt() < other->getValue().toInt();
}

bool IntegerObject::operator_less(Object *other) const
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		return operator_less(&tmp);
	}

	return Object::operator_less(other);
}

bool IntegerObject::operator_less_equal(IntegerObject *other) const
{
	return mValue.toInt() <= other->getValue().toInt();
}

bool IntegerObject::operator_less_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		return operator_less_equal(&tmp);
	}

	return Object::operator_less_equal(other);
}

void IntegerObject::operator_modulo(IntegerObject *other)
{
	mValue = mValue.toInt() % other->getValue().toInt();
}

void IntegerObject::operator_modulo(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		operator_modulo(&tmp);
	}
	else {
		Object::operator_modulo(other);
	}
}

void IntegerObject::operator_multiply(IntegerObject *other)
{
	mValue = mValue.toInt() * other->getValue().toInt();
}

void IntegerObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		operator_multiply(&tmp);
	}
	else {
		Object::operator_multiply(other);
	}
}

void IntegerObject::operator_plus(IntegerObject *other)
{
	mValue = mValue.toInt() + other->getValue().toInt();
}

void IntegerObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		operator_plus(&tmp);
	}
	else {
		Object::operator_plus(other);
	}
}

void IntegerObject::operator_subtract(IntegerObject *other)
{
	mValue = mValue.toInt() - other->getValue().toInt();
}

void IntegerObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		IntegerObject tmp(other->getValue());

		operator_subtract(&tmp);
	}
	else {
		Object::operator_subtract(other);
	}
}

void IntegerObject::operator_unary_decrement()
{
	mValue = mValue.toInt() - 1;
}

void IntegerObject::operator_unary_increment()
{
	mValue = mValue.toInt() + 1;
}

void IntegerObject::operator_unary_minus()
{
	mValue = mValue.toInt() * -1;
}

void IntegerObject::operator_unary_not()
{
	mValue = (int)!mValue.toBool();
}

std::string IntegerObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue().toStdString();
}


}
}
