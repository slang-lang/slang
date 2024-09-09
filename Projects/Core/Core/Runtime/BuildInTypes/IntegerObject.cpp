
// Header
#include "IntegerObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "EnumerationObject.h"
#include "FloatObject.h"
#include "StringObject.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue IntegerObject::DEFAULTVALUE = AtomicValue( 0 );
std::string IntegerObject::TYPENAME = _int;


IntegerObject::IntegerObject( int32_t value )
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
	mIsAtomicType = true;
}

IntegerObject::IntegerObject( const AtomicValue& value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value.toInt() ) )
{
	mIsAtomicType = true;
}

IntegerObject::IntegerObject( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

IntegerObject::IntegerObject( const Object& other )
: Object( other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE )
{
	// generic type cast

	mIsAtomicType = true;

	const std::string& target = other.QualifiedTypename();

	if ( target == IntegerObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other.isEnumerationValue() ) {
		mValue = other.getValue().toInt();
	}
	else {
		Object::operator_assign( &other );
	}
}

const std::string& IntegerObject::getTypeName() const
{
	return TYPENAME;
}

void IntegerObject::operator_assign( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = other->getValue().toInt();
	}
	else {
		Object::operator_assign( other );
	}
}

bool IntegerObject::operator_bool() const
{
	return mValue.toBool();
}

void IntegerObject::operator_bitand( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toInt() & other->getValue().toInt();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator&: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void IntegerObject::operator_bitor( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toInt() | other->getValue().toInt();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator|: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void IntegerObject::operator_divide( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toInt() / other->getValue().toInt();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool IntegerObject::operator_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toInt() == other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool IntegerObject::operator_greater( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toInt() > other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool IntegerObject::operator_greater_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toInt() >= other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool IntegerObject::operator_less( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toInt() < other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool IntegerObject::operator_less_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toInt() <= other->getValue().toInt();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void IntegerObject::operator_modulo( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toInt() % other->getValue().toInt();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator%: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void IntegerObject::operator_multiply( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toInt() * other->getValue().toInt();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void IntegerObject::operator_plus( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toInt() + other->getValue().toInt();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void IntegerObject::operator_subtract( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toInt() - other->getValue().toInt();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
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
	mValue = static_cast<int32_t>( !mValue.toBool() );
}


}
}
