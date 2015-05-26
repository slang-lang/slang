
// Header
#include "Parameter.h"

// Library includes

// Project includes
#include <Core/Object.h>

// Namespace declarations


namespace ObjectiveScript {


Parameter::Parameter()
: mAccessMode(AccessMode::Unspecified),
  mIsConst(false)
{
}

Parameter::Parameter(const std::string& name, const std::string& type, const std::string& value, bool isConst, AccessMode::E access, Reference reference)
: mAccessMode(access),
  mIsConst(isConst),
  mName(name),
  mReference(reference),
  mType(type),
  mValue(value)
{
}

Parameter::AccessMode::E Parameter::access() const
{
	return mAccessMode;
}

bool Parameter::isConst() const
{
	return mIsConst;
}

const std::string& Parameter::name() const
{
	return mName;
}

const Reference& Parameter::reference() const
{
	return mReference;
}

const std::string& Parameter::type() const
{
	return mType;
}

const std::string& Parameter::value() const
{
	return mValue;
}


}
