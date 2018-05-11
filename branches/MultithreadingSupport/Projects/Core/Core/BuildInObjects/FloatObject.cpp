
// Header
#include "FloatObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Common/Exceptions.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "IntegerObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


AtomicValue FloatObject::DEFAULTVALUE = AtomicValue(0.f);
std::string FloatObject::TYPENAME = "float";


FloatObject::FloatObject(const AtomicValue& value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue(value.toFloat()))
{
	mIsAtomicType = true;
}

FloatObject::FloatObject(const std::string& name, const AtomicValue& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
}

FloatObject::FloatObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE)
{
	// generic type cast

	mIsAtomicType = true;

	std::string source = other.QualifiedTypename();

	if ( source == BoolObject::TYPENAME ||
		 source == DoubleObject::TYPENAME ||
		 source == FloatObject::TYPENAME ||
		 source == IntegerObject::TYPENAME ||
		 source == StringObject::TYPENAME ) {
		mValue = other.getValue().toFloat();
	}
	else {
		Object::operator_assign(&other);
	}
}

void FloatObject::operator_assign(const FloatObject *other)
{
	mValue = other->getValue().toFloat();
}

void FloatObject::operator_assign(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = other->getValue().toFloat();
	}
	else {
		Object::operator_assign(other);
	}
}

bool FloatObject::operator_bool() const
{
	return mValue.toBool();
}

void FloatObject::operator_divide(const FloatObject *other)
{
	mValue = mValue.toFloat() / other->getValue().toFloat();
}

void FloatObject::operator_divide(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = mValue.toFloat() / other->getValue().toFloat();
	}
	else {
		Object::operator_divide(other);
	}
}

bool FloatObject::operator_equal(const FloatObject *other)
{
	return mValue.toFloat() == other->getValue().toFloat();
}

bool FloatObject::operator_equal(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		return mValue.toFloat() == other->getValue().toFloat();
	}

	return Object::operator_equal(other);
}

bool FloatObject::operator_greater(const FloatObject *other)
{
	return mValue.toFloat() > other->getValue().toFloat();
}

bool FloatObject::operator_greater(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		return mValue.toFloat() > other->getValue().toFloat();
	}

	return Object::operator_greater(other);
}

bool FloatObject::operator_greater_equal(const FloatObject *other)
{
	return mValue.toFloat() >= other->getValue().toFloat();
}

bool FloatObject::operator_greater_equal(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		return mValue.toFloat() >= other->getValue().toFloat();
	}

	return Object::operator_greater_equal(other);
}

bool FloatObject::operator_less(const FloatObject *other)
{
	return mValue.toFloat() < other->getValue().toFloat();
}

bool FloatObject::operator_less(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		return mValue.toFloat() < other->getValue().toFloat();
	}

	return Object::operator_less(other);
}

bool FloatObject::operator_less_equal(const FloatObject *other)
{
	return mValue.toFloat() <= other->getValue().toFloat();
}

bool FloatObject::operator_less_equal(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		return mValue.toFloat() <= other->getValue().toFloat();
	}

	return Object::operator_less_equal(other);
}

void FloatObject::operator_multiply(const FloatObject *other)
{
	mValue = mValue.toFloat() * other->getValue().toFloat();
}

void FloatObject::operator_multiply(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = mValue.toFloat() * other->getValue().toFloat();
	}
	else {
		Object::operator_multiply(other);
	}
}

void FloatObject::operator_plus(const FloatObject *other)
{
	mValue = mValue.toFloat() + other->getValue().toFloat();
}

void FloatObject::operator_plus(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = mValue.toFloat() + other->getValue().toFloat();
	}
	else {
		Object::operator_plus(other);
	}
}

void FloatObject::operator_subtract(const FloatObject *other)
{
	mValue = mValue.toFloat() - other->getValue().toFloat();
}

void FloatObject::operator_subtract(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = mValue.toFloat() - other->getValue().toFloat();
	}
	else {
		Object::operator_subtract(other);
	}
}

void FloatObject::operator_unary_decrement()
{
	mValue = mValue.toFloat() - 1.f;
}

void FloatObject::operator_unary_increment()
{
	mValue = mValue.toFloat() + 1.f;
}

void FloatObject::operator_unary_minus()
{
	mValue = mValue.toFloat() * -1.f;
}

void FloatObject::operator_unary_not()
{
	mValue = (float)!mValue.toFloat();
}


}
}
