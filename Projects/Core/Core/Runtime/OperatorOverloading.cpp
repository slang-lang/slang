
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


void operator_binary_assign(Object* left, Object* right, const Common::Position& position)
{
	if ( !left || !right ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();
	std::string target = right->QualifiedTypename();

	if ( source == ANONYMOUS_OBJECT || source == target ) {
		// assign directly because our left has not yet been initialized
		// or no type conversion is necessary
		left->assign(*right);
	}
	else if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		tmp.operator_assign(right);

		left->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		tmp.operator_assign(right);

		left->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		tmp.operator_assign(right);

		left->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		tmp.operator_assign(right);

		left->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		tmp.operator_assign(right);

		left->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_assign(right);

		left->assign(tmp);
	}
/*
	// special handling for enumeration values
	else if ( left->isEnumerationValue() && right->isEnumerationValue() && source == target ) {
		left->setValue(right->getValue().toInt());
	}
*/
	// special handling for enumeration values
	else if ( left->isEnumerationValue() && right->QualifiedTypename() == _int ) {
		left->setValue(right->getValue().toInt());
	}
		// special handling for enumeration values
	else if ( left->QualifiedTypename() == _int && right->isEnumerationValue() ) {
		left->setValue( right->getValue().toInt() );
	}
	// no atomic data type, so we have to look if our assign operator has been overwritten
	else {
		if ( !right->isValid() ) {	// special handling for null object
			left->assign(*right);
			return;
		}

		if ( right->isInstanceOf(left->QualifiedTypename()) ) {
			left->assign(*right);
			return;
		}

		// invalid binary assignment operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + left->QualifiedTypename() + ".operator=(" + right->QualifiedTypename() + ")'");
	}
}

void operator_binary_bitand(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		tmp.operator_bitand(right);

		left->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		tmp.operator_bitand(right);

		left->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		tmp.operator_bitand(right);

		left->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		tmp.operator_bitand(right);

		left->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		tmp.operator_bitand(right);

		left->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitand(right);

		left->assign(tmp);
	}
	else {
		// invalid binary bitand operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + left->getFullScopeName() + ".operator&()'");
	}
}

void operator_binary_bitcomplement(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		tmp.operator_bitcomplement(right);

		left->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		tmp.operator_bitcomplement(right);

		left->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		tmp.operator_bitcomplement(right);

		left->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		tmp.operator_bitcomplement(right);

		left->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		tmp.operator_bitcomplement(right);

		left->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitcomplement(right);

		left->assign(tmp);
	}
	else {
		// invalid binary bitcomplement operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + left->getFullScopeName() + ".operator~()'");
	}
}

void operator_binary_bitor(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		tmp.operator_bitor(right);

		left->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		tmp.operator_bitor(right);

		left->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		tmp.operator_bitor(right);

		left->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		tmp.operator_bitor(right);

		left->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		tmp.operator_bitor(right);

		left->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitor(right);

		left->assign(tmp);
	}
	else {
		// invalid binary bitor operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + left->getFullScopeName() + ".operator|()'");
	}
}

void operator_binary_divide(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		tmp.operator_divide(right);

		left->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		tmp.operator_divide(right);

		left->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		tmp.operator_divide(right);

		left->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		tmp.operator_divide(right);

		left->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		tmp.operator_divide(right);

		left->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_divide(right);

		left->assign(tmp);
	}
	else {
		// invalid binary division operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + left->getFullScopeName() + ".operator/()'");
	}
}

bool operator_binary_equal(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot compare null pointer to object", position);
	}
	if ( !right ) {
		throw Runtime::Exceptions::AccessViolation("cannot compare object to null pointer", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		return tmp.operator_equal(right);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		return tmp.operator_equal(right);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		return tmp.operator_equal(right);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		return tmp.operator_equal(right);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		return tmp.operator_equal(right);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_equal(right);
	}
	else if (left->isEnumerationValue() && right->isEnumerationValue() && left->QualifiedTypename() == right->QualifiedTypename() ) {
		return left->getValue().toInt() == right->getValue().toInt();
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(right->QualifiedTypename(), right->getValue(), right->getReference()));

	if ( left->resolveMethod("operator==", params, false, Visibility::Public) ) {
		Object tmp;
		left->execute(&tmp, "operator==", params);
		return isTrue(tmp);
	}

	// no equality operator found, so we have to compare our references
	return left->operator_equal(right);
}

bool operator_binary_greater(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		return tmp.operator_greater(right);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		return tmp.operator_greater(right);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		return tmp.operator_greater(right);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		return tmp.operator_greater(right);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		return tmp.operator_greater(right);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_greater(right);
	}
	else if (left->isEnumerationValue() && right->isEnumerationValue() && left->QualifiedTypename() == right->QualifiedTypename() ) {
		return left->getValue().toInt() > right->getValue().toInt();
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(right->QualifiedTypename(), right->getValue(), right->getReference()));

	Object tmp;
	left->execute(&tmp, "operator>", params);
	return isTrue(tmp);
}

