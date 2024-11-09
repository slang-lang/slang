
// Header
#include "DoubleType.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolType.h"
#include "EnumerationObject.h"
#include "FloatObject.h"
#include "Int16Type.h"
#include "Int32Type.h"
#include "Int64Type.h"
#include "StringObject.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue DoubleType::DEFAULTVALUE = AtomicValue( 0.0 );
std::string DoubleType::TYPENAME = _double;


DoubleType::DoubleType( double value )
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
	mIsAtomicType = true;
}

DoubleType::DoubleType( const AtomicValue& value )
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value.toDouble() ) )
{
	mIsAtomicType = true;
}

DoubleType::DoubleType( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

DoubleType::DoubleType( const Object& other )
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
		mValue = other.getValue().toDouble();
	}
	else {
		Object::operator_assign( &other );
	}
}

void DoubleType::operator_assign( const Object* other )
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
		mValue = other->getValue().toDouble();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleType::operator_bool() const
{
	return mValue.toBool();
}

void DoubleType::operator_divide( const Object* other )
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
		mValue = mValue.toDouble() / other->getValue().toDouble();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleType::operator_equal( const Object* other )
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
		return mValue.toDouble() == other->getValue().toDouble();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleType::operator_greater( const Object* other )
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
		return mValue.toDouble() > other->getValue().toDouble();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleType::operator_greater_equal( const Object* other )
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
		return mValue.toDouble() >= other->getValue().toDouble();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleType::operator_less( const Object* other )
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
		return mValue.toDouble() < other->getValue().toDouble();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool DoubleType::operator_less_equal( const Object* other )
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
		return mValue.toDouble() <= other->getValue().toDouble();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void DoubleType::operator_multiply( const Object* other )
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
		mValue = mValue.toDouble() * other->getValue().toDouble();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void DoubleType::operator_plus( const Object* other )
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
		mValue = mValue.toDouble() + other->getValue().toDouble();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void DoubleType::operator_subtract( const Object* other )
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
		mValue = mValue.toDouble() - other->getValue().toDouble();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void DoubleType::operator_unary_decrement()
{
	mValue = mValue.toDouble() - 1.0;
}

void DoubleType::operator_unary_increment()
{
	mValue = mValue.toDouble() + 1.0;
}

void DoubleType::operator_unary_minus()
{
	mValue = mValue.toDouble() * -1.0;
}

void DoubleType::operator_unary_not()
{
	mValue = static_cast<double>( !mValue.toDouble() );
}


}
}
