
// Header
#include "Value.h"

// Library includes

// Project includes
#include <Tools/Strings.h>
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

Value::Value(const std::string& v)
: mName(""),
  mType(""),
  mValue(v)
{
}

Value::Value(const std::string& t, const std::string& v)
: mName(""),
  mType(t),
  mValue(v)
{
}

Value::Value(const std::string& n, const std::string& t, const std::string& v)
: mName(n),
  mType(t),
  mValue(v),
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
	return Tools::StringCompareI(mName, name);
}

bool Value::is_(const std::string& name) const
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
	return Tools::StringCompareI(mType, type);
}

bool Value::ofType_(const std::string& type) const
{
	return Tools::StringCompare(mType, type);
}

bool Value::ofValue(const std::string& value) const
{
	return Tools::StringCompareI(mValue, value);
}

bool Value::ofValue_(const std::string& value) const
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

vector2f Value::toVector2f()
{
	vector2f result;
	Tokenizer t(mValue);

	if ( t.hasNext() ) {
		result.x = Tools::stringToFloat(t.getToken());
		if ( t.hasNext() ) {
			result.y = Tools::stringToFloat(t.getToken());
			return result;
		}
	}

	//error("Invalid input provided for '" + mName + "' as '" + mType + "' with '" + mValue + "'");
	return vector2f();
}

vector3f Value::toVector3f()
{
	vector3f result;
	Tokenizer t(mValue);

	if ( t.hasNext() ) {
		result.x = Tools::stringToFloat(t.getToken());
		if ( t.hasNext() ) {
			result.y = Tools::stringToFloat(t.getToken());

			if ( t.hasNext() ) {
				result.z = Tools::stringToFloat(t.getToken());
				return result;
			}
		}
	}

	//error("Invalid input provided for '" + mName + "' as '" + mType + "' with '" + mValue + "'");
	return vector3f();
}

vector4f Value::toVector4f()
{
	vector4f result;
	Tokenizer t(mValue);

	if ( t.hasNext() ) {
		result.x = Tools::stringToFloat(t.getToken());
		if ( t.hasNext() ) {
			result.y = Tools::stringToFloat(t.getToken());

			if ( t.hasNext() ) {
				result.z = Tools::stringToFloat(t.getToken());

				if ( t.hasNext() ) {
					result.w = Tools::stringToFloat(t.getToken());
					return result;
				}
			}
		}
	}

	//error("Invalid input provided for '" + mName + "' as '" + mType + "' with '" + mValue + "'");
	return vector4f();
}


}