bool operator_binary_greater_equal(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		return tmp.operator_greater_equal(right);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		return tmp.operator_greater_equal(right);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		return tmp.operator_greater_equal(right);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		return tmp.operator_greater_equal(right);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		return tmp.operator_greater_equal(right);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_greater_equal(right);
	}
	else if (left->isEnumerationValue() && right->isEnumerationValue() && left->QualifiedTypename() == right->QualifiedTypename() ) {
		return left->getValue().toInt() >= right->getValue().toInt();
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(right->QualifiedTypename(), right->getValue(), right->getReference()));

	Object tmp;
	left->execute(&tmp, "operator>=", params);
	return isTrue(tmp);
}

bool operator_binary_less(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		return tmp.operator_less(right);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		return tmp.operator_less(right);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		return tmp.operator_less(right);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		return tmp.operator_less(right);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		return tmp.operator_less(right);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_less(right);
	}
	else if (left->isEnumerationValue() && right->isEnumerationValue() && left->QualifiedTypename() == right->QualifiedTypename() ) {
		return left->getValue().toInt() < right->getValue().toInt();
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(right->QualifiedTypename(), right->getValue(), right->getReference()));

	Object tmp;
	left->execute(&tmp, "operator<", params);
	return isTrue(tmp);
}

bool operator_binary_less_equal(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		return tmp.operator_less_equal(right);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		return tmp.operator_less_equal(right);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		return tmp.operator_less_equal(right);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		return tmp.operator_less_equal(right);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		return tmp.operator_less_equal(right);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		return tmp.operator_less_equal(right);
	}
	else if (left->isEnumerationValue() && right->isEnumerationValue() && left->QualifiedTypename() == right->QualifiedTypename() ) {
		return left->getValue().toInt() <= right->getValue().toInt();
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(right->QualifiedTypename(), right->getValue(), right->getReference()));

	Object tmp;
	left->execute(&tmp, "operator<=", params);
	return isTrue(tmp);
}

void operator_binary_modulo(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		tmp.operator_modulo(right);

		left->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		tmp.operator_modulo(right);

		left->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		tmp.operator_modulo(right);

		left->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		tmp.operator_modulo(right);

		left->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		tmp.operator_modulo(right);

		left->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_modulo(right);

		left->assign(tmp);
	}
	else {
		// invalid binary modulo operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + left->getFullScopeName() + ".operator%()'");
	}
}

void operator_binary_multiply(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		tmp.operator_multiply(right);

		left->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		tmp.operator_multiply(right);

		left->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		tmp.operator_multiply(right);

		left->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		tmp.operator_multiply(right);

		left->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		tmp.operator_multiply(right);

		left->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_multiply(right);

		left->assign(tmp);
	}
	else {
		// invalid binary multiply operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + left->getFullScopeName() + ".operator*()'");
	}
}

void operator_binary_plus(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		tmp.operator_plus(right);

		left->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		tmp.operator_plus(right);

		left->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		tmp.operator_plus(right);

		left->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		tmp.operator_plus(right);

		left->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		tmp.operator_plus(right);

		left->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_plus(right);

		left->assign(tmp);
	}
	else {
		// invalid binary addition operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + left->getFullScopeName() + ".operator+()'");
	}
}

void operator_binary_subtract(Object* left, Object* right, const Common::Position& position)
{
	if ( !left ) {
		throw Runtime::Exceptions::AccessViolation("cannot add null pointer to object", position);
	}

	std::string source = left->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(left->isValid());
		tmp.operator_subtract(right);

		left->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(left->getValue());
		tmp.operator_subtract(right);

		left->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(left->getValue());
		tmp.operator_subtract(right);

		left->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(left->getValue());
		tmp.operator_subtract(right);

		left->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(left->getValue());
		tmp.operator_subtract(right);

		left->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_subtract(right);

		left->assign(tmp);
	}
	else {
		// invalid binary subtract operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + left->getFullScopeName() + ".operator-()'");
	}
}

void operator_unary_decrement(Object* base, const Common::Position& position)
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
		// invalid decrement operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + base->getFullScopeName() + ".operator--()'");
	}
}

void operator_unary_increment(Object* base, const Common::Position& position)
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
		// invalid increment operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + base->getFullScopeName() + ".operator++()'");
	}
}

void operator_unary_minus(Object* base, const Common::Position& position)
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
		// invalid unary minus operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + base->getFullScopeName() + ".-operator()'");
	}
}

void operator_unary_plus(Object* base, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access", position);
	}

	std::string source = base->QualifiedTypename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->isValid());
		tmp.operator_unary_plus();

		base->assign(tmp);
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_unary_plus();

		base->assign(tmp);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_unary_plus();

		base->assign(tmp);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_unary_plus();

		base->assign(tmp);
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_unary_plus();

		base->assign(tmp);
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_plus();

		base->assign(tmp);
	}
	else {
		// invalid unary plus operator handling!
		throw Runtime::Exceptions::InvalidOperation("'" + base->getFullScopeName() + ".+operator()'");
	}
}

void operator_unary_not(Object* base, const Common::Position& position)
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

void operator_unary_validate(Object* base, const Common::Position& position)
{
	if ( !base ) {
		throw Runtime::Exceptions::AccessViolation("null pointer access", position);
	}

	if ( !base->isValid() ) {
		throw ControlFlow::Throw;
	}
}


}
}
