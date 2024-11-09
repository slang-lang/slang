
// Header
#include "StringType.h"

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
#include "Int64Type.h"
#include "UserObject.h"
#include "VoidObject.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue StringType::DEFAULTVALUE = AtomicValue( std::string( "" ) );
std::string StringType::TYPENAME = _string;


StringType::StringType( const AtomicValue& value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value.toStdString() ) )
{
	mIsAtomicType = true;
}

StringType::StringType(  const std::string& value)
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
	mIsAtomicType = true;
}

StringType::StringType( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

StringType::StringType( const Object& other )
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
		mValue = other.getValue().toStdString();
	}
	else {
		Object::operator_assign( &other );
	}
}

void StringType::operator_assign( const Object* other )
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
		mValue = other->getValue().toStdString();
	}
    else {
        Object::operator_assign( other );
    }
}

bool StringType::operator_bool() const
{
	return mValue.toBool();
}

bool StringType::operator_equal( const Object* other )
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
		return mValue.toStdString() == other->getValue().toStdString();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool StringType::operator_greater( const Object* other )
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
		return mValue.toStdString() > other->getValue().toStdString();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool StringType::operator_greater_equal( const Object* other )
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
		return mValue.toStdString() >= other->getValue().toStdString();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool StringType::operator_less( const Object* other )
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
		return mValue.toStdString() < other->getValue().toStdString();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool StringType::operator_less_equal( const Object* other )
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
		return mValue.toStdString() <= other->getValue().toStdString();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void StringType::operator_plus( const Object* other )
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
		mValue = mValue.toStdString() + other->getValue().toStdString();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void StringType::operator_shift_left( const Object* other )
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
		mValue = mValue.toStdString() + other->getValue().toStdString();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}


}
}
