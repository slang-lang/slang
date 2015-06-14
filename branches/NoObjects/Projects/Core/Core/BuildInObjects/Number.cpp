
// Header
#include "Number.h"

// Library includes

// Project includes
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Number::Number(const std::string& value = "0")
: Object("", "SYSTEM.OS", "Number", value)
{
	Constructor(ParameterList());
}

void Number::operator_assign(Object *other)
{
	mValue = other->value();
}

void Number::operator_divide(Object *other)
{
	float value = Tools::stringToFloat(mValue);
	value /= Tools::stringToFloat(other->value());

	mValue = Tools::toString(value);
}

void Number::operator_multiply(Object *other)
{
	float value = Tools::stringToFloat(mValue);
	value *= Tools::stringToFloat(other->value());

	mValue = Tools::toString(value);
}

void Number::operator_plus(Object *other)
{
	float value = Tools::stringToFloat(mValue);
	value += Tools::stringToFloat(other->value());

	mValue = Tools::toString(value);
}

void Number::operator_subtract(Object *other)
{
	float value = Tools::stringToFloat(mValue);
	value -= Tools::stringToFloat(other->value());

	mValue = Tools::toString(value);
}

std::string Number::ToString() const
{
	return mValue;
}


}
