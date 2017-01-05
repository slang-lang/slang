
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

bool PrototypeConstraint::hasRuntimeType() const
{
	return !mRunType.empty();
}


std::string PrototypeConstraints::extractTypes(const std::list<PrototypeConstraint>& other) const
{
	std::string result;

	for ( std::list<PrototypeConstraint>::const_iterator it = other.begin(); it != other.end(); ++it ) {
		if ( result.size() ) {
			result += ",";
		}

		result += lookupType((*it).mDesignType);
	}

	return "<" + result + ">";
}

bool PrototypeConstraints::hasRuntimeTypes() const
{
	for ( std::list<PrototypeConstraint>::const_iterator it = this->begin(); it != this->end(); ++it ) {
		if ( !(*it).hasRuntimeType() ) {
			return false;
		}
	}

	return true;
}

const std::string& PrototypeConstraints::lookupType(const std::string& type) const
{
	for ( std::list<PrototypeConstraint>::const_iterator it = this->begin(); it != this->end(); ++it ) {
		if ( (*it).mDesignType == type ) {
			return (*it).mRunType;
		}
	}

	return type;
}


}
