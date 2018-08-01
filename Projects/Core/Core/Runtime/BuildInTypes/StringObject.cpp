
// Header
#include "StringObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/Exceptions.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "UserObject.h"
#include "VoidObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


AtomicValue StringObject::DEFAULTVALUE = AtomicValue(std::string(""));
std::string StringObject::TYPENAME = _string;


StringObject::StringObject(const AtomicValue& value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue(value.toStdString()))
{
	mIsAtomicType = true;
}

StringObject::StringObject(const std::string& value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue(value))
{
	mIsAtomicType = true;
}

StringObject::StringObject(const std::string& name, const AtomicValue& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
}

StringObject::StringObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE)
{
	// generic type cast

	mIsAtomicType = true;

	std::string source = other.QualifiedTypename();

	if ( source == IntegerObject::TYPENAME ||
		 source == BoolObject::TYPENAME ||
		 source == StringObject::TYPENAME ||
		 source == DoubleObject::TYPENAME ||
		 source == FloatObject::TYPENAME ) {
		mValue = other.getValue().toStdString();
	}
	else if ( other.isEnumerationValue() ) {
		mValue = other.getValue().toStdString();
	}
	else {
		Object::operator_assign(&other);
	}
}

void StringObject::operator_assign(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == StringObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = other->getValue().toStdString();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation("'" + TYPENAME + "' offers no = operator for use with '" + other->QualifiedTypename() + "'");
}

void StringObject::operator_assign(const StringObject *other)
{
	mValue = other->getValue().toStdString();
}

bool StringObject::operator_bool() const
{
	return mValue.toBool();
}

bool StringObject::operator_equal(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		return mValue.toStdString() == other->getValue().toStdString();
	}

	return Object::operator_equal(other);
}

bool StringObject::operator_equal(const StringObject *other)
{
	return mValue.toStdString() == other->getValue().toStdString();
}

bool StringObject::operator_greater(const StringObject *other)
{
	return mValue.toStdString() > other->getValue().toStdString();
}

bool StringObject::operator_greater(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		return mValue.toStdString() > other->getValue().toStdString();
	}

	return Object::operator_greater(other);
}

bool StringObject::operator_greater_equal(const StringObject *other)
{
	return mValue.toStdString() >= other->getValue().toStdString();
}

bool StringObject::operator_greater_equal(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		return mValue.toStdString() >= other->getValue().toStdString();
	}

	return Object::operator_greater_equal(other);
}

bool StringObject::operator_less(const StringObject *other)
{
	return mValue.toStdString() < other->getValue().toStdString();
}

bool StringObject::operator_less(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		return mValue.toStdString() < other->getValue().toStdString();
	}

	return Object::operator_less(other);
}

bool StringObject::operator_less_equal(const StringObject *other)
{
	return mValue.toStdString() <= other->getValue().toStdString();
}

bool StringObject::operator_less_equal(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		return mValue.toStdString() <= other->getValue().toStdString();
	}

	return Object::operator_less_equal(other);
}

void StringObject::operator_plus(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == StringObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ) {
		mValue = mValue.toStdString() + other->getValue().toStdString();
		return;
	}

	throw Runtime::Exceptions::InvalidOperation("'" + TYPENAME + "' offers no + operator for use with '" + other->QualifiedTypename() + "'");
}

void StringObject::operator_plus(const StringObject *other)
{
	mValue = mValue.toStdString() + other->getValue().toStdString();
}


}
}
