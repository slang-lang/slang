
// Header
#include "AtomicValue.h"

// Library includes

// Project includes
#include <Core/Common/StringTools.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


AtomicValue::AtomicValue()
{
	type = UNKOWN;
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;
}

AtomicValue::AtomicValue(bool val)
{
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;

	type = BOOL;
	mValue.bool_ = val;
}

AtomicValue::AtomicValue(double val)
{
	mValue.bool_ = false;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;

	type = DOUBLE;
	mValue.double_ = val;
}

AtomicValue::AtomicValue(float val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.int_ = 0;
	//mValue.string_ = 0;

	type = FLOAT;
	mValue.float_ = val;
}

AtomicValue::AtomicValue(int val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	//mValue.string_ = 0;

	type = INT;
	mValue.int_ = val;
}

/*
AtomicValue::AtomicValue(const char* val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;

	type = STRING;
	mValue.string_ = Common::Strings::duplicateStringValue(val, strlen(val));
}
*/

AtomicValue::AtomicValue(const std::string& val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;

	type = STRING;
	//mValue.string_ = val.c_str();
	mStringValue = val;
}

AtomicValue::~AtomicValue()
{
/*
	if ( type == STRING ) {
		Common::Strings::releaseStringValue(mValue.string_, strlen(mValue.string_));
	}
*/
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

/*
void AtomicValue::operator=(const char* val)
{
	mStringValue = "";

	type = STRING;
	mValue.string_ = Common::Strings::duplicateStringValue(val, strlen(val));
}
*/

void AtomicValue::operator=(const std::string& val)
{
	mValue.double_ = 0.0;

	type = STRING;
	//mValue.string_ = val.c_str();
	mStringValue = val;
}

bool AtomicValue::toBool() const
{
	switch ( type ) {
		case BOOL: return mValue.bool_;
		case DOUBLE: return (bool)mValue.double_;
		case FLOAT: return (bool)mValue.float_;
		case INT: return (bool)mValue.int_;
		//case STRING: return (bool)mValue.string_;
		case STRING: return Tools::stringToBool(mStringValue);
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
		//case STRING: return Tools::stringToDouble(mValue.string_);
		case STRING: return Tools::stringToDouble(mStringValue);
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
		//case STRING: return Tools::stringToFloat(mValue.string_);
		case STRING: return Tools::stringToFloat(mStringValue);
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
		//case STRING: return Tools::stringToInt(mValue.string_);
		case STRING: return Tools::stringToInt(mStringValue);
		default: break;
	}

	assert(!"invalid data type");
	return 0;
}

/*
const char* AtomicValue::toString() const
{
	switch ( type ) {
		case BOOL: return Tools::ConvertToStdString(mValue.bool_).c_str();
		case DOUBLE: return Tools::ConvertToStdString(mValue.double_).c_str();
		case FLOAT: return Tools::ConvertToStdString(mValue.float_).c_str();
		case INT: return Tools::ConvertToStdString(mValue.int_).c_str();
		//case STRING: return mValue.string_;
		case STRING: return mStringValue.c_str();
		default: break;
	}

	assert(!"invalid data type");
	return "";
}
*/

std::string AtomicValue::toStdString() const
{
	switch ( type ) {
		case BOOL: return Tools::ConvertToStdString(mValue.bool_);
		case DOUBLE: return Tools::ConvertToStdString(mValue.double_);
		case FLOAT: return Tools::ConvertToStdString(mValue.float_);
		case INT: return Tools::ConvertToStdString(mValue.int_);
		//case STRING: return std::string(mValue.string_);
		case STRING: return mStringValue;
		default: break;
	}

	assert(!"invalid data type");
	return "";
}


}
}
