
// Header
#include "PrototypeConstraint.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


PrototypeConstraint::PrototypeConstraint(unsigned int index, const std::string& type, const std::string& constraint)
: mConstraint(constraint),
  mIndex(index),
  mType(type)
{
}

bool PrototypeConstraint::operator==(const PrototypeConstraint& other) const
{
	return mConstraint == other.mConstraint && mIndex == other.mIndex && mType == mType;
}


}
