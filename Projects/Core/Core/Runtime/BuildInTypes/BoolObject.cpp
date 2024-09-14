
// Header
#include "BoolObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "DoubleObject.h"
#include "EnumerationObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "StringObject.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue BoolObject::DEFAULTVALUE = AtomicValue( false );
std::string BoolObject::TYPENAME = _bool;


BoolObject::BoolObject( bool value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
	mIsAtomicType = true;
}

BoolObject::BoolObject( const AtomicValue& value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value.toBool() ) )
{
	mIsAtomicType = true;
}

BoolObject::BoolObject( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

BoolObject::BoolObject( const Object& other )
: Object( other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE )
{
	// generic type cast

	mIsAtomicType = true;

	const std::string& target = other.QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == EnumerationObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ||
         other.isEnumerationValue() ) {
		mValue = other.getValue().toBool();
	}
	else {
		mValue = other.isValid();
	}
}

bool BoolObject::operator_bool() const
{
	return mValue.toBool();
}

void BoolObject::operator_assign( const Object* rvalue )
{
	const std::string& source = rvalue->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ||
		 source == DoubleObject::TYPENAME ||
		 source == EnumerationObject::TYPENAME ||
		 source == FloatObject::TYPENAME ||
		 source == IntegerObject::TYPENAME ||
		 source == StringObject::TYPENAME ||
         rvalue->isEnumerationValue() ) {
		mValue = rvalue->getValue().toBool();
		return;
	}
    else {
        mValue = rvalue->isValid();
    }
}

bool BoolObject::operator_equal( const Object* rvalue )
{
	const std::string& source = rvalue->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ||
		 source == DoubleObject::TYPENAME ||
		 source == EnumerationObject::TYPENAME ||
		 source == FloatObject::TYPENAME ||
		 source == IntegerObject::TYPENAME ||
		 source == StringObject::TYPENAME ||
         rvalue->isEnumerationValue() ) {
		return mValue.toBool() == rvalue->getValue().toBool();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + rvalue->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void BoolObject::operator_unary_not()
{
	mValue = !mValue.toBool();
}


}
}
