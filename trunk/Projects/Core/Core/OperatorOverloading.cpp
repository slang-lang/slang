
// Header
#include "OperatorOverloading.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Utils/Exceptions.h>
#include "Consts.h"
#include "Object.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


void operator_assign(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot assign value to null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot assign object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == ANONYMOUS_OBJECT ) {
		// assign directly because our base has not yet been initialized
		*base = *other;
	}
	else if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_assign(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_assign(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_assign(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

		Object tmp;
		base->execute(&tmp, "operator=", params, 0);
	}
}

void operator_bitand(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot bitand value to null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot bitand object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_bitand(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_bitand(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_bitand(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

		Object tmp;
		base->execute(&tmp, "operator&", params, 0);
	}
}

void operator_bitcomplement(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot bitcomplement value to null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot bitcomplement object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_bitcomplement(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_bitcomplement(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_bitcomplement(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

		Object tmp;
		base->execute(&tmp, "operator~", params, 0);
	}
}

void operator_bitor(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot bitor value to null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot bitor object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_bitor(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_bitor(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_bitor(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

		Object tmp;
		base->execute(&tmp, "operator|", params, 0);
	}
}

void operator_divide(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("operator_divide: cannot divide null pointer through object");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot divide object through null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_divide(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_divide(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_divide(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

		Object tmp;
		base->execute(&tmp, "operator/", params, 0);
	}
}

bool operator_equal(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot compare object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		return tmp.operator_equal(other);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		return tmp.operator_equal(other);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		return tmp.operator_equal(other);
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

	Object tmp;
	base->execute(&tmp, "operator==", params, 0);
	return isTrue(tmp);
}

bool operator_greater(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot compare object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		return tmp.operator_greater(other);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		return tmp.operator_greater(other);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		return tmp.operator_greater(other);
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

bool operator_greater_equal(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot compare object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		return tmp.operator_greater_equal(other);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		return tmp.operator_greater_equal(other);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		return tmp.operator_greater_equal(other);
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

bool operator_less(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot compare object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		return tmp.operator_less(other);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		return tmp.operator_less(other);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		return tmp.operator_less(other);
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

bool operator_less_equal(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot compare null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot compare object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		return tmp.operator_less_equal(other);
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		return tmp.operator_less_equal(other);
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		return tmp.operator_less_equal(other);
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

void operator_modulo(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot modulo null pointer by object");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot modulo object by null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_modulo(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_modulo(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_modulo(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

		Object tmp;
		base->execute(&tmp, "operator%", params, 0);
	}
}

void operator_multiply(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot multiply null pointer by object");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot multiply object by null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_multiply(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_multiply(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_multiply(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

		Object tmp;
		base->execute(&tmp, "operator*", params, 0);
	}
}

void operator_plus(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot add null pointer to object");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot add object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_plus(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_plus(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_plus(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

		Object tmp;
		base->execute(&tmp, "operator+", params, 0);
	}
}

void operator_subtract(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot subtract object from null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot subtract null pointer from object");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_subtract(other);

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_subtract(other);

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_subtract(other);

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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

		Object tmp;
		base->execute(&tmp, "operator-", params, 0);
	}
}

void operator_unary_decrement(Object *base)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot subtract object from null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_unary_decrement();

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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
		Object tmp;
		base->execute(&tmp, "operator--", ParameterList(), 0);
	}
}

void operator_unary_increment(Object *base)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot subtract object from null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_unary_increment();

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
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
		Object tmp;
		base->execute(&tmp, "operator++", ParameterList(), 0);
	}
}

void operator_unary_not(Object *base)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot subtract object from null pointer");
	}

	std::string source = base->Typename();

	if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(base->getValue()));
		tmp.operator_unary_not();

		*base = tmp;
	}
	else if ( source == FloatObject::TYPENAME ) {
		FloatObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_unary_not();

		*base = tmp;
	}
	else if ( source == IntegerObject::TYPENAME ) {
		IntegerObject tmp(Tools::stringToInt(base->getValue()));
		tmp.operator_unary_not();

		*base = tmp;
	}
	else if ( source == NumberObject::TYPENAME ) {
		NumberObject tmp(Tools::stringToFloat(base->getValue()));
		tmp.operator_unary_not();

		*base = tmp;
	}
	else if ( source == StringObject::TYPENAME ) {
		StringObject tmp(base->getValue());
		tmp.operator_unary_not();

		*base = tmp;
	}
	else if ( source == VoidObject::TYPENAME ) {
		VoidObject tmp;
		tmp.operator_unary_not();

		*base = tmp;
	}
	else {
		Object tmp;
		base->execute(&tmp, "operator!", ParameterList(), 0);
	}
}


}
}
