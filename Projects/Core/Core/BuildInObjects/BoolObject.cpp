
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
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, Tools::toString(value)),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

BoolObject::BoolObject(const std::string& name, bool value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, Tools::toString(value)),
  mValue(value)
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

BoolObject::BoolObject(const std::string& name, const std::string& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value),
  mValue(Tools::stringToBool(value))
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

BoolObject::BoolObject(const BoolObject& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, object.getValue()),
  mValue(object.getNativeValue())
{
}

BoolObject::operator bool() const
{
	return mValue;
}

bool BoolObject::getNativeValue() const
{
	return mValue;
}

const std::string& BoolObject::getTypeName() const
{
	return TYPENAME;
}

std::string BoolObject::getValue() const
{
	return Tools::toString(mValue);
}

bool BoolObject::isValid() const
{
	return mValue;
}

void BoolObject::operator_assign(BoolObject *other)
{
	mValue = other->getNativeValue();
}

void BoolObject::operator_assign(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		BoolObject tmp(Tools::stringToBool(other->getValue()));

		operator_assign(&tmp);
	}
	else {
		Object::operator_assign(other);
	}
}

void BoolObject::operator_bitand(BoolObject *other)
{
	mValue &= other->getNativeValue();
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
	mValue |= other->getNativeValue();
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
	return (mValue == other->getNativeValue());
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

void BoolObject::setNativeValue(bool value)
{
	mValue = value;
}

void BoolObject::setValue(const std::string& value)
{
	mValue = Tools::stringToBool(value);
}

std::string BoolObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
}
