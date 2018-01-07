
// Header
#include "EnumerationObject.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>
#include "BoolObject.h"
#include "DoubleObject.h"
#include "FloatObject.h"
#include "IntegerObject.h"
#include "StringObject.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


AtomicValue EnumerationObject::DEFAULTVALUE = AtomicValue(0);
std::string EnumerationObject::TYPENAME = "enum";


EnumerationObject::EnumerationObject(const std::string& name, const std::string& type, const AtomicValue& value)
: Object(name, SYSTEM_LIBRARY, TYPENAME, value)
{
	mIsAtomicType = true;
	mIsConstructed = true;
	mIsEnumerationValue = true;
	mQualifiedOuterface = type;
	mQualifiedTypename = type;
}

const std::string& EnumerationObject::getTypeName() const
{
	return TYPENAME;
}

bool EnumerationObject::isValid() const
{
	return mIsConstructed;
}

void EnumerationObject::operator_assign(const EnumerationObject *other)
{
	mValue = other->getValue().toInt();
}

void EnumerationObject::operator_assign(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == EnumerationObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		mValue = other->getValue().toInt();
	}
	else {
		Object::operator_assign(other);
	}
}

bool EnumerationObject::operator_bool() const
{
	return mValue.toInt() != 0;
}

bool EnumerationObject::operator_equal(const EnumerationObject *other)
{
	return mValue.toInt() == other->getValue().toInt();
}

bool EnumerationObject::operator_equal(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == EnumerationObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		return mValue.toInt() == other->getValue().toInt();
	}

	return Object::operator_equal(other);
}

bool EnumerationObject::operator_greater(const EnumerationObject *other)
{
	return mValue.toInt() > other->getValue().toInt();
}

bool EnumerationObject::operator_greater(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == EnumerationObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		return mValue.toInt() > other->getValue().toInt();
	}

	return Object::operator_greater(other);
}

bool EnumerationObject::operator_greater_equal(const EnumerationObject *other)
{
	return mValue.toInt() >= other->getValue().toInt();
}

bool EnumerationObject::operator_greater_equal(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == EnumerationObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		return mValue.toInt() >= other->getValue().toInt();
	}

	return Object::operator_greater_equal(other);
}

bool EnumerationObject::operator_less(const EnumerationObject *other)
{
	return mValue.toInt() < other->getValue().toInt();
}

bool EnumerationObject::operator_less(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == EnumerationObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		return mValue.toInt() < other->getValue().toInt();
	}

	return Object::operator_less(other);
}

bool EnumerationObject::operator_less_equal(const EnumerationObject *other)
{
	return mValue.toInt() <= other->getValue().toInt();
}

bool EnumerationObject::operator_less_equal(const Object *other)
{
	std::string target = other->QualifiedTypename();

	if ( target == EnumerationObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ) {
		return mValue.toInt() <= other->getValue().toInt();
	}

	return Object::operator_less_equal(other);
}


}
}
