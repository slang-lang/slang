
// Header
#include "OperatorOverloading.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Runtime/BuildInTypes/BoolObject.h>
#include <Core/Runtime/BuildInTypes/DoubleObject.h>
#include <Core/Runtime/BuildInTypes/EnumerationObject.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/BuildInTypes/UserObject.h>
#include <Core/Runtime/BuildInTypes/VoidObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/Tools.h>

// Namespace declarations


namespace Slang {
namespace Runtime {


void operator_binary_assign( Object* lvalue, Object* rvalue )
{
	if ( !lvalue || !rvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string source = rvalue->QualifiedTypename();
	std::string target = lvalue->QualifiedTypename();

	if ( target == ANONYMOUS_OBJECT || source == target ) {
		// assign directly because our lvalue has not yet been initialized
		// or no type conversion is necessary
		lvalue->assign( *rvalue );
	}
	else if ( target == BoolObject::TYPENAME ) {
		lvalue->assign( BoolObject( rvalue ) );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		lvalue->assign( DoubleObject( rvalue ) );
	}
	else if ( target == FloatObject::TYPENAME ) {
		lvalue->assign( FloatObject( rvalue ) );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		lvalue->assign( IntegerObject( rvalue ) );
	}
	else if ( target == StringObject::TYPENAME ) {
		lvalue->assign( StringObject( rvalue ) );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;

		lvalue->assign( tmp );
	}
/*
	// special handling for enumeration values
	else if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && source == target ) {
		lvalue->setValue( rvalue->getValue().toInt() );
	}
*/
	// special handling for enumeration values
	else if ( lvalue->isEnumerationValue() && rvalue->QualifiedTypename() == _int ) {
		lvalue->setValue( rvalue->getValue().toInt() );
	}
	// special handling for enumeration values
	else if ( lvalue->QualifiedTypename() == _int && rvalue->isEnumerationValue() ) {
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
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->QualifiedTypename() + ".operator=(" + rvalue->QualifiedTypename() + ")'" );
	}
}

void operator_binary_bitand( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitand( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary bitand operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator&()'" );
	}
}

void operator_binary_bitcomplement( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitcomplement( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary bitcomplement operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator~()'" );
	}
}

void operator_binary_bitor( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitor( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary bitor operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator|()'" );
	}
}

void operator_binary_divide( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_divide( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary division operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator/()'" );
	}
}

bool operator_binary_equal( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot compare null pointer to object" );
	}
	if ( !rvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot compare object to null pointer" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		return BoolObject( lvalue->isValid() ).operator_equal( rvalue );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		return DoubleObject( lvalue->getValue() ).operator_equal( rvalue );
	}
	else if ( target == FloatObject::TYPENAME ) {
		return FloatObject( lvalue->getValue() ).operator_equal( rvalue );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		return IntegerObject( lvalue->getValue() ).operator_equal( rvalue );
	}
	else if ( target == StringObject::TYPENAME ) {
		return StringObject( lvalue->getValue() ).operator_equal( rvalue );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_equal( rvalue );
	}
	else if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && lvalue->QualifiedTypename() == rvalue->QualifiedTypename() ) {
		return lvalue->getValue().toInt() == rvalue->getValue().toInt();
	}

	ParameterList params;
	params.push_back( Parameter::CreateRuntime( rvalue->QualifiedTypename(), rvalue->getValue(), rvalue->getReference() ) );

	if ( lvalue->resolveMethod( "operator==", params, false, Visibility::Public ) ) {
		Object tmp;
		lvalue->execute( &tmp, "operator==", params );
		return isTrue( tmp );
	}

	// no equality operator found, so we have to compare our references
	return lvalue->operator_equal( rvalue );
}

bool operator_binary_greater( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		return tmp.operator_greater( rvalue );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		return tmp.operator_greater( rvalue );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		return tmp.operator_greater( rvalue );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		return tmp.operator_greater( rvalue );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		return tmp.operator_greater( rvalue );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_greater( rvalue );
	}
	else if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && lvalue->QualifiedTypename() == rvalue->QualifiedTypename() ) {
		return lvalue->getValue().toInt() > rvalue->getValue().toInt();
	}

	ParameterList params;
	params.push_back( Parameter::CreateRuntime( rvalue->QualifiedTypename(), rvalue->getValue(), rvalue->getReference() ) );

	Object tmp;
	lvalue->execute( &tmp, "operator>", params );
	return isTrue( tmp );
}

