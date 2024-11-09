
// Header
#include "Int16Type.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolType.h"
#include "DoubleType.h"
#include "EnumerationType.h"
#include "FloatType.h"
#include "Int32Type.h"
#include "Int64Type.h"
#include "StringObject.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue Int16Type::DEFAULTVALUE = AtomicValue( static_cast<int16_t>( 0 ) );
std::string Int16Type::TYPENAME = _int16;


Int16Type::Int16Type( int16_t value )
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
	mIsAtomicType = true;
}

Int16Type::Int16Type( const AtomicValue& value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( static_cast<int16_t>( value.toInt() ) ) )
{
	mIsAtomicType = true;
}

Int16Type::Int16Type( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

Int16Type::Int16Type( const Object& other )
: Object( other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE )
{
	// generic type cast

	mIsAtomicType = true;

	const std::string& target = other.QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other.isEnumerationValue() ) {
        mValue = static_cast<int16_t>( other.getValue().toInt() );
	}
	else {
		Object::operator_assign( &other );
	}
}

const std::string& Int16Type::getTypeName() const
{
	return TYPENAME;
}

void Int16Type::operator_assign( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int16_t>( other->getValue().toInt() );
	}
	else {
		Object::operator_assign( other );
	}
}

bool Int16Type::operator_bool() const
{
	return mValue.toBool();
}

void Int16Type::operator_bitand( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int16_t>( mValue.toInt() ) & static_cast<int16_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator&: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int16Type::operator_bitor( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int16_t>( mValue.toInt() ) | static_cast<int16_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator|: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int16Type::operator_divide( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int16_t>( mValue.toInt() ) / static_cast<int16_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int16Type::operator_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return static_cast<int16_t>( mValue.toInt() ) == static_cast<int16_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int16Type::operator_greater( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return static_cast<int16_t>( mValue.toInt() ) > static_cast<int16_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int16Type::operator_greater_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return static_cast<int16_t>( mValue.toInt() ) >= static_cast<int16_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int16Type::operator_less( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return static_cast<int16_t>( mValue.toInt() ) < static_cast<int16_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int16Type::operator_less_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return static_cast<int16_t>( mValue.toInt() ) <= static_cast<int16_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int16Type::operator_modulo( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int16_t>( mValue.toInt() ) % static_cast<int16_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator%: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int16Type::operator_multiply( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int16_t>( mValue.toInt() ) * static_cast<int16_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int16Type::operator_plus( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int16_t>( mValue.toInt() ) + static_cast<int16_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int16Type::operator_subtract( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = static_cast<int16_t>( mValue.toInt() ) - static_cast<int16_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int16Type::operator_unary_decrement()
{
	mValue = static_cast<int16_t>( mValue.toInt() ) - 1;
}

void Int16Type::operator_unary_increment()
{
	mValue = static_cast<int16_t>( mValue.toInt() ) + 1;
}

void Int16Type::operator_unary_minus()
{
	mValue = static_cast<int16_t>( mValue.toInt() ) * -1;
}

void Int16Type::operator_unary_not()
{
	mValue = static_cast<int16_t>( !mValue.toBool() );
}


}
}
