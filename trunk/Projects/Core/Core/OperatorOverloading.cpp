
// Header
#include "OperatorOverloading.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Utils/Exceptions.h>
#include "Object.h"

// Namespace declarations


namespace ObjectiveScript {


void operator_assign(Object *base, Object *other)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot assign value to null pointer");
	}
	if ( !other ) {
		throw Utils::Exceptions::NullPointer("cannot assign object to null pointer");
	}

	std::string source = base->Typename();

	if ( source == "<unknown type>" ) {
		// assign directly because our base has not yet been initialized
		*base = *other;
	}
	else if ( source == BoolObject::TYPENAME ) {
		BoolObject tmp(base->getValue());
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
		ParameterList params;
		params.push_back(
			Parameter(other->getName(), other->Typename(), other->getValue(), false, other->isConst(), Parameter::AccessMode::ByReference, other)
		);

		BoolObject tmp;
		base->execute(&tmp, "operator_assign", params, 0);
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
		BoolObject tmp(base->getValue());
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

		BoolObject tmp;
		base->execute(&tmp, "operator_divide", params, 0);
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
		BoolObject tmp(base->getValue());
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

	BoolObject tmp;
	base->execute(&tmp, "operator_equal", params, 0);
	return tmp;
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
		BoolObject tmp(base->getValue());
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

	BoolObject tmp;
	base->execute(&tmp, "operator_greater", params, 0);
	return tmp;
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
		BoolObject tmp(base->getValue());
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

	BoolObject tmp;
	base->execute(&tmp, "operator_greater_equal", params, 0);
	return tmp;
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
		BoolObject tmp(base->getValue());
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

	BoolObject tmp;
	base->execute(&tmp, "operator_less", params, 0);
	return tmp;
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
		BoolObject tmp(base->getValue());
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

	BoolObject tmp;
	base->execute(&tmp, "operator_less_equal", params, 0);
	return tmp;
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
		BoolObject tmp(base->getValue());
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

		BoolObject tmp;
		base->execute(&tmp, "operator_multiply", params, 0);
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
		BoolObject tmp(base->getValue());
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

		BoolObject tmp;
		base->execute(&tmp, "operator_plus", params, 0);
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
		BoolObject tmp(base->getValue());
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

		BoolObject tmp;
		base->execute(&tmp, "operator_subtract", params, 0);
	}
}


}
