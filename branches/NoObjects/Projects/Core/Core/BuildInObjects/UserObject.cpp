
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

void UserObject::operator_assign(Object * /*other*/)
{
	throw Utils::NotImplemented("operator=");
}

void UserObject::operator_divide(Object * /*other*/)
{
	throw Utils::NotImplemented("operator/");
}

void UserObject::operator_multiply(Object * /*other*/)
{
	throw Utils::NotImplemented("operator*");
}

void UserObject::operator_plus(Object * /*other*/)
{
	throw Utils::NotImplemented("operator+");
}

void UserObject::operator_subtract(Object * /*other*/)
{
	throw Utils::NotImplemented("operator-");
}

std::string UserObject::ToString() const
{
	return getValue();
}

void UserObject::setValue(UserObject * /*val*/)
{
	throw Utils::NotImplemented("setValue");
}


}
