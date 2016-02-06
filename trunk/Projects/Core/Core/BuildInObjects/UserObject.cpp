
// Header
#include "UserObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "BoolObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


std::string UserObject::DEFAULTVALUE = "";
std::string UserObject::TYPENAME = "UserObject";


UserObject::UserObject(const std::string& name, const std::string& filename, const std::string& type, const std::string& value)
: Object(name, filename, type, value)
{
	mIsAtomicType = false;

	//setValue(value);
}

UserObject::UserObject(const Object& object)
: Object(object.getName(), object.Filename(), object.Typename(), "")
{
	mIsAtomicType = false;

	setValue(object.getValue());
}

UserObject::operator bool()
{
	ParameterList params;
	// empty parameter list

	BoolObject tmp;
	this->execute(&tmp, "operator_bool", params, 0);
	return tmp;
}

const std::string& UserObject::getTypeName() const
{
	return TYPENAME;
}

void UserObject::operator_assign(Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator=", params, 0);
}

void UserObject::operator_divide(Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator/", params, 0);
}

bool UserObject::operator_equal(Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->getName(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator==", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_greater(Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->getName(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator>", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_greater_equal(Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->getName(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator>=", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_less(Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->getName(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator<", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_less_equal(Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->getName(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator<=", params, 0);

	return tmp.isValid();
}

void UserObject::operator_multiply(Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator*", params, 0);
}

void UserObject::operator_plus(Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator+", params, 0);
}

void UserObject::operator_subtract(Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator-", params, 0);
}

std::string UserObject::ToString() const
{
	return Typename() + " " + getName();// + " = " + getValue();
}


}
}
