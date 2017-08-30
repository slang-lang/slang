
// Header
#include "Version.h"

// Library includes

// Project includes
#include <Tools/Strings.h>

// Namespace declarations


SemanticVersionNumber::SemanticVersionNumber()
: mBugfix(0),
  mIsValid(false),
  mMajor(0),
  mMinor(0)
{
}

SemanticVersionNumber::SemanticVersionNumber(const std::string& version)
: mBugfix(0),
  mIsValid(false),
  mMajor(0),
  mMinor(0)
{
	parse(version);
}

SemanticVersionNumber& SemanticVersionNumber::operator=(const std::string& version)
{
	parse(version);

	return *this;
}

bool SemanticVersionNumber::operator==(const SemanticVersionNumber& other) const
{
	return mMajor == other.mMajor && mMinor == other.mMinor && mBugfix == other.mBugfix;
}

bool SemanticVersionNumber::operator<(const SemanticVersionNumber& other) const
{
	if ( mMajor == other.mMajor ) {
		if ( mMinor == other.mMinor ) {
			return mBugfix < other.mBugfix;
		}

		return mMinor < other.mMinor;
	}

	return mMajor < other.mMajor;
}

bool SemanticVersionNumber::isValid() const
{
	return mIsValid;
}

void SemanticVersionNumber::parse(const std::string& version)
{
	mIsValid = false;

	std::string bugfix;
	std::string major;
	std::string minor;
	std::string tmp;

	Utils::Tools::splitBy(version, '.', major, tmp);
	Utils::Tools::splitBy(tmp, '.', minor, bugfix);

	mMajor = Utils::Tools::stringToInt(major);
	mMinor = Utils::Tools::stringToInt(minor);
	mBugfix = Utils::Tools::stringToInt(bugfix);

	mIsValid = true;
}

std::string SemanticVersionNumber::toString() const
{
	return Utils::Tools::toString(mMajor) + "." + Utils::Tools::toString(mMinor) + "." + Utils::Tools::toString(mBugfix);
}
