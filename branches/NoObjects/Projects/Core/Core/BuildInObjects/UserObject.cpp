
// Header
#include "UserObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


UserObject::UserObject(const std::string& name, const std::string& filename, const std::string& type, const std::string& value)
: Object(name, filename, type, value)
{
}

UserObject::UserObject(const Object& object)
: Object(object.name(), object.Filename(), object.Typename(), object.getValue())
{
}

void UserObject::operator_assign(Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->name(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator_assign", params, 0);
}

void UserObject::operator_divide(Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->name(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator_divide", params, 0);
}

bool UserObject::operator_equal(Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->name(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator_equal", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_greater(Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->name(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator_greater", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_greater_equal(Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->name(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator_greater_equal", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_less(Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->name(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator_less", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_less_equal(Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->name(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator_less_equal", params, 0);

	return tmp.isValid();
}

void UserObject::operator_multiply(Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->name(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator_multiply", params, 0);
}

void UserObject::operator_plus(Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->name(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator_plus", params, 0);
}

void UserObject::operator_subtract(Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->name(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator_subtract", params, 0);
}

std::string UserObject::ToString() const
{
	return Typename() + " " + name() + " = " + getValue();
}


}
