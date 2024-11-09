
// Header
#include "FloatType.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolType.h"
#include "DoubleType.h"
#include "EnumerationType.h"
#include "Int16Type.h"
#include "Int32Type.h"
#include "Int64Type.h"
#include "StringObject.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue FloatType::DEFAULTVALUE = AtomicValue( 0.0f );
std::string FloatType::TYPENAME = _float;


FloatType::FloatType( float value )
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
    mIsAtomicType = true;
}

FloatType::FloatType( const AtomicValue& value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value.toFloat() ) )
{
	mIsAtomicType = true;
}

FloatType::FloatType( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

FloatType::FloatType( const Object& other )
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
		mValue = other.getValue().toFloat();
	}
	else {
		Object::operator_assign( &other );
	}
}

void FloatType::operator_assign( const Object* other  )
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
        mValue = other->getValue().toFloat();
    }
    else {
        Object::operator_assign( other );
    }
}

bool FloatType::operator_bool() const
{
	return mValue.toBool();
}

void FloatType::operator_divide( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleType::TYPENAME ||
         target == EnumerationType::TYPENAME ||
         target == FloatType::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toFloat() / other->getValue().toFloat();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool FloatType::operator_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleType::TYPENAME ||
         target == EnumerationType::TYPENAME ||
         target == FloatType::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toFloat() == other->getValue().toFloat();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool FloatType::operator_greater( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleType::TYPENAME ||
         target == EnumerationType::TYPENAME ||
         target == FloatType::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toFloat() > other->getValue().toFloat();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool FloatType::operator_greater_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleType::TYPENAME ||
         target == EnumerationType::TYPENAME ||
         target == FloatType::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toFloat() >= other->getValue().toFloat();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool FloatType::operator_less( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleType::TYPENAME ||
         target == EnumerationType::TYPENAME ||
         target == FloatType::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toFloat() < other->getValue().toFloat();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool FloatType::operator_less_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleType::TYPENAME ||
         target == EnumerationType::TYPENAME ||
         target == FloatType::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toFloat() <= other->getValue().toFloat();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void FloatType::operator_multiply( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleType::TYPENAME ||
         target == EnumerationType::TYPENAME ||
         target == FloatType::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toFloat() * other->getValue().toFloat();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void FloatType::operator_plus( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleType::TYPENAME ||
         target == EnumerationType::TYPENAME ||
         target == FloatType::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toFloat() + other->getValue().toFloat();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void FloatType::operator_subtract( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == DoubleType::TYPENAME ||
         target == EnumerationType::TYPENAME ||
         target == FloatType::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == Int64Type::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = mValue.toFloat() - other->getValue().toFloat();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void FloatType::operator_unary_decrement()
{
	mValue = mValue.toFloat() - 1.f;
}

void FloatType::operator_unary_increment()
{
	mValue = mValue.toFloat() + 1.f;
}

void FloatType::operator_unary_minus()
{
	mValue = mValue.toFloat() * -1.f;
}

void FloatType::operator_unary_not()
{
	mValue = static_cast<float>( !mValue.toFloat() );
}


}
}
