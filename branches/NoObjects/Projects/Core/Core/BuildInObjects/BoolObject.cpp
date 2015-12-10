
// Header
#include "BoolObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


Bool::Bool(bool value)
: Object("", "SYSTEM.OS", "Bool", ""),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

Bool::Bool(const std::string& value)
: Object("", "SYSTEM.OS", "Bool", value),
  mValue(Tools::stringToBool(value))
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

Bool::Bool(const Object& object)
: Object(object.name(), "SYSTEM.OS", "Bool", object.getValue()),
  mValue(Tools::stringToFloat(object.getValue()))
{
}

std::string Bool::getValue() const
{
	return Tools::toString(mValue);
}

bool Bool::isValid() const
{
	return true;
}

void Bool::operator_assign(Object *other)
{
	mValue = Tools::stringToBool(other->getValue());

	Object::setValue(other->getValue());
}

bool Bool::operator_equal(Object *other)
{
	return (mValue == Tools::stringToBool(other->getValue()));
}

std::string Bool::ToString() const
{
	return Typename() + " " + name() + " = " + getValue();
}


}
