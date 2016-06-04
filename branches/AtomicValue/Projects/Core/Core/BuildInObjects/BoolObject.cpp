
// Header
#include "BoolObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>
#include "DoubleObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "NumberObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


bool BoolObject::DEFAULTVALUE = false;
AtomicValue BoolObject::ATOMIC_DEFAULTVALUE = false;
std::string BoolObject::TYPENAME = "bool";


BoolObject::BoolObject(AtomicValue value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

BoolObject::BoolObject(const std::string& name, bool value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

BoolObject::BoolObject(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE)
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;
}

bool BoolObject::operator_bool() const
{
	return mValue.toBool();
}

const std::string& BoolObject::getTypeName() const
{
	return TYPENAME;
}

bool BoolObject::isValid() const
{
	return mIsConstructed;
}

void BoolObject::operator_assign(BoolObject *other)
{
	mValue = other->getValue().toBool();
}

void BoolObject::operator_assign(Object *other)
{
	mValue = other->isValid();
}

void BoolObject::operator_bitand(BoolObject *other)
{
	mValue.value.bool_ &= other->getValue().toBool();
}

void BoolObject::operator_bitand(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		BoolObject tmp(other->getValue());

		operator_bitand(&tmp);
	}
	else {
		Object::operator_bitand(other);
	}
}

void BoolObject::operator_bitor(BoolObject *other)
{
	mValue.value.bool_ |= other->getValue().toBool();
}

void BoolObject::operator_bitor(Object *other)
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		BoolObject tmp(other->getValue());

		operator_bitor(&tmp);
	}
	else {
		Object::operator_bitor(other);
	}
}

bool BoolObject::operator_equal(BoolObject *other) const
{
	return mValue.toBool() == other->getValue().toBool();
}

bool BoolObject::operator_equal(Object *other) const
{
	std::string target = other->Typename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		BoolObject tmp(other->getValue());

		return operator_equal(&tmp);
	}

	return Object::operator_equal(other);
}

void BoolObject::operator_unary_not()
{
	mValue = !mValue.toBool();
}

std::string BoolObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue().toStdString();
}


}
}
