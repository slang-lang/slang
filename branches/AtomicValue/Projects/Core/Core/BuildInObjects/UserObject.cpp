
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

	//setValue(VALUE_NONE);
}

UserObject::UserObject(const std::string& name, const std::string& filename, const std::string& type, AtomicValue value)
: Object(name, filename, type, value)
{
	mIsAtomicType = false;
	mIsConstructed = false;

	//setValue(value);
}

UserObject::UserObject(const Object& object)
: Object(object.getName(), object.Filename(), object.Typename(), VALUE_NONE)
{
	mIsAtomicType = false;
	mIsConstructed = false;

	setValue(object.getValue());
}

bool UserObject::operator_bool() const
{
	return isValid();
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


}
}
