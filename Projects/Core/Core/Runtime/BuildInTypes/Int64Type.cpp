
// Header
#include "Int64Type.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolType.h"
#include "DoubleType.h"
#include "EnumerationType.h"
#include "FloatType.h"
#include "Int16Type.h"
#include "Int32Type.h"
#include "StringType.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue Int64Type::DEFAULTVALUE = AtomicValue( static_cast<int64_t>( 0 ) );
std::string Int64Type::TYPENAME = _int64;


Int64Type::Int64Type( int64_t value )
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
	mIsAtomicType = true;
}

Int64Type::Int64Type( const AtomicValue& value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value.toInt() ) )
{
	mIsAtomicType = true;
}

Int64Type::Int64Type( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

Int64Type::Int64Type( const Object& other )
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
		 target == StringType::TYPENAME ||
		 other.isEnumerationValue() ) {
		mValue = static_cast<int64_t>( other.getValue().toInt() );
	}
	else {
		Object::operator_assign( &other );
	}
}

const std::string& Int64Type::getTypeName() const
{
	return TYPENAME;
}

void Int64Type::operator_assign( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		mValue = static_cast<int64_t>( other->getValue().toInt() );
	}
	else {
		Object::operator_assign( other );
	}
}

bool Int64Type::operator_bool() const
{
	return mValue.toBool();
}

void Int64Type::operator_bitand( const Object* other )
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
		mValue = static_cast<int64_t>( mValue.toInt() ) & static_cast<int64_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator&: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int64Type::operator_bitor( const Object* other )
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
		mValue = static_cast<int64_t>( mValue.toInt() ) | static_cast<int64_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator|: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int64Type::operator_divide( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		mValue = static_cast<int64_t>( mValue.toInt() ) / static_cast<int64_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int64Type::operator_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		return static_cast<int64_t>( mValue.toInt() ) == static_cast<int64_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int64Type::operator_greater( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		return static_cast<int64_t>( mValue.toInt() ) > static_cast<int64_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int64Type::operator_greater_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		return static_cast<int64_t>( mValue.toInt() ) >= static_cast<int64_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int64Type::operator_less( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		return static_cast<int64_t>( mValue.toInt() ) < static_cast<int64_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool Int64Type::operator_less_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		return static_cast<int64_t>( mValue.toInt() ) <= static_cast<int64_t>( other->getValue().toInt() );
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int64Type::operator_modulo( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		mValue = static_cast<int64_t>( mValue.toInt() ) % static_cast<int64_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator%: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int64Type::operator_multiply( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		mValue = static_cast<int64_t>( mValue.toInt() ) * static_cast<int64_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int64Type::operator_plus( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		mValue = static_cast<int64_t>( mValue.toInt() ) + static_cast<int64_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int64Type::operator_subtract( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolType::TYPENAME ||
		 target == DoubleType::TYPENAME ||
		 target == EnumerationType::TYPENAME ||
		 target == FloatType::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == Int64Type::TYPENAME ||
		 target == StringType::TYPENAME ||
		 other->isEnumerationValue() ) {
		mValue = static_cast<int64_t>( mValue.toInt() ) - static_cast<int64_t>( other->getValue().toInt() );
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void Int64Type::operator_unary_decrement()
{
	mValue = static_cast<int64_t>( mValue.toInt() ) - 1;
}

void Int64Type::operator_unary_increment()
{
	mValue = static_cast<int64_t>( mValue.toInt() ) + 1;
}

void Int64Type::operator_unary_minus()
{
	mValue = static_cast<int64_t>( mValue.toInt() ) * -1;
}

void Int64Type::operator_unary_not()
{
	mValue = static_cast<int64_t>( !mValue.toBool() );
}


}
}
