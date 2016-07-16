
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


AtomicValue StringObject::DEFAULTVALUE = "";
std::string StringObject::TYPENAME = "string";


StringObject::StringObject(AtomicValue value)
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, value.toStdString())
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

	if ( source == BoolObject::TYPENAME ) {
		mValue = Tools::toString(other.getValue().toBool());
	}
	else if ( source == StringObject::TYPENAME ||
			  source == DoubleObject::TYPENAME ||
			  source == FloatObject::TYPENAME ||
			  source == IntegerObject::TYPENAME ||
			  source == NumberObject::TYPENAME ) {
		mValue = other.getValue().toStdString();
	}
	else {
		Object::operator_assign(&other);
	}
}

bool StringObject::isValid() const
{
	return mIsConstructed;
}

void StringObject::operator_assign(const Object *other)
{
	std::string target = other->Typename();

	if ( target == StringObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = other->getValue().toStdString();
	}
	else {
		Object::operator_assign(other);
	}
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
	std::string target = other->Typename();

	if ( target == StringObject::TYPENAME ) {
		return mValue.toStdString() == other->getValue().toStdString();
	}

	return Object::operator_equal(other);
}

bool StringObject::operator_equal(const StringObject *other)
{
	return mValue.toStdString() == other->getValue().toStdString();
}

void StringObject::operator_plus(const Object *other)
{
	std::string target = other->Typename();

	if ( target == StringObject::TYPENAME ||
		 target == BoolObject::TYPENAME ||
		 target == DoubleObject::TYPENAME ||
		 target == FloatObject::TYPENAME ||
		 target == IntegerObject::TYPENAME ||
		 target == NumberObject::TYPENAME ) {
		mValue = mValue.toStdString() + other->getValue().toStdString();
	}
	else {
		Object::operator_plus(other);
	}
}

void StringObject::operator_plus(const StringObject *other)
{
	mValue = mValue.toStdString() + other->getValue().toStdString();
}

std::string StringObject::ToString() const
{
	std::string result;
	result += Visibility::convert(mVisibility);
//	result += " " + LanguageFeatureState::convert(mLanguageFeatureState);
	result += " " + Typename() + " " + getName();
//	result += " " + Mutability::convert(mMutability);
	result += " = \"" + getValue().toStdString() + "\"";

	return result;
}


}
}
