
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

void UserObject::operator_assign(Object * /*other*/)
{
	throw Utils::Exception("operator= not implemented");
}

void UserObject::operator_divide(Object * /*other*/)
{
	throw Utils::Exception("operator/ not implemented");
}

void UserObject::operator_multiply(Object * /*other*/)
{
	throw Utils::Exception("operator* not implemented");
}

void UserObject::operator_plus(Object * /*other*/)
{
	throw Utils::Exception("operator+ not implemented");
}

void UserObject::operator_subtract(Object * /*other*/)
{
	throw Utils::Exception("operator- not implemented");
}

std::string UserObject::ToString() const
{
	return getValue();
}

void UserObject::setValue(UserObject *val)
{
(void)val;
	assert(!"not implemented!");
}


}
