
// Header
#include "OperatorOverloading.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/EnumerationObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Common/Method.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


void operator_binary_assign(Object *base, Object *other, const Common::Position& position)
{
	if ( !base || !other ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();
	std::string target = other->QualifiedTypename();

	if ( source == ANONYMOUS_OBJECT || source == target ) {
		// assign directly because our base has not yet been initialized
		// or no type conversion is necessary
		base->assign(*other);
	}
	else if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
/*
	// special handling for enumeration values
	else if ( base->isEnumerationValue() && other->isEnumerationValue() && source == target ) {
		base->setValue(other->getValue().toInt());
	}
*/
	// no atomic data type, so we have to look if our assign operator has been overwritten
	else {
		if ( !other->isValid() ) {	// special handling for null object
			base->assign(*other);
			return;
		}

		if ( other->isInstanceOf(base->QualifiedTypename()) ) {
			base->assign(*other);
			return;
		}

		{
			ParameterList params;
			params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

			::ObjectiveScript::MethodSymbol* operator_method = base->resolveMethod("operator=", params, true, Visibility::Private);
			if ( operator_method ) {
				Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(operator_method), params, 0);

				return;
			}
		}

		ParameterList params;
		params.push_back(Parameter::CreateRuntime(base->QualifiedTypename(), base->getValue(), base->getReference()));

		::ObjectiveScript::MethodSymbol* operator_method = other->resolveMethod("=operator", params, true, Visibility::Public);
		if ( operator_method ) {
			Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(operator_method), params, base);

			return;
		}

		throw Common::Exceptions::Exception(base->QualifiedTypename() + ".operator=: conversion from " + other->QualifiedTypename() + " to " + base->QualifiedTypename() + " not supported");
	}
}

void operator_binary_bitand(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
		params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

		VoidObject tmp;
		base->execute(&tmp, "operator&", params);
	}
}

void operator_binary_bitcomplement(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
		params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

		VoidObject tmp;
		base->execute(&tmp, "operator~", params);
	}
}

void operator_binary_bitor(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
		params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

		VoidObject tmp;
		base->execute(&tmp, "operator|", params);
	}
}

void operator_binary_divide(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
		params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

		VoidObject tmp;
		base->execute(&tmp, "operator/", params);
	}
}

bool operator_binary_equal(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot compare null pointer to object", position);
	}
	if ( !other ) {
		throw Runtime::Exceptions::AccessViolation("cannot compare object to null pointer", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
	else if ( base->isEnumerationValue() && other->isEnumerationValue() && base->QualifiedTypename() == other->QualifiedTypename() ) {
		return base->getValue().toInt() == other->getValue().toInt();
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

	if ( base->resolveMethod("operator==", params, false, Visibility::Public) ) {
		Object tmp;
		base->execute(&tmp, "operator==", params);
		return isTrue(tmp);
	}

	params.clear();
	params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

	if ( base->resolveMethod("operator==", params, false, Visibility::Public) ) {
		Object tmp;
		base->execute(&tmp, "operator==", params);
		return isTrue(tmp);
	}

	// no equality operator found, so we have to compare our references
	return base->operator_equal(other);
}

bool operator_binary_greater(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
	else if ( base->isEnumerationValue() && other->isEnumerationValue() && base->QualifiedTypename() == other->QualifiedTypename() ) {
		return base->getValue().toInt() > other->getValue().toInt();
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

	Object tmp;
	base->execute(&tmp, "operator>", params);
	return isTrue(tmp);
}

bool operator_binary_greater_equal(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
	else if ( base->isEnumerationValue() && other->isEnumerationValue() && base->QualifiedTypename() == other->QualifiedTypename() ) {
		return base->getValue().toInt() >= other->getValue().toInt();
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

	Object tmp;
	base->execute(&tmp, "operator>=", params);
	return isTrue(tmp);
}

bool operator_binary_less(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
	else if ( base->isEnumerationValue() && other->isEnumerationValue() && base->QualifiedTypename() == other->QualifiedTypename() ) {
		return base->getValue().toInt() < other->getValue().toInt();
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

	Object tmp;
	base->execute(&tmp, "operator<", params);
	return isTrue(tmp);
}

bool operator_binary_less_equal(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
	else if ( base->isEnumerationValue() && other->isEnumerationValue() && base->QualifiedTypename() == other->QualifiedTypename() ) {
		return base->getValue().toInt() <= other->getValue().toInt();
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

	Object tmp;
	base->execute(&tmp, "operator<=", params);
	return isTrue(tmp);
}

bool operator_binary_is(Object* base, const std::string& type, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	return base->operator_is(type);
}

void operator_binary_modulo(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
		params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

		VoidObject tmp;
		base->execute(&tmp, "operator%", params);
	}
}

void operator_binary_multiply(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
		params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

		VoidObject tmp;
		base->execute(&tmp, "operator*", params);
	}
}

void operator_binary_plus(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
		params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

		VoidObject tmp;
		base->execute(&tmp, "operator+", params);
	}
}

void operator_binary_subtract(Object *base, Object *other, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
		params.push_back(Parameter::CreateRuntime(other->QualifiedTypename(), other->getValue(), other->getReference()));

		VoidObject tmp;
		base->execute(&tmp, "operator-", params);
	}
}

void operator_unary_decrement(Object *base, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
		base->execute(&tmp, "operator--", ParameterList());
	}
}

void operator_unary_increment(Object *base, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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
		base->execute(&tmp, "operator++", ParameterList());
	}
}

void operator_unary_minus(Object *base, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
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

void operator_unary_not(Object *base, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());

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
		*base = BoolObject(!base->isValid());
	}
}

void operator_unary_validate(Object *base, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access", position);
	}

	if ( !base->isValid() ) {
		Controller::Instance().stack()->exception() = Runtime::ExceptionData(new StringObject(std::string("validation failed")), position);

		throw ControlFlow::Throw;
	}
}


}
}
