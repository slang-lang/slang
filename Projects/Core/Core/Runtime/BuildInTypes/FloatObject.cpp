
// Header
#include "FloatObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "IntegerObject.h"
#include "StringObject.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue FloatObject::DEFAULTVALUE = AtomicValue(0.f);
std::string FloatObject::TYPENAME = _float;


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

	const std::string& target = other.QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		target == DoubleObject::TYPENAME ||
		target == FloatObject::TYPENAME ||
		target == IntegerObject::TYPENAME ||
		target == StringObject::TYPENAME ) {
		mValue = other.getValue().toFloat();
	}
	else {
		Object::operator_assign(&other);
	}
}

void FloatObject::operator_assign(const Object *other)
{
	const std::string& target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = other->getValue().toFloat();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool FloatObject::operator_bool() const
{
	return mValue.toBool();
}

void FloatObject::operator_divide(const Object *other)
{
	const std::string& target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = mValue.toFloat() / other->getValue().toFloat();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool FloatObject::operator_equal(const Object *other)
{
	const std::string& target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		return mValue.toFloat() == other->getValue().toFloat();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool FloatObject::operator_greater(const Object *other)
{
	const std::string& target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		return mValue.toFloat() > other->getValue().toFloat();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool FloatObject::operator_greater_equal(const Object *other)
{
	const std::string& target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		return mValue.toFloat() >= other->getValue().toFloat();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool FloatObject::operator_less(const Object *other)
{
	const std::string& target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		return mValue.toFloat() < other->getValue().toFloat();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool FloatObject::operator_less_equal(const Object *other)
{
	const std::string& target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		return mValue.toFloat() <= other->getValue().toFloat();
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void FloatObject::operator_multiply(const Object *other)
{
	const std::string& target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = mValue.toFloat() * other->getValue().toFloat();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void FloatObject::operator_plus(const Object *other)
{
	const std::string& target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = mValue.toFloat() + other->getValue().toFloat();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void FloatObject::operator_subtract(const Object *other)
{
	const std::string& target = other->QualifiedTypename();

	if ( target == FloatObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = mValue.toFloat() - other->getValue().toFloat();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
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
	mValue = static_cast<float>( !mValue.toFloat() );
}


}
}
