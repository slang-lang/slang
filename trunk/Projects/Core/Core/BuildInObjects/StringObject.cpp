
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


std::string StringObject::DEFAULTVALUE = "";
std::string StringObject::TYPENAME = "string";


StringObject::StringObject(const std::string& value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

StringObject::StringObject(const std::string& name, const std::string& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

StringObject::StringObject(const StringObject& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, object.getValue())
{
}

StringObject::operator bool() const
{
	return !getValue().empty();
}

std::string StringObject::getNativeValue() const
{
	return mValue;
}

const std::string& StringObject::getTypeName() const
{
	return TYPENAME;
}

std::string StringObject::getValue() const
{
	return mValue;
}

void StringObject::operator_assign(BoolObject *other)
{
	mValue = other->getValue();
}

void StringObject::operator_assign(FloatObject *other)
{
	mValue = other->getValue();
}

void StringObject::operator_assign(IntegerObject *other)
{
	mValue = other->getValue();
}

void StringObject::operator_assign(NumberObject *other)
{
	mValue = other->getValue();
}

void StringObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		StringObject tmp(other->getValue());

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

void StringObject::operator_assign(StringObject *other)
{
	mValue = other->getNativeValue();
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
	return (mValue == other->getNativeValue());
}

void StringObject::operator_plus(BoolObject *other)
{
	mValue += other->getValue();
}

void StringObject::operator_plus(FloatObject *other)
{
	mValue += other->getValue();
}

void StringObject::operator_plus(IntegerObject *other)
{
	mValue += other->getValue();
}

void StringObject::operator_plus(NumberObject *other)
{
	mValue += other->getValue();
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
	mValue += other->getNativeValue();
}

void StringObject::setNativeValue(const std::string& value)
{
	mValue = value;
}

void StringObject::setValue(const std::string& value)
{
	mValue = value;
}

std::string StringObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
