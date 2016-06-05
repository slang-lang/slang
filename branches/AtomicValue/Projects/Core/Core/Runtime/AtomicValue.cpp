
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
	type = UNKOWN;
	value.bool_ = false;
	value.double_ = 0.0;
	value.float_ = 0.f;
	value.int_ = 0;
	value.string_ = 0;
}

AtomicValue::AtomicValue(bool val)
{
	value.double_ = 0.0;
	value.float_ = 0.f;
	value.int_ = 0;
	value.string_ = 0;

	type = BOOL;
	value.bool_ = val;
}

AtomicValue::AtomicValue(double val)
{
	value.bool_ = false;
	value.float_ = 0.f;
	value.int_ = 0;
	value.string_ = 0;

	type = DOUBLE;
	value.double_ = val;
}

AtomicValue::AtomicValue(float val)
{
	value.bool_ = false;
	value.double_ = 0.0;
	value.int_ = 0;
	value.string_ = 0;

	type = FLOAT;
	value.float_ = val;
}

AtomicValue::AtomicValue(int val)
{
	value.bool_ = false;
	value.double_ = 0.0;
	value.float_ = 0.f;
	value.string_ = 0;

	type = INT;
	value.int_ = val;
}

AtomicValue::AtomicValue(const char* val)
{
	value.bool_ = false;
	value.double_ = 0.0;
	value.float_ = 0.f;
	value.int_ = 0;

	type = STRING;
	value.string_ = val;
}

AtomicValue::AtomicValue(const std::string& val)
{
	value.bool_ = false;
	value.double_ = 0.0;
	value.float_ = 0.f;
	value.int_ = 0;

	type = STRING;
	value.string_ = val.c_str();
}

void AtomicValue::operator=(bool v)
{
	type = BOOL;
	value.bool_ = v;
}

void AtomicValue::operator=(double v)
{
	type = DOUBLE;
	value.double_ = v;
}

void AtomicValue::operator=(float v)
{
	type = FLOAT;
	value.float_ = v;
}

void AtomicValue::operator=(int v)
{
	type = INT;
	value.int_ = v;
}

void AtomicValue::operator=(const char* v)
{
	type = STRING;
	value.string_ = v;
}

void AtomicValue::operator=(const std::string& v)
{
	type = STRING;
	value.string_ = v.c_str();
}

bool AtomicValue::toBool() const
{
	switch ( type ) {
		case BOOL: return value.bool_;
		case DOUBLE: return (bool)value.double_;
		case FLOAT: return (bool)value.float_;
		case INT: return (bool)value.int_;
		case STRING: return (bool)value.string_;
		default: break;
	}

	assert(!"invalid data type");
	return false;
}

double AtomicValue::toDouble() const
{
	switch ( type ) {
		case BOOL: return (double)value.bool_;
		case DOUBLE: return value.double_;
		case FLOAT: return (double)value.float_;
		case INT: return (double)value.int_;
		case STRING: return Tools::stringToDouble(value.string_);
		default: break;
	}

	assert(!"invalid data type");
	return 0.0;
}

float AtomicValue::toFloat() const
{
	switch ( type ) {
		case BOOL: return (float)value.bool_;
		case DOUBLE: return (float)value.double_;
		case FLOAT: return value.float_;
		case INT: return (float)value.int_;
		case STRING: return Tools::stringToFloat(value.string_);
		default: break;
	}

	assert(!"invalid data type");
	return 0.f;
}

int AtomicValue::toInt() const
{
	switch ( type ) {
		case BOOL: return (int)value.bool_;
		case DOUBLE: return (int)value.double_;
		case FLOAT: return (int)value.float_;
		case INT: return value.int_;
		case STRING: return Tools::stringToInt(value.string_);
		default: break;
	}

	assert(!"invalid data type");
	return 0;
}

const char* AtomicValue::toString() const
{
	switch ( type ) {
		case BOOL: return Tools::ConvertToString(value.bool_).c_str();
		case DOUBLE: return Tools::ConvertToString(value.double_).c_str();
		case FLOAT: return Tools::ConvertToString(value.float_).c_str();
		case INT: return Tools::ConvertToString(value.int_).c_str();
		case STRING: return value.string_;
		default: break;
	}

	assert(!"invalid data type");
	return "";
}

std::string AtomicValue::toStdString() const
{
	switch ( type ) {
		case BOOL: return Tools::ConvertToString(value.bool_);
		case DOUBLE: return Tools::ConvertToString(value.double_);
		case FLOAT: return Tools::ConvertToString(value.float_);
		case INT: return Tools::ConvertToString(value.int_);
		case STRING: return std::string(value.string_);
		default: break;
	}

	assert(!"invalid data type");
	return "";
}


}
}
