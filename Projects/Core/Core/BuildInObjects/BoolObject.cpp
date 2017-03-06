
// Header
#include "BoolObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Common/Exceptions.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>
#include "DoubleObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


AtomicValue BoolObject::DEFAULTVALUE = AtomicValue(false);
std::string BoolObject::TYPENAME = "bool";


BoolObject::BoolObject(AtomicValue value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue(value.toBool()))
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

BoolObject::BoolObject(const std::string& name, bool value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, AtomicValue(value))
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

BoolObject::BoolObject(const Object& other)
: Object(other.getName(), SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE)
{
	// generic type cast

	mIsAtomicType = true;
	mIsConstructed = true;

	std::string target = other.QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		mValue = other.getValue().toBool();
	}
	else {
		//Object::operator_assign(&other);

		mValue = other.isValid();
	}
}

bool BoolObject::operator_bool() const
{
	return mValue.toBool();
}

bool BoolObject::isValid() const
{
	return mIsConstructed;
}

void BoolObject::operator_assign(const BoolObject *other)
{
	mValue = other->getValue().toBool();
}

void BoolObject::operator_assign(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		mValue = other->getValue().toBool();
	}
	else {
		Object::operator_assign(other);
	}
}

/*
void BoolObject::operator_bitand(const BoolObject *other)
{
	mValue = mValue.toBool() & other->getValue().toBool();
}

void BoolObject::operator_bitand(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		mValue = mValue.toBool() & other->getValue().toBool();
	}
	else {
		Object::operator_bitand(other);
	}
}
*/

/*
void BoolObject::operator_bitor(const BoolObject *other)
{
	mValue = mValue.toBool() | other->getValue().toBool();
}

void BoolObject::operator_bitor(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		mValue = mValue.toBool() | other->getValue().toBool();
	}
	else {
		Object::operator_bitor(other);
	}
}
*/

bool BoolObject::operator_equal(const BoolObject *other)
{
	return mValue.toBool() == other->getValue().toBool();
}

bool BoolObject::operator_equal(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == StringObject::TYPENAME ) {
		return mValue.toBool() == other->getValue().toBool();
	}

	return Object::operator_equal(other);
}

void BoolObject::operator_unary_not()
{
	mValue = !mValue.toBool();
}


}
}