bool operator_binary_greater_equal( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		return tmp.operator_greater_equal( rvalue );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		return tmp.operator_greater_equal( rvalue );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		return tmp.operator_greater_equal( rvalue );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		return tmp.operator_greater_equal( rvalue );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		return tmp.operator_greater_equal( rvalue );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_greater_equal( rvalue );
	}
	else if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && lvalue->QualifiedTypename() == rvalue->QualifiedTypename() ) {
		return lvalue->getValue().toInt() >= rvalue->getValue().toInt();
	}

	ParameterList params;
	params.push_back( Parameter::CreateRuntime( rvalue->QualifiedTypename(), rvalue->getValue(), rvalue->getReference() ) );

	Object tmp;
	lvalue->execute( &tmp, "operator>=", params );
	return isTrue( tmp );
}

bool operator_binary_less( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		return tmp.operator_less( rvalue );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		return tmp.operator_less( rvalue );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		return tmp.operator_less( rvalue );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		return tmp.operator_less( rvalue );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		return tmp.operator_less( rvalue );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_less( rvalue );
	}
	else if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && lvalue->QualifiedTypename() == rvalue->QualifiedTypename() ) {
		return lvalue->getValue().toInt() < rvalue->getValue().toInt();
	}

	ParameterList params;
	params.push_back( Parameter::CreateRuntime( rvalue->QualifiedTypename(), rvalue->getValue(), rvalue->getReference() ) );

	Object tmp;
	lvalue->execute( &tmp, "operator<", params );
	return isTrue( tmp );
}

bool operator_binary_less_equal( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		return tmp.operator_less_equal( rvalue );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		return tmp.operator_less_equal( rvalue );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		return tmp.operator_less_equal( rvalue );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		return tmp.operator_less_equal( rvalue );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		return tmp.operator_less_equal( rvalue );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_less_equal( rvalue );
	}
	else if ( lvalue->isEnumerationValue() && rvalue->isEnumerationValue() && lvalue->QualifiedTypename() == rvalue->QualifiedTypename() ) {
		return lvalue->getValue().toInt() <= rvalue->getValue().toInt();
	}

	ParameterList params;
	params.push_back( Parameter::CreateRuntime( rvalue->QualifiedTypename(), rvalue->getValue(), rvalue->getReference() ) );

	Object tmp;
	lvalue->execute( &tmp, "operator<=", params );
	return isTrue( tmp );
}

void operator_binary_modulo( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_modulo( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary modulo operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator%()'" );
	}
}

void operator_binary_multiply( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if (target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else if (target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_multiply( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary multiply operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator*()'" );
	}
}

void operator_binary_plus( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_plus( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary addition operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator+()'" );
	}
}

void operator_binary_subtract( Object* lvalue, Object* rvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "cannot add null pointer to object" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_subtract( rvalue );

		lvalue->assign( tmp );
	}
	else {
		// invalid binary subtract operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator-()'" );
	}
}

void operator_unary_decrement (Object* lvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "null pointer access" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_decrement();

		lvalue->assign( tmp );
	}
	else {
		// invalid decrement operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator--()'" );
	}
}

void operator_unary_increment( Object* lvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "null pointer access" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->isValid() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_increment();

		lvalue->assign( tmp );
	}
	else {
		// invalid increment operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".operator++()'" );
	}
}

void operator_unary_minus( Object* lvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "null pointer access" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->getValue() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if (target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_minus();

		lvalue->assign( tmp );
	}
	else {
		// invalid unary minus operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".-operator()'" );
	}
}

void operator_unary_plus( Object* lvalue )
{
	if ( !lvalue ) {
		throw Runtime::Exceptions::AccessViolation( "null pointer access" );
	}

	std::string target = lvalue->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ) {
		BoolObject tmp( lvalue->getValue() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == DoubleObject::TYPENAME ) {
		DoubleObject tmp( lvalue->getValue() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == FloatObject::TYPENAME ) {
		FloatObject tmp( lvalue->getValue() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == IntegerObject::TYPENAME ) {
		IntegerObject tmp( lvalue->getValue() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == StringObject::TYPENAME ) {
		StringObject tmp( lvalue->getValue() );
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else if ( target == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_plus();

		lvalue->assign( tmp );
	}
	else {
		// invalid unary plus operator handling!
		throw Runtime::Exceptions::InvalidOperation( "'" + lvalue->getFullScopeName() + ".+operator()'" );
	}
}

void operator_unary_not( Object* base )
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation( "null pointer access" );
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp( base->isValid() );

		*base = BoolObject( !tmp.operator_bool() );
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp( base->getValue() );

		*base = BoolObject( !tmp.operator_bool() );
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp( base->getValue() );

		*base = BoolObject( !tmp.operator_bool() );
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp( base->getValue() );

		*base = BoolObject( !tmp.operator_bool() );
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp( base->getValue() );

		*base = BoolObject( !tmp.operator_bool() );
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;

		*base = BoolObject( !tmp.operator_bool() );
	}
	else {
		*base = BoolObject( !base->isValid() );
	}
}

void operator_unary_validate( Object* base )
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation( "null pointer access" );
	}

	if ( !base->isValid() ) {
		throw ControlFlow::Throw;
	}
}


}
}
