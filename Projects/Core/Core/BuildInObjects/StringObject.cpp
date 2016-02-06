
// Header
#include "StringObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "BoolObject.h"
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


StringObject::StringObject(const std::string& value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, "")
{
	mIsAtomicType = true;

	Constructor(ParameterList());

	setNativeValue(value);
}

StringObject::StringObject(const std::string& name, const std::string& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, "")
{
	mIsAtomicType = true;

	Constructor(ParameterList());

	setNativeValue(value);
}

StringObject::StringObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, "")
{
	// generic type cast

	std::string source = other.Typename();

	if ( source == BoolObject::TYPENAME ||
		 source == FloatObject::TYPENAME ||
		 source == IntegerObject::TYPENAME ||
		 source == NumberObject::TYPENAME ) {
		setValue(other.getValue());
	}
	else {
		throw Utils::Exceptions::InvalidTypeCast("from " + source + " to " + TYPENAME);
	}
}

StringObject::operator bool() const
{
	return !mNativeValue.empty();
}

std::string StringObject::getNativeValue() const
{
	return mNativeValue;
}

const std::string& StringObject::getTypeName() const
{
	return TYPENAME;
}

std::string StringObject::getValue() const
{
	return mValue;
}

bool StringObject::isValid() const
{
	return !mNativeValue.empty();
}

void StringObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		setNativeValue(other->getValue());
	}
	else {
		Object::operator_assign(other);
	}
}

void StringObject::operator_assign(StringObject *other)
{
	setNativeValue(other->getNativeValue());
}

bool StringObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == StringObject::TYPENAME ) {
		StringObject tmp(other->getValue());

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

bool StringObject::operator_equal(StringObject *other)
{
	return (mNativeValue == other->getNativeValue());
}

void StringObject::operator_plus(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		StringObject tmp(other->getValue());

		operator_plus(&tmp);
	}
	else {
		Object::operator_plus(other);
	}
}

void StringObject::operator_plus(StringObject *other)
{
	setNativeValue(mNativeValue + other->getNativeValue());
}

void StringObject::setNativeValue(const std::string& value)
{
	mNativeValue = value;
	mValue = value;
}

void StringObject::setValue(const std::string& value)
{
	mNativeValue = value;
	mValue = value;
}

std::string StringObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
}
