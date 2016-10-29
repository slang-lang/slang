
// Header
#include "Parameter.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Parameter::Parameter()
: mAccessMode(AccessMode::Unspecified),
  mHasDefaultValue(false),
  mIsConst(false),
  mPointer(0)
{
}

Parameter::Parameter(const std::string& name, const std::string& type, Runtime::AtomicValue value, bool hasDefaultValue,
					 bool isConst, AccessMode::E access, Reference reference)
: mAccessMode(access),
  mHasDefaultValue(hasDefaultValue),
  mIsConst(isConst),
  mName(name),
  mPointer(0),
  mReference(reference),
  mType(type),
  mValue(value)
{
}

/*
Parameter::Parameter(const std::string& name, const std::string& type, Runtime::AtomicValue value, bool hasDefaultValue,
		 	 	 	 bool isConst, AccessMode::E access, Runtime::Object* pointer)
: mAccessMode(access),
  mHasDefaultValue(hasDefaultValue),
  mIsConst(isConst),
  mName(name),
  mPointer(pointer),
  mType(type),
  mValue(value)
{
}
*/

Parameter::AccessMode::E Parameter::access() const
{
	return mAccessMode;
}

bool Parameter::hasDefaultValue() const
{
	return mHasDefaultValue;
}

bool Parameter::isConst() const
{
	return mIsConst;
}

const std::string& Parameter::name() const
{
	return mName;
}

Runtime::Object* Parameter::pointer() const
{
	return mPointer;
}

const Reference& Parameter::reference() const
{
	return mReference;
}

const std::string& Parameter::type() const
{
	return mType;
}

Runtime::AtomicValue Parameter::value() const
{
	return mValue;
}


}
