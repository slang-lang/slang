
// Header
#include "StringObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "EnumerationObject.h"
#include "FloatObject.h"
#include "Int16Type.h"
#include "Int32Type.h"
#include "UserObject.h"
#include "VoidObject.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue StringObject::DEFAULTVALUE = AtomicValue( std::string( "" ) );
std::string StringObject::TYPENAME = _string;


StringObject::StringObject( const AtomicValue& value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value.toStdString() ) )
{
	mIsAtomicType = true;
}

StringObject::StringObject(  const std::string& value)
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
	mIsAtomicType = true;
}

StringObject::StringObject( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

StringObject::StringObject( const Object& other )
: Object( other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE )
{
	// generic type cast

	mIsAtomicType = true;

	const std::string& target = other.QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
         target == DoubleObject::TYPENAME ||
         target == EnumerationObject::TYPENAME ||
         target == FloatObject::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == StringObject::TYPENAME ||
         other.isEnumerationValue() ) {
		mValue = other.getValue().toStdString();
	}
	else {
		Object::operator_assign( &other );
	}
}

void StringObject::operator_assign( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
         target == DoubleObject::TYPENAME ||
         target == EnumerationObject::TYPENAME ||
         target == FloatObject::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		mValue = other->getValue().toStdString();
	}
    else {
        Object::operator_assign( other );
    }
}

bool StringObject::operator_bool() const
{
	return mValue.toBool();
}

bool StringObject::operator_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
         target == DoubleObject::TYPENAME ||
         target == EnumerationObject::TYPENAME ||
         target == FloatObject::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toStdString() == other->getValue().toStdString();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool StringObject::operator_greater( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
         target == DoubleObject::TYPENAME ||
         target == EnumerationObject::TYPENAME ||
         target == FloatObject::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toStdString() > other->getValue().toStdString();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool StringObject::operator_greater_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
         target == DoubleObject::TYPENAME ||
         target == EnumerationObject::TYPENAME ||
         target == FloatObject::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toStdString() >= other->getValue().toStdString();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool StringObject::operator_less( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
         target == DoubleObject::TYPENAME ||
         target == EnumerationObject::TYPENAME ||
         target == FloatObject::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toStdString() < other->getValue().toStdString();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

bool StringObject::operator_less_equal( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
         target == DoubleObject::TYPENAME ||
         target == EnumerationObject::TYPENAME ||
         target == FloatObject::TYPENAME ||
         target == Int16Type::TYPENAME ||
         target == Int32Type::TYPENAME ||
         target == StringObject::TYPENAME ||
         other->isEnumerationValue() ) {
		return mValue.toStdString() <= other->getValue().toStdString();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void StringObject::operator_plus( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
		 other->isEnumerationValue() ) {
		mValue = mValue.toStdString() + other->getValue().toStdString();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void StringObject::operator_shift_left( const Object* other )
{
	const std::string& target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == Int16Type::TYPENAME ||
		 target == Int32Type::TYPENAME ||
		 target == StringObject::TYPENAME ||
		 other->isEnumerationValue() ) {
		mValue = mValue.toStdString() + other->getValue().toStdString();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator<<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}


}
}
