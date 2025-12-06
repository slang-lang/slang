
// Header
#include "OperatorOverloading.h"

// Library includes

// Project includes
#include <Core/AST/TreeInterpreter.h>
#include <Core/Common/Method.h>
#include <Core/Runtime/BuildInTypes/BoolType.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/EnumerationType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>
#include <Core/Runtime/BuildInTypes/Int16Type.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/Int64Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/BuildInTypes/UserType.h>
#include <Core/Runtime/BuildInTypes/VoidType.h>
#include <Core/Runtime/Exceptions.h>
#include "Utils.h"

// Namespace declarations


namespace Slang {
namespace Runtime {


void operator_binary_assign( Object* lvalue, Object* rvalue )
{
	if ( !lvalue || !rvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	const auto& source{ rvalue->QualifiedTypename() };
	const auto& target{ lvalue->QualifiedTypename() };

	if ( target == ANONYMOUS_OBJECT || source == target ) {
		// assign directly because our lvalue has not yet been initialized
		// or no type conversion is necessary
		lvalue->assign( *rvalue );
	}
	else if ( target == BoolType::TYPENAME ) {
		lvalue->assign( BoolType( rvalue->getValue().toBool() ) );
	}
	else if ( target == DoubleType::TYPENAME ) {
		lvalue->assign( DoubleType( rvalue->getValue().toDouble() ) );
	}
	else if ( target == FloatType::TYPENAME ) {
		lvalue->assign( FloatType( rvalue->getValue().toFloat() ) );
	}
	else if ( target == Int16Type::TYPENAME ) {
		lvalue->assign( Int16Type( rvalue->getValue().toInt() ) );
	}
	else if ( target == Int32Type::TYPENAME ) {
		lvalue->assign( Int32Type( rvalue->getValue().toInt() ) );
	}
	else if ( target == Int64Type::TYPENAME ) {
		lvalue->assign( Int64Type( rvalue->getValue().toInt() ) );
	}
	else if ( target == StringType::TYPENAME ) {
		lvalue->assign( StringType( rvalue->getValue().toStdString() ) );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;

		lvalue->assign( tmp );
	}
/*
	// special handling for enumeration values
	else if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && source == target ) {
		lvalue->setValue( rvalue->getValue().toInt() );
	}
*/
	// special handling for enumeration values
	else if ( lvalue->isEnumerationValue() && rvalue->QualifiedTypename() == _int32 ) {
		lvalue->setValue( rvalue->getValue().toInt() );
	}
	// special handling for enumeration values
	else if ( lvalue->QualifiedTypename() == _int32 && rvalue->isEnumerationValue() ) {
		lvalue->setValue( rvalue->getValue().toInt() );
	}
	// no atomic data type, so we have to look if our assign operator has been overwritten
	else {
		if ( !rvalue->isValid() ) {	// special handling for null object
			lvalue->assign( *rvalue );
			return;
		}

		if ( rvalue->isInstanceOf( lvalue->QualifiedTypename() ) ) {
			lvalue->assign( *rvalue );
			return;
		}

		// invalid binary assignment operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->QualifiedTypename() + ".operator=: conversion from " + rvalue->QualifiedTypename() + " to " + lvalue->QualifiedTypename() + " not supported" );
	}
}

void operator_binary_bitand( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary bitand operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator&()'" );
	}
}

void operator_binary_bitcomplement( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary bitcomplement operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator~()'" );
	}
}

void operator_binary_bitor( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	const auto& target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary bitor operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator|()'" );
	}
}

void operator_binary_divide( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary division operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator/()'" );
	}
}

bool operator_binary_equal( AST::TreeInterpreter* runtime, Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot compare null pointer to object" );
	}
	if ( !rvalue ) {
		throw Exceptions::AccessViolation( "cannot compare object to null pointer" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		return BoolType( lvalue->isValid() ).operator_equal( rvalue );
	}
	if ( target == DoubleType::TYPENAME ) {
		return DoubleType( lvalue->getValue().toDouble() ).operator_equal( rvalue );
	}
	if ( target == FloatType::TYPENAME ) {
		return FloatType( lvalue->getValue().toFloat() ).operator_equal( rvalue );
	}
	if ( target == Int16Type::TYPENAME ) {
		return Int16Type( lvalue->getValue().toInt() ).operator_equal( rvalue );
	}
	if ( target == Int32Type::TYPENAME ) {
		return Int32Type( lvalue->getValue().toInt() ).operator_equal( rvalue );
	}
	if ( target == Int64Type::TYPENAME ) {
		return Int64Type( lvalue->getValue().toInt() ).operator_equal( rvalue );
	}
	if ( target == StringType::TYPENAME ) {
		return StringType( lvalue->getValue().toStdString() ).operator_equal( rvalue );
	}
	if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		return tmp.operator_equal( rvalue );
	}
	if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && lvalue->QualifiedTypename() == rvalue->QualifiedTypename() ) {
		return lvalue->getValue().toInt() == rvalue->getValue().toInt();
	}

	ParameterList params;
	params.emplace_back( Parameter::CreateRuntime( rvalue->QualifiedTypename(), rvalue->getValue(), rvalue->getReference() ) );

	if ( auto* method = dynamic_cast<Common::Method*>( lvalue->resolveMethod( "operator==", params, false, Visibility::Public ) ) ) {
		Object tmp;
		runtime->execute( lvalue, method, params, &tmp );
		return isTrue( tmp );
	}

	// no equality operator found, so we have to compare our references
	return lvalue->operator_equal( rvalue );
}

