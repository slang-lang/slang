
// Header
#include "PrototypeConstraint.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


PrototypeConstraint::PrototypeConstraint(unsigned int index, const std::string& designType, const std::string& runType, const std::string& constraint)
: mConstraint(constraint),
  mDesignType(designType),
  mIndex(index),
  mRunType(runType)
{
}

bool PrototypeConstraint::operator==(const PrototypeConstraint& other) const
{
	return mIndex == other.mIndex && mDesignType == mDesignType /*&& mRunType == other.mRunType*/;
}

bool PrototypeConstraint::typeHasBeenResolved() const
{
	return !mRunType.empty();
}


}
