
// Header
#include "AtomicValue.h"

// Library includes

// Project includes
#include <Tools/Strings.h>

#include <utility>

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue::AtomicValue()
: mType(Type::INT)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.reference_ = 0;
}

AtomicValue::AtomicValue(bool val)
: mType(Type::BOOL)
{
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.reference_ = 0;

	mValue.bool_ = val;
}

AtomicValue::AtomicValue(double val)
: mType(Type::DOUBLE)
{
	mValue.bool_ = false;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.reference_ = 0;

	mValue.double_ = val;
}

AtomicValue::AtomicValue(float val)
: mType(Type::FLOAT)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.int_ = 0;
	mValue.reference_ = 0;

	mValue.float_ = val;
}

AtomicValue::AtomicValue(int val)
: mType(Type::INT)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.reference_ = 0;

	mValue.int_ = val;
}

AtomicValue::AtomicValue(MemoryId val)
: mType(Type::REFERENCE)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;

	mValue.reference_ = val;
}

AtomicValue::AtomicValue(std::string val)
: mStringValue(std::move(val)),
  mType(Type::STRING)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.reference_ = 0;
}

AtomicValue& AtomicValue::operator=(bool val)
{
	mStringValue = "";

	mType = Type::BOOL;
	mValue.bool_ = val;

	return *this;
}

AtomicValue& AtomicValue::operator=(double val)
{
	mStringValue = "";

	mType = Type::DOUBLE;
	mValue.double_ = val;

	return *this;
}

AtomicValue& AtomicValue::operator=(float val)
{
	mStringValue = "";

	mType = Type::FLOAT;
	mValue.float_ = val;

	return *this;
}

AtomicValue& AtomicValue::operator=(int val)
{
	mStringValue = "";

	mType = Type::INT;
	mValue.int_ = val;

	return *this;
}

AtomicValue& AtomicValue::operator=(MemoryId val)
{
	mStringValue = "";

	mType = Type::REFERENCE;
	mValue.reference_ = val;

	return *this;
}

AtomicValue& AtomicValue::operator=(const std::string& val)
{
	mValue.double_ = 0.0;

	mType = Type::STRING;
	mStringValue = val;

	return *this;
}

bool AtomicValue::toBool() const
{
	switch ( mType ) {
		case Type::BOOL: return mValue.bool_;
		case Type::DOUBLE: return (mValue.double_ != 0.0);
		case Type::FLOAT: return (mValue.float_ != 0.f);
		case Type::INT: return (mValue.int_ != 0);
		case Type::REFERENCE: return (mValue.reference_ != 0);
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
		case Type::REFERENCE: return (double)(mValue.reference_ != 0);
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
		case Type::REFERENCE: return (float)(mValue.reference_ != 0);
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
		case Type::REFERENCE: return (int)(mValue.reference_ != 0);
		case Type::STRING: return Utils::Tools::stringToInt(mStringValue);
		default: break;
	}

	assert(!"invalid data type");
	return 0;
}

MemoryId AtomicValue::toReference() const
{
	switch ( mType ) {
		case Type::REFERENCE: return mValue.reference_;

		case Type::BOOL:
		case Type::DOUBLE:
		case Type::FLOAT:
		case Type::INT:
		case Type::STRING:
		default: return MemoryId(-1);	// invalid typecast
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
		case Type::REFERENCE: return Utils::Tools::toString(mValue.reference_);
		case Type::STRING: return mStringValue;
		default: break;
	}

	assert(!"invalid data type");
	return "";
}

AtomicValue::Type::E AtomicValue::type() const
{
	return mType;
}


}
}