bool operator_binary_greater( AST::TreeInterpreter* runtime, Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		return tmp.operator_greater( rvalue );
	}
	if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		return tmp.operator_greater( rvalue );
	}
	if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		return tmp.operator_greater( rvalue );
	}
	if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_greater( rvalue );
	}
	if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_greater( rvalue );
	}
	if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_greater( rvalue );
	}
	if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		return tmp.operator_greater( rvalue );
	}
	if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		return tmp.operator_greater( rvalue );
	}
	if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && lvalue->QualifiedTypename() == rvalue->QualifiedTypename() ) {
		return lvalue->getValue().toInt() > rvalue->getValue().toInt();
	}

	ParameterList params;
	params.emplace_back( Parameter::CreateRuntime( rvalue->QualifiedTypename(), rvalue->getValue(), rvalue->getReference() ) );

	Object tmp;
	auto* method = dynamic_cast<Common::Method*>( lvalue->resolveMethod( "operator>", params, false, Visibility::Public ) );
	runtime->execute( lvalue, method, params, &tmp );

	return isTrue( tmp );
}

bool operator_binary_greater_equal( AST::TreeInterpreter* runtime, Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		return tmp.operator_greater_equal( rvalue );
	}
	if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		return tmp.operator_greater_equal( rvalue );
	}
	if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		return tmp.operator_greater_equal( rvalue );
	}
	if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_greater_equal( rvalue );
	}
	if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_greater_equal( rvalue );
	}
	if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_greater_equal( rvalue );
	}
	if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		return tmp.operator_greater_equal( rvalue );
	}
	if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		return tmp.operator_greater_equal( rvalue );
	}
	if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && lvalue->QualifiedTypename() == rvalue->QualifiedTypename() ) {
		return lvalue->getValue().toInt() >= rvalue->getValue().toInt();
	}

	ParameterList params;
	params.emplace_back( Parameter::CreateRuntime( rvalue->QualifiedTypename(), rvalue->getValue(), rvalue->getReference() ) );

	Object tmp;
	auto* method = dynamic_cast<Common::Method*>( lvalue->resolveMethod( "operator>=", params, false, Visibility::Public ) );
	runtime->execute( lvalue, method, params, &tmp );

	return isTrue( tmp );
}

bool operator_binary_less( AST::TreeInterpreter* runtime, Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		return tmp.operator_less( rvalue );
	}
	if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		return tmp.operator_less( rvalue );
	}
	if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		return tmp.operator_less( rvalue );
	}
	if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_less( rvalue );
	}
	if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_less( rvalue );
	}
	if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_less( rvalue );
	}
	if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		return tmp.operator_less( rvalue );
	}
	if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		return tmp.operator_less( rvalue );
	}
	if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && lvalue->QualifiedTypename() == rvalue->QualifiedTypename() ) {
		return lvalue->getValue().toInt() < rvalue->getValue().toInt();
	}

	ParameterList params;
	params.emplace_back( Parameter::CreateRuntime( rvalue->QualifiedTypename(), rvalue->getValue(), rvalue->getReference() ) );

	Object tmp;
	auto* method = dynamic_cast<Common::Method*>( lvalue->resolveMethod( "operator<", params, false, Visibility::Public ) );
	runtime->execute( lvalue, method, params, &tmp );

	return isTrue( tmp );
}

