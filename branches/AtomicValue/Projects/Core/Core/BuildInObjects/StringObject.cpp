
// Header
#include "StringObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "NumberObject.h"
#include "UserObject.h"
#include "VoidObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


std::string StringObject::DEFAULTVALUE = "";
std::string StringObject::TYPENAME = "string";


StringObject::StringObject(AtomicValue value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value.toString())
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

StringObject::StringObject(const std::string& value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

StringObject::StringObject(const std::string& name, const std::string& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

StringObject::StringObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE)
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;

	std::string source = other.Typename();

	if ( source == StringObject::TYPENAME ||
		 source == BoolObject::TYPENAME ||
		 source == DoubleObject::TYPENAME ||
		 source == FloatObject::TYPENAME ||
		 source == IntegerObject::TYPENAME ||
		 source == NumberObject::TYPENAME ) {
		mValue = other.getValue().toString();
	}
	else {
		throw Utils::Exceptions::InvalidTypeCast("from " + source + " to " + TYPENAME);
	}
}

const std::string& StringObject::getTypeName() const
{
	return TYPENAME;
}

bool StringObject::isValid() const
{
	return mIsConstructed;
}

void StringObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		mValue = other->getValue().toString();
	}
	else {
		Object::operator_assign(other);
	}
}

void StringObject::operator_assign(StringObject *other)
{
	mValue = other->getValue().toString();
}

bool StringObject::operator_bool() const
{
	return mValue.toBool();
}

bool StringObject::operator_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == StringObject::TYPENAME ) {
		return mValue.toStdString() == other->getValue().toStdString();
	}

	return Object::operator_equal(other);
}

bool StringObject::operator_equal(StringObject *other) const
{
	return mValue.toStdString() == other->getValue().toStdString();
}

void StringObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		mValue = mValue.toStdString() + other->getValue().toStdString();
	}
	else {
		Object::operator_plus(other);
	}
}

void StringObject::operator_plus(StringObject *other)
{
	mValue = mValue.toStdString() + other->getValue().toStdString();
}

std::string StringObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue().toStdString();
}


}
}
