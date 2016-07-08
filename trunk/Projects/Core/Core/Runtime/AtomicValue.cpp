
// Header
#include "AtomicValue.h"

// Library includes

// Project includes
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


AtomicValue::AtomicValue()
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;
	mValue.uint_ = 0;

	type = UNKOWN;
}

AtomicValue::AtomicValue(bool val)
{
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;
	mValue.uint_ = 0;

	type = BOOL;
	mValue.bool_ = val;
}

AtomicValue::AtomicValue(double val)
{
	mValue.bool_ = false;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;
	mValue.uint_ = 0;

	type = DOUBLE;
	mValue.double_ = val;
}

AtomicValue::AtomicValue(float val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.int_ = 0;
	//mValue.string_ = 0;
	mValue.uint_ = 0;

	type = FLOAT;
	mValue.float_ = val;
}

AtomicValue::AtomicValue(int val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	//mValue.string_ = 0;
	mValue.uint_ = 0;

	type = INT;
	mValue.int_ = val;
}

AtomicValue::AtomicValue(const char* val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.uint_ = 0;

	type = STRING;
	//mValue.string_ = std::string(val);
	mStringValue = std::string(val);
}

AtomicValue::AtomicValue(const std::string& val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.uint_ = 0;

	type = STRING;
	//mValue.string_ = val.c_str();
	mStringValue = val;
}

AtomicValue::AtomicValue(unsigned int val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;

	type = UINT;
	mValue.uint_ = val;
}

AtomicValue::~AtomicValue()
{
}

void AtomicValue::operator=(bool val)
{
	mStringValue = "";

	type = BOOL;
	mValue.bool_ = val;
}

void AtomicValue::operator=(double val)
{
	mStringValue = "";

	type = DOUBLE;
	mValue.double_ = val;
}

void AtomicValue::operator=(float val)
{
	mStringValue = "";

	type = FLOAT;
	mValue.float_ = val;
}

void AtomicValue::operator=(int val)
{
	mStringValue = "";

	type = INT;
	mValue.int_ = val;
}

void AtomicValue::operator=(const char* val)
{
	mValue.double_ = 0.0;

	type = STRING;
	//mValue.string_ = val.c_str();
	mStringValue = std::string(val);
}

void AtomicValue::operator=(const std::string& val)
{
	mValue.double_ = 0.0;

	type = STRING;
	//mValue.string_ = val.c_str();
	mStringValue = val;
}

void AtomicValue::operator=(unsigned int val)
{
	mStringValue = "";

	type = UINT;
	mValue.uint_ = val;
}

bool AtomicValue::toBool() const
{
	switch ( type ) {
		case BOOL: return mValue.bool_;
		case DOUBLE: return (mValue.double_ != 0.0);
		case FLOAT: return (mValue.float_ != 0.f);
		case INT: return (mValue.int_ != 0);
		case STRING: return Tools::stringToBool(mStringValue);
		case UINT: return (mValue.uint_ != 0);
		default: break;
	}

	assert(!"invalid data type");
	return false;
}

double AtomicValue::toDouble() const
{
	switch ( type ) {
		case BOOL: return (double)mValue.bool_;
		case DOUBLE: return mValue.double_;
		case FLOAT: return (double)mValue.float_;
		case INT: return (double)mValue.int_;
		case STRING: return Tools::stringToDouble(mStringValue);
		case UINT: return (double)mValue.uint_;
		default: break;
	}

	assert(!"invalid data type");
	return 0.0;
}

float AtomicValue::toFloat() const
{
	switch ( type ) {
		case BOOL: return (float)mValue.bool_;
		case DOUBLE: return (float)mValue.double_;
		case FLOAT: return mValue.float_;
		case INT: return (float)mValue.int_;
		case STRING: return Tools::stringToFloat(mStringValue);
		case UINT: return (float)mValue.uint_;
		default: break;
	}

	assert(!"invalid data type");
	return 0.f;
}

int AtomicValue::toInt() const
{
	switch ( type ) {
		case BOOL: return (int)mValue.bool_;
		case DOUBLE: return (int)mValue.double_;
		case FLOAT: return (int)mValue.float_;
		case INT: return mValue.int_;
		case STRING: return Tools::stringToInt(mStringValue);
		case UINT: return (int)mValue.uint_;
		default: break;
	}

	assert(!"invalid data type");
	return 0;
}

std::string AtomicValue::toStdString() const
{
	switch ( type ) {
		case BOOL: return Tools::ConvertToStdString(mValue.bool_);
		case DOUBLE: return Tools::ConvertToStdString(mValue.double_);
		case FLOAT: return Tools::ConvertToStdString(mValue.float_);
		case INT: return Tools::ConvertToStdString(mValue.int_);
		case STRING: return mStringValue;
		case UINT: return Tools::ConvertToStdString(mValue.uint_);
		default: break;
	}

	assert(!"invalid data type");
	return "";
}


}
}
