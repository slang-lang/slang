
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
	Constructor(ParameterList());

	mValue = Tools::stringToFloat(value);
}

void Number::operator_assign(Object *other)
{
	Object::setValue(other->getValue());
}

void Number::operator_divide(Object *other)
{
	float f = Tools::stringToFloat(getValue());
	f /= Tools::stringToFloat(other->getValue());

	setValue(f);
}

void Number::operator_multiply(Object *other)
{
	float f = Tools::stringToFloat(getValue());
	f *= Tools::stringToFloat(other->getValue());

	setValue(f);
}

void Number::operator_plus(Object *other)
{
	float f = Tools::stringToFloat(getValue());
	f += Tools::stringToFloat(other->getValue());

	setValue(f);
}

void Number::operator_subtract(Object *other)
{
	float f = Tools::stringToFloat(getValue());
	f -= Tools::stringToFloat(other->getValue());

	setValue(f);
}

std::string Number::ToString() const
{
	return getValue();
}

void Number::setValue(float val)
{
	Object::setValue(Tools::toString(val));
}


}
