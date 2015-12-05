
// Header
#include "BoolObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


Bool::Bool(const std::string& value)
: Object("", "SYSTEM.OS", "Bool", value)
{
	Constructor(ParameterList());
}

Bool::Bool(const Object& object)
: Object(object.name(), "SYSTEM.OS", "Bool", object.getValue())
{
}

bool Bool::isValid() const
{
	return Tools::stringToBool(Object::getValue());
}

void Bool::operator_assign(Object *other)
{
	Object::setValue(other->getValue());
}

void Bool::operator_divide(Object * /*other*/)
{
	throw Utils::NotImplemented("operator/");
}

void Bool::operator_multiply(Object * /*other*/)
{
	throw Utils::NotImplemented("operator*");
}

void Bool::operator_plus(Object * /*other*/)
{
	throw Utils::NotImplemented("operator+");
}

void Bool::operator_subtract(Object * /*other*/)
{
	throw Utils::NotImplemented("operator-");
}

std::string Bool::ToString() const
{
	return getValue();
}

void Bool::setValue(bool val)
{
	Object::setValue(Tools::toString(val));
}


}
