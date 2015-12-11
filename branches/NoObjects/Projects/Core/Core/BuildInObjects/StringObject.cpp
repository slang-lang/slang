
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
: Object(object.getName(), "SYSTEM.OS", "String", object.getValue())
{
}

String::operator bool() const
{
	return !getValue().empty();
}

void String::operator_assign(Object *other)
{
	setValue(other->getValue());
}

bool String::operator_equal(Object *other)
{
	return (this->getValue() == other->getValue());
}

void String::operator_plus(Object *other)
{
	setValue(getValue() + other->getValue());
}

std::string String::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
