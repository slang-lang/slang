
// Header
#include "Number.h"

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
}

void Number::operator_assign(Object *other)
{
	value(other->value());
}

void Number::operator_divide(Object *other)
{
	float f = Tools::stringToFloat(value());
	f /= Tools::stringToFloat(other->value());

	value(Tools::toString(f));
}

void Number::operator_multiply(Object *other)
{
	float f = Tools::stringToFloat(value());
	f *= Tools::stringToFloat(other->value());

	value(Tools::toString(f));
}

void Number::operator_plus(Object *other)
{
	float f = Tools::stringToFloat(value());
	f += Tools::stringToFloat(other->value());

	value(Tools::toString(f));
}

void Number::operator_subtract(Object *other)
{
	float f = Tools::stringToFloat(value());
	f -= Tools::stringToFloat(other->value());

	value(Tools::toString(f));
}

std::string Number::ToString() const
{
	return value();
}


}
