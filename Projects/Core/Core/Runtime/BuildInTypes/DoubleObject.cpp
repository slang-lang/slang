
// Header
#include "DoubleObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolObject.h"
#include "EnumerationObject.h"
#include "FloatObject.h"
#include "Int32Type.h"
#include "StringObject.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue DoubleObject::DEFAULTVALUE = AtomicValue( 0.0 );
std::string DoubleObject::TYPENAME = _double;


DoubleObject::DoubleObject( double value )
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
	mIsAtomicType = true;
}

DoubleObject::DoubleObject( const AtomicValue& value )
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value.toDouble() ) )
{
	mIsAtomicType = true;
}

DoubleObject::DoubleObject( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

DoubleObject::DoubleObject( const Object& other )
: Object( other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE )
{
	// generic type cast

	mIsAtomicType = true;

	const std::string& target = other.QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		target == BoolObject::TYPENAME ||
		target == EnumerationObject::TYPENAME ||
		target == FloatObject::TYPENAME ||
		target == Int32Type::TYPENAME ||
		target == StringObject::TYPENAME ||
        other.isEnumerationValue() ) {
		mValue = other.getValue().toDouble();
	}
	else {
		Object::operator_assign( &other );
	}
}

void DoubleObject::operator_assign( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int32Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = other->getValue().toDouble();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleObject::operator_bool() const
{
	return mValue.toBool();
}

void DoubleObject::operator_divide( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int32Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toDouble() / other->getValue().toDouble();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleObject::operator_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int32Type::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toDouble() == other->getValue().toDouble();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleObject::operator_greater( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int32Type::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toDouble() > other->getValue().toDouble();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleObject::operator_greater_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int32Type::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toDouble() >= other->getValue().toDouble();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleObject::operator_less( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int32Type::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toDouble() < other->getValue().toDouble();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleObject::operator_less_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int32Type::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toDouble() <= other->getValue().toDouble();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void DoubleObject::operator_multiply( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int32Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toDouble() * other->getValue().toDouble();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void DoubleObject::operator_plus( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int32Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toDouble() + other->getValue().toDouble();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void DoubleObject::operator_subtract( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int32Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toDouble() - other->getValue().toDouble();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
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
	mValue = static_cast<double>( !mValue.toDouble() );
}


}
}
