
// Header
#include "BoolType.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "DoubleType.h"
#include "EnumerationType.h"
#include "FloatType.h"
#include "Int16Type.h"
#include "Int32Type.h"
#include "Int64Type.h"
#include "StringType.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue BoolType::DEFAULTVALUE = AtomicValue( false );
std::string BoolType::TYPENAME = _bool;


BoolType::BoolType( bool value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value ) )
{
	mIsAtomicType = true;
}

BoolType::BoolType( const AtomicValue& value )
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue( value.toBool() ) )
{
	mIsAtomicType = true;
}

BoolType::BoolType( const std::string& name, const AtomicValue& value )
: Object( name, SYSTEM_LIBRARY, TYPENAME, value )
{
	mIsAtomicType = true;
}

BoolType::BoolType( const Object& other )
: Object( other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE )
{
	// generic type cast

	mIsAtomicType = true;

	const std::string& source = other.QualifiedTypename();

	if ( source == BoolType::TYPENAME ||
		 source == DoubleType::TYPENAME ||
		 source == EnumerationType::TYPENAME ||
		 source == FloatType::TYPENAME ||
		 source == Int16Type::TYPENAME ||
		 source == Int32Type::TYPENAME ||
		 source == Int64Type::TYPENAME ||
		 source == StringType::TYPENAME ||
         other.isEnumerationValue() ) {
		mValue = other.getValue().toBool();
	}
	else {
		mValue = other.isValid();
	}
}

bool BoolType::operator_bool() const
{
	return mValue.toBool();
}

void BoolType::operator_assign( const Object* rvalue )
{
	const std::string& source = rvalue->QualifiedTypename();

	if ( source == BoolType::TYPENAME ||
		 source == DoubleType::TYPENAME ||
		 source == EnumerationType::TYPENAME ||
		 source == FloatType::TYPENAME ||
		 source == Int16Type::TYPENAME ||
		 source == Int32Type::TYPENAME ||
		 source == Int64Type::TYPENAME ||
		 source == StringType::TYPENAME ||
         rvalue->isEnumerationValue() ) {
		mValue = rvalue->getValue().toBool();
	}
    else {
        mValue = rvalue->isValid();
    }
}

bool BoolType::operator_equal( const Object* rvalue )
{
	const std::string& source = rvalue->QualifiedTypename();

	if ( source == BoolType::TYPENAME ||
		 source == DoubleType::TYPENAME ||
		 source == EnumerationType::TYPENAME ||
		 source == FloatType::TYPENAME ||
		 source == Int16Type::TYPENAME ||
		 source == Int32Type::TYPENAME ||
		 source == Int64Type::TYPENAME ||
		 source == StringType::TYPENAME ||
         rvalue->isEnumerationValue() ) {
		return mValue.toBool() == rvalue->getValue().toBool();
	}

	throw Runtime::Exceptions::InvalidOperation( QualifiedTypename() + ".operator==: conversion from " + rvalue->QualifiedTypename() + " to " + QualifiedTypename() + " not supported" );
}

void BoolType::operator_unary_not()
{
	mValue = !mValue.toBool();
}


}
}
