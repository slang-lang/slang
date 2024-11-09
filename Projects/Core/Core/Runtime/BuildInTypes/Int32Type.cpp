
// Header
#include "Int32Type.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolType.h"
#include "DoubleType.h"
#include "EnumerationObject.h"
#include "FloatObject.h"
#include "Int16Type.h"
#include "Int64Type.h"
#include "StringObject.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue Int32Type::DEFAULTVALUE = AtomicValue( static_cast<int32_t>( 0 ) );
std::string Int32Type::TYPENAME = _int32;


Int32Type::Int32Type( int32_t value )
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
	mIsAtomicType = true;
}

Int32Type::Int32Type( const AtomicValue& value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value.toInt() ) )
{
	mIsAtomicType = true;
}

Int32Type::Int32Type( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

Int32Type::Int32Type( const Object& other )
: Object( other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE )
{
	// generic type cast

	mIsAtomicType = true;

	const std::string& target = other.QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other.isEnumerationValue() ) {
		mValue = static_cast<int32_t>( other.getValue().toInt() );
	}
	else {
		Object::operator_assign( &other );
	}
}

const std::string& Int32Type::getTypeName() const
{
	return TYPENAME;
}

void Int32Type::operator_assign( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int32_t>( other->getValue().toInt() );
	}
	else {
		Object::operator_assign( other );
	}
}

bool Int32Type::operator_bool() const
{
	return mValue.toBool();
}

void Int32Type::operator_bitand( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int32_t>( mValue.toInt() ) & static_cast<int32_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator&: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int32Type::operator_bitor( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int32_t>( mValue.toInt() ) | static_cast<int32_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator|: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int32Type::operator_divide( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int32_t>( mValue.toInt() ) / static_cast<int32_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int32Type::operator_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return static_cast<int32_t>( mValue.toInt() ) == static_cast<int32_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int32Type::operator_greater( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return static_cast<int32_t>( mValue.toInt() ) > static_cast<int32_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int32Type::operator_greater_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return static_cast<int32_t>( mValue.toInt() ) >= static_cast<int32_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int32Type::operator_less( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return static_cast<int32_t>( mValue.toInt() ) < static_cast<int32_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int32Type::operator_less_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return static_cast<int32_t>( mValue.toInt() ) <= static_cast<int32_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int32Type::operator_modulo( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int32_t>( mValue.toInt() ) % static_cast<int32_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator%: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int32Type::operator_multiply( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int32_t>( mValue.toInt() ) * static_cast<int32_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int32Type::operator_plus( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int32_t>( mValue.toInt() ) + static_cast<int32_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int32Type::operator_subtract( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int32_t>( mValue.toInt() ) - static_cast<int32_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int32Type::operator_unary_decrement()
{
	mValue = static_cast<int32_t>( mValue.toInt() ) - 1;
}

void Int32Type::operator_unary_increment()
{
	mValue = static_cast<int32_t>( mValue.toInt() ) + 1;
}

void Int32Type::operator_unary_minus()
{
	mValue = static_cast<int32_t>( mValue.toInt() ) * -1;
}

void Int32Type::operator_unary_not()
{
	mValue = static_cast<int32_t>( !mValue.toBool() );
}


}
}
