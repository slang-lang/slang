
// Header
#include "PrototypeConstraint.h"

// Library includes

// Project includes
#include <Core/Consts.h>

#include <utility>

// Namespace declarations


namespace Slang {


PrototypeConstraint::PrototypeConstraint()
: mIndex(-1)
{
}

PrototypeConstraint::PrototypeConstraint(size_t index, std::string designType, std::string runType, std::string constraint)
: mConstraint(std::move(constraint)),
  mDesignType(std::move(designType)),
  mIndex(index),
  mRunType(std::move(runType))
{
}

bool PrototypeConstraint::operator==(const PrototypeConstraint& other) const
{
	return mIndex == other.mIndex && mDesignType == /*other.*/ mDesignType /*&& mRunType == other.mRunType*/;
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
		auto thisIt = this->begin();
		for ( auto otherIt = other.begin(); otherIt != other.end(); ++otherIt, ++thisIt ) {
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

	auto otherIt = other.begin();
	auto thisIt = this->begin();

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
	auto thisIt = this->begin();

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

	for ( const auto& it : other ) {
		if ( !result.empty() ) {
			result += ",";
		}

		result += lookupType(it.mDesignType);
	}

	return "<" + result + ">";
}

bool PrototypeConstraints::hasDesigntimeTypes() const
{
	for ( const auto& it : *this ) {
		if ( !it.hasDesigntimeType() ) {
			return false;
		}
	}

	return true;
}

bool PrototypeConstraints::hasRuntimeTypes() const
{
	for ( const auto& it : *this ) {
		if ( !it.hasRuntimeType() ) {
			return false;
		}
	}

	return true;
}

PrototypeConstraint PrototypeConstraints::lookupConstraint(const std::string &type) const
{
	for ( const auto& it : *this ) {
		if ( it.mDesignType == type ) {
			return it;
		}
	}

	return PrototypeConstraint();
}

const std::string& PrototypeConstraints::lookupType(const std::string& type) const
{
	for ( const auto& it : *this ) {
		if ( it.mDesignType == type ) {
			return it.mRunType;
		}
	}

	return type;
}


}
