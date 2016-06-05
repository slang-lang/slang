
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


FloatObject::FloatObject(AtomicValue value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value.toFloat())
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

FloatObject::FloatObject(const std::string& name, float value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

FloatObject::FloatObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE)
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;

	std::string source = other.Typename();

	if ( source == BoolObject::TYPENAME ||
		 source == DoubleObject::TYPENAME ||
		 source == FloatObject::TYPENAME ||
		 source == IntegerObject::TYPENAME ||
		 source == NumberObject::TYPENAME ||
		 source == StringObject::TYPENAME ) {
		mValue = other.getValue().toFloat();
	}
	else {
		throw Utils::Exceptions::InvalidTypeCast("from " + source + " to " + TYPENAME);
	}
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
	mValue = other->getValue().toFloat();
}

void FloatObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = other->getValue().toFloat();
	}
	else {
		Object::operator_assign(other);
	}
}

bool FloatObject::operator_bool() const
{
	return mValue.toFloat() != 0.f;
}

void FloatObject::operator_divide(FloatObject *other)
{
	mValue = mValue.toFloat() / other->getValue().toFloat();
}

void FloatObject::operator_divide(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = mValue.toFloat() / other->getValue().toFloat();
	}
	else {
		Object::operator_divide(other);
	}
}

bool FloatObject::operator_equal(FloatObject *other) const
{
	return mValue.toFloat() == other->getValue().toFloat();
}

bool FloatObject::operator_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		return mValue.toFloat() == other->getValue().toFloat();
	}

	return Object::operator_equal(other);
}

bool FloatObject::operator_greater(FloatObject *other) const
{
	return mValue.toFloat() > other->getValue().toFloat();
}

bool FloatObject::operator_greater(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		return mValue.toFloat() > other->getValue().toFloat();
	}

	return Object::operator_greater(other);
}

bool FloatObject::operator_greater_equal(FloatObject *other) const
{
	return mValue.toFloat() >= other->getValue().toFloat();
}

bool FloatObject::operator_greater_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		return mValue.toFloat() >= other->getValue().toFloat();
	}

	return Object::operator_greater_equal(other);
}

bool FloatObject::operator_less(FloatObject *other) const
{
	return mValue.toFloat() < other->getValue().toFloat();
}

bool FloatObject::operator_less(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		return mValue.toFloat() < other->getValue().toFloat();
	}

	return Object::operator_less(other);
}

bool FloatObject::operator_less_equal(FloatObject *other) const
{
	return mValue.toFloat() <= other->getValue().toFloat();
}

bool FloatObject::operator_less_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		return mValue.toFloat() <= other->getValue().toFloat();
	}

	return Object::operator_less_equal(other);
}

void FloatObject::operator_multiply(FloatObject *other)
{
	mValue = mValue.toFloat() * other->getValue().toFloat();
}

void FloatObject::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = mValue.toFloat() * other->getValue().toFloat();
	}
	else {
		Object::operator_multiply(other);
	}
}

void FloatObject::operator_plus(FloatObject *other)
{
	mValue = mValue.toFloat() + other->getValue().toFloat();
}

void FloatObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = mValue.toFloat() + other->getValue().toFloat();
	}
	else {
		Object::operator_plus(other);
	}
}

void FloatObject::operator_subtract(FloatObject *other)
{
	mValue = mValue.toFloat() - other->getValue().toFloat();
}

void FloatObject::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	if ( target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
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

std::string FloatObject::ToString() const
{
	return Typename() + " " + getName() + " = " + mValue.toStdString();
}


}
}
