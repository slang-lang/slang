
// Header
#include "NumberObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


Number::Number(const std::string& value)
: Object("", "SYSTEM.OS", "Number", value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

Number::Number(const Object& object)
: Object(object.name(), "SYSTEM.OS", "Number", object.getValue())
{
}

bool Number::isValid() const
{
	return Tools::stringToFloat(Object::getValue()) != 0.f;
}

void Number::operator_assign(Object *other)
{
	Object::setValue(other->getValue());
}

void Number::operator_divide(Object *other)
{
	float f = Tools::stringToFloat(getValue());
	f /= Tools::stringToFloat(other->getValue());

	Object::setValue(Tools::toString(f));
}

void Number::operator_multiply(Object *other)
{
	float f = Tools::stringToFloat(getValue());
	f *= Tools::stringToFloat(other->getValue());

	Object::setValue(Tools::toString(f));
}

void Number::operator_plus(Object *other)
{
	float f = Tools::stringToFloat(getValue());
	f += Tools::stringToFloat(other->getValue());

	Object::setValue(Tools::toString(f));
}

void Number::operator_subtract(Object *other)
{
	float f = Tools::stringToFloat(getValue());
	f -= Tools::stringToFloat(other->getValue());

	Object::setValue(Tools::toString(f));
}

std::string Number::ToString() const
{
	return getValue();
}


}
