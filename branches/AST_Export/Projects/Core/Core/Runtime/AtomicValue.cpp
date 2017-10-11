
// Header
#include "AtomicValue.h"

// Library includes

// Project includes
#include <Core/Tools.h>
#include <Tools/Strings.h>
#include <Core/Common/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


AtomicValue::AtomicValue()
: mType(Type::UNKOWN)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.object_ = 0;
	//mValue.string_ = 0;
}

AtomicValue::AtomicValue(bool val)
: mType(Type::BOOL)
{
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.object_ = 0;
	//mValue.string_ = 0;

	mValue.bool_ = val;
}

AtomicValue::AtomicValue(double val)
: mType(Type::DOUBLE)
{
	mValue.bool_ = false;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.object_ = 0;
	//mValue.string_ = 0;

	mValue.double_ = val;
}

AtomicValue::AtomicValue(float val)
: mType(Type::FLOAT)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.int_ = 0;
	mValue.object_ = 0;
	//mValue.string_ = 0;

	mValue.float_ = val;
}

AtomicValue::AtomicValue(int val)
: mType(Type::INT)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.object_ = 0;
	//mValue.string_ = 0;

	mValue.int_ = val;
}

AtomicValue::AtomicValue(const char* val)
: mStringValue(std::string(val)),
  mType(Type::STRING)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.object_ = 0;
}

AtomicValue::AtomicValue(const std::string& val)
: mStringValue(val),
  mType(Type::STRING)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.object_ = 0;
}

AtomicValue::AtomicValue(unsigned int val)
: mType(Type::OBJECT)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;

	mValue.object_ = val;
}

AtomicValue::~AtomicValue()
{
}

void AtomicValue::operator=(bool val)
{
	mStringValue = "";

	mType = Type::BOOL;
	mValue.bool_ = val;
}

void AtomicValue::operator=(double val)
{
	mStringValue = "";

	mType = Type::DOUBLE;
	mValue.double_ = val;
}

void AtomicValue::operator=(float val)
{
	mStringValue = "";

	mType = Type::FLOAT;
	mValue.float_ = val;
}

void AtomicValue::operator=(int val)
{
	mStringValue = "";

	mType = Type::INT;
	mValue.int_ = val;
}

void AtomicValue::operator=(const char* val)
{
	mValue.double_ = 0.0;

	mType = Type::STRING;
	//mValue.string_ = val.c_str();
	mStringValue = std::string(val);
}

void AtomicValue::operator=(const std::string& val)
{
	mValue.double_ = 0.0;

	mType = Type::STRING;
	//mValue.string_ = val.c_str();
	mStringValue = val;
}

void AtomicValue::operator=(unsigned int val)
{
	mStringValue = "";

	mType = Type::OBJECT;
	mValue.object_ = val;
}

bool AtomicValue::toBool() const
{
	switch ( mType ) {
		case Type::BOOL: return mValue.bool_;
		case Type::DOUBLE: return (mValue.double_ != 0.0);
		case Type::FLOAT: return (mValue.float_ != 0.f);
		case Type::INT: return (mValue.int_ != 0);
		case Type::OBJECT: return (mValue.object_ != 0);
		case Type::STRING: return Utils::Tools::stringToBool(mStringValue);
		default: break;
	}

	assert(!"invalid data type");
	return false;
}

double AtomicValue::toDouble() const
{
	switch ( mType ) {
		case Type::BOOL: return (double)mValue.bool_;
		case Type::DOUBLE: return mValue.double_;
		case Type::FLOAT: return (double)mValue.float_;
		case Type::INT: return (double)mValue.int_;
		case Type::OBJECT: throw Common::Exceptions::NotSupported("conversion to int not supported");
		case Type::STRING: return Utils::Tools::stringToDouble(mStringValue);
		default: break;
	}

	assert(!"invalid data type");
	return 0.0;
}

float AtomicValue::toFloat() const
{
	switch ( mType ) {
		case Type::BOOL: return (float)mValue.bool_;
		case Type::DOUBLE: return (float)mValue.double_;
		case Type::FLOAT: return mValue.float_;
		case Type::INT: return (float)mValue.int_;
		case Type::OBJECT: throw Common::Exceptions::NotSupported("conversion to float not supported");
		case Type::STRING: return Utils::Tools::stringToFloat(mStringValue);
		default: break;
	}

	assert(!"invalid data type");
	return 0.f;
}

int AtomicValue::toInt() const
{
	switch ( mType ) {
		case Type::BOOL: return (int)mValue.bool_;
		case Type::DOUBLE: return (int)mValue.double_;
		case Type::FLOAT: return (int)mValue.float_;
		case Type::INT: return mValue.int_;
		case Type::OBJECT: throw Common::Exceptions::NotSupported("conversion to int not supported");
		case Type::STRING: return Utils::Tools::stringToInt(mStringValue);
		default: break;
	}

	assert(!"invalid data type");
	return 0;
}

std::string AtomicValue::toStdString() const
{
	switch ( mType ) {
		case Type::BOOL: return Utils::Tools::toString(mValue.bool_);
		case Type::DOUBLE: return Utils::Tools::toString(mValue.double_);
		case Type::FLOAT: return Utils::Tools::toString(mValue.float_);
		case Type::INT: return Utils::Tools::toString(mValue.int_);
		case Type::OBJECT: throw Common::Exceptions::NotSupported("conversion to int not supported");
		case Type::STRING: return mStringValue;
		default: break;
	}

	assert(!"invalid data type");
	return "";
}

unsigned int AtomicValue::toObject() const
{
	switch ( mType ) {
		case Type::BOOL: return (unsigned int)mValue.bool_;
		case Type::DOUBLE: return (unsigned int)mValue.double_;
		case Type::FLOAT: return (unsigned int)mValue.float_;
		case Type::INT: return (unsigned int)mValue.int_;
		case Type::OBJECT: return mValue.object_;
		case Type::STRING: return (unsigned int)Utils::Tools::stringToInt(mStringValue);
		default: break;
	}

	assert(!"invalid data type");
	return 0;
}

AtomicValue::Type::E AtomicValue::type() const
{
	return mType;
}


}
}
