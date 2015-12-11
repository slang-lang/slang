
// Header
#include "StringObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


String::String(const std::string& value)
: Object("", "SYSTEM.OS", "String", value),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

String::String(const Object& object)
: Object(object.getName(), "SYSTEM.OS", "String", object.getValue()),
  mValue(object.getValue())
{
}

String::operator bool() const
{
	return !getValue().empty();
}

std::string String::getNativeValue() const
{
	return mValue;
}

std::string String::getValue() const
{
	return mValue;
}

void String::operator_assign(Object *other)
{
	mValue = other->getValue();
}

bool String::operator_equal(Object *other)
{
	return (this->getValue() == other->getValue());
}

void String::operator_plus(Object *other)
{
	mValue = getValue() + other->getValue();
}

void String::setNativeValue(const std::string& value)
{
	mValue = value;
}

void String::setValue(const std::string& value)
{
	mValue = value;
}

std::string String::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
