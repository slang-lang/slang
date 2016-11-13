
// Header
#include "OperatorOverloading.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


void operator_binary_assign(Object *base, Object *other)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();
	std::string target = other->Typename();

	if ( source == ANONYMOUS_OBJECT || source == target ) {
		// assign directly because our base has not yet been initialized
		// or no type conversion is necessary
		base->assign(*other);
	}
	else if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_assign(other);

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_assign(other);

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_assign(other);

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_assign(other);

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_assign(other);

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_assign(other);

		base->assign(tmp);
	}
	// no atomic data type, so we have to look if our assign operator has been overwritten
	else {
		base->operator_assign(other);
	}
}

void operator_binary_bitand(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_bitand(other);

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_bitand(other);

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_bitand(other);

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_bitand(other);

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_bitand(other);

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitand(other);

		base->assign(tmp);
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
		);

		VoidObject tmp;
		base->execute(&tmp, "operator&", params, 0);
	}
}

void operator_binary_bitcomplement(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitcomplement(other);

		base->assign(tmp);
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
		);

		VoidObject tmp;
		base->execute(&tmp, "operator~", params, 0);
	}
}

void operator_binary_bitor(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_bitor(other);

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_bitor(other);

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_bitor(other);

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_bitor(other);

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_bitor(other);

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitor(other);

		base->assign(tmp);
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
		);

		VoidObject tmp;
		base->execute(&tmp, "operator|", params, 0);
	}
}

void operator_binary_divide(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_divide(other);

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_divide(other);

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_divide(other);

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_divide(other);

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_divide(other);

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_divide(other);

		base->assign(tmp);
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
		);

		VoidObject tmp;
		base->execute(&tmp, "operator/", params, 0);
	}
}

bool operator_binary_equal(Object *base, Object *other)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Runtime::Exceptions::AccessViolation("cannot compare object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_equal(other);
		return tmp.operator_equal(other);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		return tmp.operator_equal(other);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		return tmp.operator_equal(other);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		return tmp.operator_equal(other);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		return tmp.operator_equal(other);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_equal(other);
	}

	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
	);

	if ( base->resolveMethod("operator==", params, false, Visibility::Public) ) {
		Object tmp;
		base->execute(&tmp, "operator==", params);
		return isTrue(tmp);
	}

	params.clear();
	params.push_back(
		Parameter(other->getName(), other->QualifiedOutterface(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
	);

	if ( base->resolveMethod("operator==", params, false, Visibility::Public) ) {
		Object tmp;
		base->execute(&tmp, "operator==", params);
		return isTrue(tmp);
	}

	// no equality operator found, so we have to compare our references
	return base->operator_equal(other);
}

bool operator_binary_greater(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		return tmp.operator_greater(other);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		return tmp.operator_greater(other);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		return tmp.operator_greater(other);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		return tmp.operator_greater(other);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		return tmp.operator_greater(other);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_greater(other);
	}

	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
	);

	Object tmp;
	base->execute(&tmp, "operator>", params);
	return isTrue(tmp);
}

bool operator_binary_greater_equal(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		return tmp.operator_greater_equal(other);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		return tmp.operator_greater_equal(other);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		return tmp.operator_greater_equal(other);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		return tmp.operator_greater_equal(other);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		return tmp.operator_greater_equal(other);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_greater_equal(other);
	}

	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
	);

	Object tmp;
	base->execute(&tmp, "operator>=", params, 0);
	return isTrue(tmp);
}

bool operator_binary_less(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		return tmp.operator_less(other);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		return tmp.operator_less(other);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		return tmp.operator_less(other);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		return tmp.operator_less(other);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		return tmp.operator_less(other);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_less(other);
	}

	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
	);

	Object tmp;
	base->execute(&tmp, "operator<", params, 0);
	return isTrue(tmp);
}

bool operator_binary_less_equal(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		return tmp.operator_less_equal(other);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		return tmp.operator_less_equal(other);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		return tmp.operator_less_equal(other);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		return tmp.operator_less_equal(other);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		return tmp.operator_less_equal(other);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_less_equal(other);
	}

	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
	);

	Object tmp;
	base->execute(&tmp, "operator<=", params, 0);
	return isTrue(tmp);
}

bool operator_binary_is(Object* base, Symbol* other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	return base->operator_is(other);
}

void operator_binary_modulo(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_modulo(other);

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_modulo(other);

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_modulo(other);

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_modulo(other);

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_modulo(other);

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_modulo(other);

		base->assign(tmp);
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
		);

		VoidObject tmp;
		base->execute(&tmp, "operator%", params, 0);
	}
}

