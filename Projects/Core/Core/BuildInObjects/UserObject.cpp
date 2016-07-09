
// Header
#include "UserObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


std::string UserObject::DEFAULTVALUE = VALUE_NONE;
std::string UserObject::TYPENAME = "UserObject";


UserObject::UserObject()
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, VALUE_NONE)
{
	mIsAtomicType = false;
	mIsConstructed = false;
}

UserObject::UserObject(const std::string& name, const std::string& filename, const std::string& type)
: Object(name, filename, type, 0)
{
	mIsAtomicType = false;
	mIsConstructed = false;
}

UserObject::UserObject(const Object& object)
: Object(object.getName(), object.Filename(), object.Typename(), object.getValue())
{
	mIsAtomicType = false;
	mIsConstructed = false;
}

void UserObject::operator_assign(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator=", params, 0);
}

bool UserObject::operator_bool() const
{
	return isValid();
}

void UserObject::operator_divide(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator/", params, 0);
}

bool UserObject::operator_equal(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->getName(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator==", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_greater(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->getName(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator>", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_greater_equal(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->getName(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator>=", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_less(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->getName(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator<", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_less_equal(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter(other->getName(), other->Typename(), other->getValue()));

	Object tmp;
	this->execute(&tmp, "operator<=", params, 0);

	return tmp.isValid();
}

void UserObject::operator_multiply(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator*", params, 0);
}

void UserObject::operator_plus(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator+", params, 0);
}

void UserObject::operator_subtract(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(other->getName(), other->Typename(), other->getValue())
	);

	Object tmp;
	this->execute(&tmp, "operator-", params, 0);
}


}
}
