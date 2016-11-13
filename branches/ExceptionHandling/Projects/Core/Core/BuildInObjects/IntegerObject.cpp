
// Header
#include "IntegerObject.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "FloatObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


AtomicValue IntegerObject::DEFAULTVALUE = 0;
std::string IntegerObject::TYPENAME = "int";


IntegerObject::IntegerObject(AtomicValue value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value.toInt())
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
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE)
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;

	std::string target = other.Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		mValue = other.getValue().toInt();
	}
	else {
		Object::operator_assign(&other);
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

void IntegerObject::operator_assign(const IntegerObject *other)
{
	mValue = other->getValue().toInt();
}

void IntegerObject::operator_assign(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		mValue = other->getValue().toInt();
	}
	else {
		Object::operator_assign(other);
	}
}

bool IntegerObject::operator_bool() const
{
	return mValue.toInt() != 0;
}

void IntegerObject::operator_divide(const IntegerObject *other)
{
	mValue = mValue.toInt() / other->getValue().toInt();
}

void IntegerObject::operator_divide(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		mValue = mValue.toInt() / other->getValue().toInt();
	}
	else {
		Object::operator_divide(other);
	}
}

bool IntegerObject::operator_equal(const IntegerObject *other)
{
	return mValue.toInt() == other->getValue().toInt();
}

bool IntegerObject::operator_equal(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		return mValue.toInt() == other->getValue().toInt();
	}

	return Object::operator_equal(other);
}

bool IntegerObject::operator_greater(const IntegerObject *other)
{
	return mValue.toInt() > other->getValue().toInt();
}

bool IntegerObject::operator_greater(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		return mValue.toInt() > other->getValue().toInt();
	}

	return Object::operator_greater(other);
}

bool IntegerObject::operator_greater_equal(const IntegerObject *other)
{
	return mValue.toInt() >= other->getValue().toInt();
}

bool IntegerObject::operator_greater_equal(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		return mValue.toInt() >= other->getValue().toInt();
	}

	return Object::operator_greater_equal(other);
}

bool IntegerObject::operator_less(const IntegerObject *other)
{
	return mValue.toInt() < other->getValue().toInt();
}

bool IntegerObject::operator_less(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		return mValue.toInt() < other->getValue().toInt();
	}

	return Object::operator_less(other);
}

bool IntegerObject::operator_less_equal(const IntegerObject *other)
{
	return mValue.toInt() <= other->getValue().toInt();
}

bool IntegerObject::operator_less_equal(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		return mValue.toInt() <= other->getValue().toInt();
	}

	return Object::operator_less_equal(other);
}

void IntegerObject::operator_modulo(const IntegerObject *other)
{
	mValue = mValue.toInt() % other->getValue().toInt();
}

void IntegerObject::operator_modulo(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		mValue = mValue.toInt() % other->getValue().toInt();
	}
	else {
		Object::operator_modulo(other);
	}
}

void IntegerObject::operator_multiply(const IntegerObject *other)
{
	mValue = mValue.toInt() * other->getValue().toInt();
}

void IntegerObject::operator_multiply(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		mValue = mValue.toInt() * other->getValue().toInt();
	}
	else {
		Object::operator_multiply(other);
	}
}

void IntegerObject::operator_plus(const IntegerObject *other)
{
	mValue = mValue.toInt() + other->getValue().toInt();
}

void IntegerObject::operator_plus(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		mValue = mValue.toInt() + other->getValue().toInt();
	}
	else {
		Object::operator_plus(other);
	}
}

void IntegerObject::operator_subtract(const IntegerObject *other)
{
	mValue = mValue.toInt() - other->getValue().toInt();
}

void IntegerObject::operator_subtract(const Object *other)
{
	std::string target = other->Typename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		mValue = mValue.toInt() - other->getValue().toInt();
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

std::string IntegerObject::ToString(unsigned int indent) const
{
	return ::Utils::Tools::indent(indent) + Typename() + " " + getName() + " = " + getValue().toStdString();
}


}
}
