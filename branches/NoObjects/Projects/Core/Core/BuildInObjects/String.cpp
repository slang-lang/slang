
// Header
#include "String.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


String::String(const std::string& value)
: Object("", "SYSTEM.OS", "String", value)
{
	Constructor(ParameterList());
}

void String::operator_assign(Object *other)
{
	value(other->value());
}

void String::operator_divide(Object * /*other*/)
{
	throw Utils::Exception("operator/ not implemented");
}

void String::operator_multiply(Object * /*other*/)
{
	throw Utils::Exception("operator* not implemented");
}

void String::operator_plus(Object *other)
{
	value(value() + other->value());
}

void String::operator_subtract(Object * /*other*/)
{
	throw Utils::Exception("operator- not implemented");
}

std::string String::ToString() const
{
	return value();
}


}
