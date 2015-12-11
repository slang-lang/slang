
// Header
#include "NumberObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


Number::Number(float value)
: Object("", "SYSTEM.OS", "Number", ""),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

Number::Number(const std::string& value)
: Object("", "SYSTEM.OS", "Number", value),
  mValue(Tools::stringToFloat(value))
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

Number::Number(const Object& object)
: Object(object.getName(), "SYSTEM.OS", "Number", object.getValue()),
  mValue(0.f)
{
}

Number::operator bool() const
{
	return mValue != 0.f;
}

std::string Number::getValue() const
{
	return Tools::toString(mValue);
}

bool Number::isValid() const
{
	return true;
}

void Number::operator_assign(Object *other)
{
	mValue = Tools::stringToFloat(other->getValue());

	Object::setValue(other->getValue());
}

void Number::operator_divide(Object *other)
{
	mValue /= Tools::stringToFloat(other->getValue());

	Object::setValue(Tools::toString(mValue));
}

bool Number::operator_equal(Object *other)
{
	return (mValue == Tools::stringToFloat(other->getValue()));
}

bool Number::operator_greater(Object *other)
{
	return (mValue > Tools::stringToFloat(other->getValue()));
}

bool Number::operator_greater_equal(Object *other)
{
	return (mValue >= Tools::stringToFloat(other->getValue()));
}

bool Number::operator_less(Object *other)
{
	return (mValue < Tools::stringToFloat(other->getValue()));
}

bool Number::operator_less_equal(Object *other)
{
	return (mValue <= Tools::stringToFloat(other->getValue()));
}

void Number::operator_multiply(Object *other)
{
	mValue *= Tools::stringToFloat(other->getValue());

	Object::setValue(Tools::toString(mValue));
}

void Number::operator_plus(Object *other)
{
	mValue += Tools::stringToFloat(other->getValue());

	Object::setValue(Tools::toString(mValue));
}

void Number::operator_subtract(Object *other)
{
	mValue -= Tools::stringToFloat(other->getValue());

	Object::setValue(Tools::toString(mValue));
}

std::string Number::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
