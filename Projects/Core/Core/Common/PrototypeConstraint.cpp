
// Header
#include "PrototypeConstraint.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {


PrototypeConstraint::PrototypeConstraint()
: mIndex((unsigned int)~0)
{
}

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

bool PrototypeConstraint::hasDesigntimeType() const
{
	return !mDesignType.empty();
}

bool PrototypeConstraint::hasRuntimeType() const
{
	return !mRunType.empty();
}


bool PrototypeConstraints::operator==(const PrototypeConstraints& other) const
{
	if ( this->size() == other.size() ) {
		PrototypeConstraints::const_iterator thisIt = this->begin();
		for ( PrototypeConstraints::const_iterator otherIt = other.begin(); otherIt != other.end(); ++otherIt, ++thisIt ) {
			if ( !((*thisIt) == (*otherIt)) ) {
				return false;
			}
		}

		return true;
	}

	return false;
}

PrototypeConstraints PrototypeConstraints::buildRawConstraints(const PrototypeConstraints& other) const
{
	PrototypeConstraints result = other;

	PrototypeConstraints::const_iterator otherIt = other.begin();
	PrototypeConstraints::const_iterator thisIt = this->begin();

	for ( ; thisIt != this->end(); ++thisIt ) {
		if ( otherIt == other.end() ) {
			result.push_back(
				PrototypeConstraint(thisIt->mIndex, thisIt->mDesignType, _object, VALUE_NONE)
			);
			continue;
		}

		++otherIt;
	}

	return result;
}

PrototypeConstraints PrototypeConstraints::buildRuntimeConstraints(const PrototypeConstraints& other) const
{
	PrototypeConstraints result;

	//PrototypeConstraints::const_iterator otherIt = other.begin();
	PrototypeConstraints::const_iterator thisIt = this->begin();

	for ( ; thisIt != this->end(); ++thisIt ) {
		PrototypeConstraint constraint = other.lookupConstraint(thisIt->mDesignType);

		if ( constraint.hasRuntimeType() ) {
			result.push_back(constraint);
		}
		else {
			//result.push_back((*thisIt));
			result.push_back(PrototypeConstraint(thisIt->mIndex, thisIt->mDesignType, _object, VALUE_NONE));
		}
	}

	return result;
}

std::string PrototypeConstraints::extractTypes(const PrototypeConstraints& other) const
{
	std::string result;

	for ( PrototypeConstraints::const_iterator it = other.begin(); it != other.end(); ++it ) {
		if ( result.size() ) {
			result += ",";
		}

		result += lookupType((*it).mDesignType);
	}

	return "<" + result + ">";
}

bool PrototypeConstraints::hasDesigntimeTypes() const
{
	for ( PrototypeConstraints::const_iterator it = this->begin(); it != this->end(); ++it ) {
		if ( !(*it).hasDesigntimeType() ) {
			return false;
		}
	}

	return true;
}

bool PrototypeConstraints::hasRuntimeTypes() const
{
	for ( PrototypeConstraints::const_iterator it = this->begin(); it != this->end(); ++it ) {
		if ( !(*it).hasRuntimeType() ) {
			return false;
		}
	}

	return true;
}

PrototypeConstraint PrototypeConstraints::lookupConstraint(const std::string &type) const
{
	for ( PrototypeConstraints::const_iterator it = this->begin(); it != this->end(); ++it ) {
		if ( (*it).mDesignType == type ) {
			return (*it);
		}
	}

	return PrototypeConstraint();
}

const std::string& PrototypeConstraints::lookupType(const std::string& type) const
{
	for ( PrototypeConstraints::const_iterator it = this->begin(); it != this->end(); ++it ) {
		if ( (*it).mDesignType == type ) {
			return (*it).mRunType;
		}
	}

	return type;
}


}
