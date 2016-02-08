
// Header
#include "BoolObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "FloatObject.h"
#include "IntegerObject.h"
#include "NumberObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


bool BoolObject::DEFAULTVALUE = false;
std::string BoolObject::TYPENAME = "bool";


BoolObject::BoolObject(bool value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, "")
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

BoolObject::BoolObject(const std::string& name, bool value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, "")
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setNativeValue(value);
}

BoolObject::BoolObject(const std::string& name, const std::string& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, "")
{
	mIsAtomicType = true;
	mIsConstructed = true;

	setValue(value);
}

BoolObject::BoolObject(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, "")
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;

	setValue(object.getValue());
}

BoolObject::operator bool() const
{
	return mNativeValue;
}

bool BoolObject::getNativeValue() const
{
	return mNativeValue;
}

const std::string& BoolObject::getTypeName() const
{
	return TYPENAME;
}

std::string BoolObject::getValue() const
{
	return mValue;
}

bool BoolObject::isValid() const
{
	return mNativeValue;
}

void BoolObject::operator_assign(BoolObject *other)
{
	setNativeValue(other->getNativeValue());
}

void BoolObject::operator_assign(Object *other)
{
/*
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		BoolObject tmp(isTrue(*other));

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
*/

	setNativeValue(isTrue(*other));
}

void BoolObject::operator_bitand(BoolObject *other)
{
	setNativeValue(mNativeValue & other->getNativeValue());
}

void BoolObject::operator_bitand(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(other->getValue()));

		operator_bitand(&tmp);
	}
	else {
		Object::operator_bitand(other);
	}
}

void BoolObject::operator_bitor(BoolObject *other)
{
	setNativeValue(mNativeValue | other->getNativeValue());
}

void BoolObject::operator_bitor(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(other->getValue()));

		operator_bitor(&tmp);
	}
	else {
		Object::operator_bitor(other);
	}
}

bool BoolObject::operator_equal(BoolObject *other)
{
	return (mNativeValue == other->getNativeValue());
}

bool BoolObject::operator_equal(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(other->getValue()));

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

void BoolObject::operator_unary_not()
{
	setNativeValue(!mNativeValue);
}

void BoolObject::setNativeValue(bool value)
{
	mNativeValue = value;
	mValue = Tools::toString(value);
}

void BoolObject::setValue(const std::string& value)
{
	mNativeValue = isTrue(value);
	mValue = Tools::toString(isTrue(value));
}

std::string BoolObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
}
