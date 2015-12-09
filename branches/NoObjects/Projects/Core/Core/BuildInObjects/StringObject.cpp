
// Header
#include "StringObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


String::String(const std::string& value)
: Object("", "SYSTEM.OS", "String", value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

String::String(const Object& object)
: Object(object.name(), "SYSTEM.OS", "String", object.getValue())
{
}

void String::operator_assign(Object *other)
{
	Object::setValue(other->getValue());
}

void String::operator_divide(Object * /*other*/)
{
	throw Utils::NotImplemented("operator/");
}

void String::operator_multiply(Object * /*other*/)
{
	throw Utils::NotImplemented("operator*");
}

void String::operator_plus(Object *other)
{
	setValue(getValue() + other->getValue());
}

void String::operator_subtract(Object * /*other*/)
{
	throw Utils::NotImplemented("operator-");
}

std::string String::ToString() const
{
	return getValue();
}


}
