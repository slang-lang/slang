
// Header
#include "Value.h"

// Library includes

// Project includes
#include <Tools/Strings.h>

#include <utility>
#include "Tokenizer.h"

// Namespace declarations


namespace Utils {


Value::Value()
: mName(""),
  mType(""),
  mValue(""),
  mIsArray(false),
  mSize(0)
{
}

Value::Value(std::string v)
: mName(""),
  mType(""),
  mValue(std::move(v)),
  mIsArray(false),
  mSize(0)
{
}

Value::Value(std::string t, std::string v)
: mName(""),
  mType(std::move(t)),
  mValue(std::move(v)),
  mIsArray(false),
  mSize(0)
{
}

Value::Value(std::string n, std::string t, std::string v)
: mName(std::move(n)),
  mType(std::move(t)),
  mValue(std::move(v)),
  mIsArray(false),
  mSize(0)
{
}

const std::string& Value::getName() const
{
	return mName;
}

const std::string& Value::getType() const
{
	return mType;
}

const std::string& Value::getValue() const
{
	return mValue;
}

bool Value::is(const std::string& name) const
{
	return Tools::StringCompare(mName, name);
}

bool Value::isArray() const
{
	return mIsArray;
}

size_t Value::size() const
{
	return mSize;
}

void Value::size(size_t size)
{
	mSize = size;
}

bool Value::isValid() const
{
	return ( mValue.length() > 0 );
}

bool Value::ofType(const std::string& type) const
{
	return Tools::StringCompare(mType, type);
}

bool Value::ofValue(const std::string& value) const
{
	return Tools::StringCompare(mValue, value);
}

//void Value::setType(const std::string& t)
//{
//	mType = t;
//}

bool Value::toBool() const
{
	return Tools::stringToBool(mValue);
}

double Value::toDouble() const
{
	return Tools::stringToDouble(mValue);
}

float Value::toFloat() const
{
	return Tools::stringToFloat(mValue);
}

int Value::toInt() const
{
	return Tools::stringToInt(mValue);
}

const std::string& Value::toString() const
{
	return mValue;
}


}