bool operator_binary_less_equal( AST::TreeInterpreter* runtime, Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		return tmp.operator_less_equal( rvalue );
	}
	if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		return tmp.operator_less_equal( rvalue );
	}
	if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		return tmp.operator_less_equal( rvalue );
	}
	if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_less_equal( rvalue );
	}
	if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_less_equal( rvalue );
	}
	if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		return tmp.operator_less_equal( rvalue );
	}
	if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		return tmp.operator_less_equal( rvalue );
	}
	if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		return tmp.operator_less_equal( rvalue );
	}
	if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && lvalue->QualifiedTypename() == rvalue->QualifiedTypename() ) {
		return lvalue->getValue().toInt() <= rvalue->getValue().toInt();
	}

	ParameterList params;
	params.emplace_back( Parameter::CreateRuntime( rvalue->QualifiedTypename(), rvalue->getValue(), rvalue->getReference() ) );

	Object tmp;
	auto* method = dynamic_cast<Common::Method*>( lvalue->resolveMethod( "operator<=", params, false, Visibility::Public ) );
	runtime->execute( lvalue, method, params, &tmp );

	return isTrue( tmp );
}

void operator_binary_modulo( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary modulo operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator%()'" );
	}
}

void operator_binary_multiply( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if (target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if (target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary multiply operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator*()'" );
	}
}

void operator_binary_plus( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary addition operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator+()'" );
	}
}

void operator_binary_shift_left( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_shift_left( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_shift_left( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_shift_left( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_shift_left( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_shift_left( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_shift_left( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid left shift operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator<<()'" );
	}
}

void operator_binary_shift_right( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_shift_right( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_shift_right( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_shift_right( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_shift_right( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_shift_right( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_shift_right( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid right shift operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator>>()'" );
	}
}

void operator_binary_subtract( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary subtract operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator-()'" );
	}
}

void operator_unary_decrement (Object* lvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "null pointer access" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else {
		// invalid decrement operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator--()'" );
	}
}

void operator_unary_increment( Object* lvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "null pointer access" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->isValid() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else {
		// invalid increment operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator++()'" );
	}
}

void operator_unary_minus( Object* lvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "null pointer access" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->getValue().toBool() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if (target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else {
		// invalid unary minus operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".-operator()'" );
	}
}

void operator_unary_plus( Object* lvalue )
{
	if ( !lvalue ) {
		throw Exceptions::AccessViolation( "null pointer access" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolType::TYPENAME ) {
		BoolType tmp( lvalue->getValue().toBool() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == DoubleType::TYPENAME ) {
		DoubleType tmp( lvalue->getValue().toDouble() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == FloatType::TYPENAME ) {
		FloatType tmp( lvalue->getValue().toFloat() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == Int16Type::TYPENAME ) {
		Int16Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == Int32Type::TYPENAME ) {
		Int32Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == Int64Type::TYPENAME ) {
		Int64Type tmp( lvalue->getValue().toInt() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == StringType::TYPENAME ) {
		StringType tmp( lvalue->getValue().toStdString() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == VoidType::TYPENAME ) {
		VoidType tmp;
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else {
		// invalid unary plus operator handling!
		throw Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".+operator()'" );
	}
}

void operator_unary_not( Object* base )
{
	if ( !base ) {
		throw Exceptions::AccessViolation( "null pointer access" );
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolType::TYPENAME ) {
		BoolType tmp( base->isValid() );

		*base = BoolType( !tmp.operator_bool() );
	}
	else if ( source == DoubleType::TYPENAME ) {
		DoubleType tmp( base->getValue() );

		*base = BoolType( !tmp.operator_bool() );
	}
	else if ( source == FloatType::TYPENAME ) {
		FloatType tmp( base->getValue() );

		*base = BoolType( !tmp.operator_bool() );
	}
	else if ( source == Int16Type::TYPENAME ) {
		Int16Type tmp( base->getValue() );

		*base = BoolType( !tmp.operator_bool() );
	}
	else if ( source == Int32Type::TYPENAME ) {
		Int32Type tmp( base->getValue() );

		*base = BoolType( !tmp.operator_bool() );
	}
	else if ( source == Int64Type::TYPENAME ) {
		Int64Type tmp( base->getValue() );

		*base = BoolType( !tmp.operator_bool() );
	}
	else if ( source == StringType::TYPENAME ) {
		StringType tmp( base->getValue() );

		*base = BoolType( !tmp.operator_bool() );
	}
	else if ( source == VoidType::TYPENAME ) {
		VoidType tmp;

		*base = BoolType( !tmp.operator_bool() );
	}
	else {
		*base = BoolType( !base->isValid() );
	}
}

void operator_unary_validate( Object* base )
{
	if ( !base ) {
		throw Exceptions::AccessViolation( "null pointer access" );
	}

	if ( !base->isValid() ) {
		throw ControlFlow::Throw;
	}
}


}
}
