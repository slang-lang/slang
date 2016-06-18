
// Header
#include "OperatorOverloading.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Consts.h>
#include <Core/Symbol.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


void operator_binary_assign(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot assign value to null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot assign object to null pointer");
	}

	std::string source = base->Typename();
	std::string target = other->Typename();

	if ( !base->isValid() || source == target ) {
		// assign directly because our base has not yet been initialized
		// or no type conversion is necessary
		*base = *other;
	}
	else if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_assign(other);

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_assign(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_assign(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_assign(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_assign(other);

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_assign(other);

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_assign(other);

		*base = tmp;
	}
	else {
		// no atomic data type, so we have to look if our assign operator has been overwritten
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
		);

		VoidObject tmp;
		base->execute(&tmp, "operator=", params, 0);
	}
}

void operator_binary_bitand(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot bitand value to null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot bitand object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_bitand(other);

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_bitand(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_bitand(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_bitand(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_bitand(other);

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_bitand(other);

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitand(other);

		*base = tmp;
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
		);

		VoidObject tmp;
		base->execute(&tmp, "operator&", params, 0);
	}
}

void operator_binary_bitcomplement(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot bitcomplement value to null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot bitcomplement object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_bitcomplement(other);

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitcomplement(other);

		*base = tmp;
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
		);

		VoidObject tmp;
		base->execute(&tmp, "operator~", params, 0);
	}
}

void operator_binary_bitor(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot bitor value to null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot bitor object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_bitor(other);

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_bitor(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_bitor(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_bitor(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_bitor(other);

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_bitor(other);

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_bitor(other);

		*base = tmp;
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
		);

		VoidObject tmp;
		base->execute(&tmp, "operator|", params, 0);
	}
}

void operator_binary_divide(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("operator_binary_divide: cannot divide null pointer through object");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot divide object through null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_divide(other);

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_divide(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_divide(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_divide(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_divide(other);

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_divide(other);

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_divide(other);

		*base = tmp;
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
		);

		VoidObject tmp;
		base->execute(&tmp, "operator/", params, 0);
	}
}

bool operator_binary_equal(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot compare object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
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
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
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
		Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
	);

	//std::cout << "operator=(" << toString(params) << ")" << std::endl;

	if ( base->resolveMethod("operator==", params, false) ) {
		Object tmp;
		base->execute(&tmp, "operator==", params, 0);
		return isTrue(tmp);
	}

	// no equality operator found, so we have to compare our references
	return base == other;
}

bool operator_binary_greater(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot compare object to null pointer");
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
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
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
		Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
	);

	Object tmp;
	base->execute(&tmp, "operator>", params, 0);
	return isTrue(tmp);
}

bool operator_binary_greater_equal(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot compare object to null pointer");
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
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
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
		Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
	);

	Object tmp;
	base->execute(&tmp, "operator>=", params, 0);
	return isTrue(tmp);
}

bool operator_binary_less(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot compare object to null pointer");
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
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
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
		Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
	);

	Object tmp;
	base->execute(&tmp, "operator<", params, 0);
	return isTrue(tmp);
}

bool operator_binary_less_equal(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot compare object to null pointer");
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
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
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
		Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
	);

	Object tmp;
	base->execute(&tmp, "operator<=", params, 0);
	return isTrue(tmp);
}

void operator_binary_modulo(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot modulo null pointer by object");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot modulo object by null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_modulo(other);

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_modulo(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_modulo(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_modulo(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_modulo(other);

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_modulo(other);

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_modulo(other);

		*base = tmp;
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
		);

		VoidObject tmp;
		base->execute(&tmp, "operator%", params, 0);
	}
}

void operator_binary_multiply(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot multiply null pointer by object");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot multiply object by null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_multiply(other);

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_multiply(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_multiply(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_multiply(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_multiply(other);

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_multiply(other);

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_multiply(other);

		*base = tmp;
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
		);

		VoidObject tmp;
		base->execute(&tmp, "operator*", params, 0);
	}
}

void operator_binary_plus(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot add null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot add object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_plus(other);

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_plus(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_plus(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_plus(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_plus(other);

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_plus(other);

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_plus(other);

		*base = tmp;
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
		);

		VoidObject tmp;
		base->execute(&tmp, "operator+", params, 0);
	}
}

void operator_binary_subtract(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot subtract object from null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::AccessViolation("cannot subtract null pointer from object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_subtract(other);

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_subtract(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_subtract(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_subtract(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_subtract(other);

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_subtract(other);

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_subtract(other);

		*base = tmp;
	}
	else {
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
		);

		VoidObject tmp;
		base->execute(&tmp, "operator-", params, 0);
	}
}

void operator_unary_infix_decrement(Object *base)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot decrement null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else {
		VoidObject tmp;
		base->execute(&tmp, "--operator", ParameterList(), 0);
	}
}

void operator_unary_infix_increment(Object *base)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot increment null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else {
		VoidObject tmp;
		base->execute(&tmp, "++operator", ParameterList(), 0);
	}
}

void operator_unary_minus(Object *base)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("null pointer access");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_unary_minus();

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_unary_minus();

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_unary_minus();

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_unary_minus();

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_unary_minus();

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_unary_minus();

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_minus();

		*base = tmp;
	}
	else {
		Object tmp;
		tmp.operator_unary_minus();

		*base = tmp;
	}
}

void operator_unary_not(Object *base)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("null pointer access");
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
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());

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
		MethodSymbol *op_not = base->resolveMethod("operator!", ParameterList(), true);
		if ( op_not ) {
			Object tmp;
			static_cast<Method*>(op_not)->execute(ParameterList(), &tmp, Token());

			operator_binary_assign(base, &tmp);
		}
		else {
			*base = BoolObject(!base->isValid());
		}
	}
}

void operator_unary_postfix_decrement(Object *base)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot decrement null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else {
		VoidObject tmp;
		base->execute(&tmp, "operator--", ParameterList(), 0);
	}
}

void operator_unary_postfix_increment(Object *base)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("cannot increment null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == DoubleObject::TYPENAME ) {
		DoubleObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else {
		VoidObject tmp;
		base->execute(&tmp, "operator++", ParameterList(), 0);
	}
}

void operator_unary_validate(Object *base)
{
	if ( !base ) {
		throw Utils::Exceptions::AccessViolation("null pointer access");
	}

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
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(base->getValue());
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
}


}
}
