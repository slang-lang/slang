
// Header
#include "Bool.h"

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

void Bool::operator_assign(Object *other)
{
	value(other->value());
}

void Bool::operator_divide(Object * /*other*/)
{
	throw Utils::Exception("operator/ not implemented");
}

void Bool::operator_multiply(Object * /*other*/)
{
	throw Utils::Exception("operator* not implemented");
}

void Bool::operator_plus(Object * /*other*/)
{
	throw Utils::Exception("operator+ not implemented");
}

void Bool::operator_subtract(Object * /*other*/)
{
	throw Utils::Exception("operator- not implemented");
}

std::string Bool::ToString() const
{
	return value();
}


}