void operator_binary_multiply(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_multiply(other);

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_multiply(other);

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_multiply(other);

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_multiply(other);

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_multiply(other);

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_multiply(other);

		base->assign(tmp);
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
		);

		VoidObject tmp;
		base->execute(&tmp, "operator*", params, 0);
	}
}

void operator_binary_plus(Object *base, Object *other)
{
	if ( !base /*|| !base->isValid()*/ ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_plus(other);

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_plus(other);

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_plus(other);

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_plus(other);

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_plus(other);

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_plus(other);

		base->assign(tmp);
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
		);

		VoidObject tmp;
		base->execute(&tmp, "operator+", params, 0);
	}
}

void operator_binary_subtract(Object *base, Object *other)
{
	if ( !base || !base->isValid() ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_subtract(other);

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_subtract(other);

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_subtract(other);

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_subtract(other);

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_subtract(other);

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_subtract(other);

		base->assign(tmp);
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->QualifiedTypename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other->getReference())
		);

		VoidObject tmp;
		base->execute(&tmp, "operator-", params, 0);
	}
}

void operator_trinary_array(Object *base, Object *index, Object* other)
{
	if ( !base || !base->isValid() ) {
		throw Runtime::Exceptions::NullPointerException("null pointer access");
	}
	if ( !index || !index->isValid() ) {
		throw Runtime::Exceptions::NullPointerException("null pointer access");
	}
	if ( !other ) {
		throw Runtime::Exceptions::AccessViolation("cannot use null pointer: other");
	}

/*
	std::string source = base->Typename();
//	std::string subscript = index->Typename();
//	std::string target = other->Typename();
*/

	other->operator_array(index, base);
}

void operator_unary_decrement(Object *base)
{
	if ( !base || !base->isValid() ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_decrement();

		base->assign(tmp);
	}
	else {
		VoidObject tmp;
		base->execute(&tmp, "operator--", ParameterList(), 0);
	}
}

void operator_unary_increment(Object *base)
{
	if ( !base || !base->isValid() ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_unary_increment();

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_unary_increment();

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_unary_increment();

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_unary_increment();

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_unary_increment();

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_increment();

		base->assign(tmp);
	}
	else {
		VoidObject tmp;
		base->execute(&tmp, "operator++", ParameterList(), 0);
	}
}

void operator_unary_minus(Object *base)
{
	if ( !base || !base->isValid() ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_unary_minus();

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_unary_minus();

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_unary_minus();

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_unary_minus();

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_unary_minus();

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_minus();

		base->assign(tmp);
	}
	else {
		Object tmp;
		tmp.operator_unary_minus();

		base->assign(tmp);
	}
}

void operator_unary_not(Object *base)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());

		*base = BoolObject(!tmp.operator_bool());
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());

		*base = BoolObject(!tmp.operator_bool());
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());

		*base = BoolObject(!tmp.operator_bool());
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());

		*base = BoolObject(!tmp.operator_bool());
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());

		*base = BoolObject(!tmp.operator_bool());
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;

		*base = BoolObject(!tmp.operator_bool());
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(ANONYMOUS_OBJECT, BoolObject::TYPENAME, false, false, false, Parameter::AccessMode::ByValue)
		);

		MethodSymbol* value_op = base->resolveMethod("=operator", params, true, Visibility::Public);
		if ( value_op ) {
			Object tmp;

			Interpreter interpreter;
			interpreter.execute(dynamic_cast<Method*>(value_op), params, &tmp);

			*base = BoolObject(!tmp.isValid());
		}
		else {
			*base = BoolObject(!base->isValid());
		}
	}
}

void operator_unary_validate(Object *base)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access");
	}

	if ( !base->isValid() ) {
		throw ControlFlow::Throw;
	}

/*
	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		if ( !tmp.operator_bool() ) {
			throw ControlFlow::Throw;
		}
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		if ( !tmp.operator_bool() ) {
			throw ControlFlow::Throw;
		}
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		if ( !tmp.operator_bool() ) {
			throw ControlFlow::Throw;
		}
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		if ( !tmp.operator_bool() ) {
			throw ControlFlow::Throw;
		}
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		if ( !tmp.operator_bool() ) {
			throw ControlFlow::Throw;
		}
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		if ( !tmp.operator_bool() ) {
			throw ControlFlow::Throw;
		}
	}
	else {
		if ( !base->isValid() ) {
			throw ControlFlow::Throw;
		}
	}
*/
}


}
}
