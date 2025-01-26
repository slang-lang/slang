
// Header
#include "Version.h"

// Library includes

// Project includes
#include <Tools/Strings.h>

// Namespace declarations


SemanticVersionNumber::SemanticVersionNumber( const std::string& version )
{
	parse( version );
}

SemanticVersionNumber& SemanticVersionNumber::operator=( const std::string& version )
{
	parse( version );

	return *this;
}

bool SemanticVersionNumber::operator==( const SemanticVersionNumber& other ) const
{
	return mMajor == other.mMajor
	    && mMinor == other.mMinor
	    && mBugfix == other.mBugfix
	    && mLabel == other.mLabel
	    && mBuildMetadata == other.mBuildMetadata;
}

bool SemanticVersionNumber::operator==( const std::string& other ) const
{
	return operator==( SemanticVersionNumber( other ) );
}

bool SemanticVersionNumber::operator<( const SemanticVersionNumber& other ) const
{
	if ( mMajor == other.mMajor ) {
		if ( mMinor == other.mMinor ) {
			if ( mBugfix == other.mBugfix ) {
				// Semantic Versioning Specification rule #9
				if ( !mLabel.empty() && !other.mLabel.empty() ) {
					return mLabel < other.mLabel;
				}

				return mLabel.empty();
			}

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

void SemanticVersionNumber::parse( const std::string& version )
{
	mIsValid = false;

	if ( version.empty() ) {
		return;
	}

	std::string bugfix;
	std::string buildMetadata;
	std::string label;
	std::string major;
	std::string minor;
	std::string tmp = version;

	Utils::Tools::splitBy( tmp, '.', major, tmp );
	Utils::Tools::splitBy( tmp, '.', minor, tmp );
	Utils::Tools::splitBy( tmp, '-', bugfix, tmp );
	Utils::Tools::splitBy( tmp, '+', label, buildMetadata );

	mBugfix        = Utils::Tools::stringToInt( bugfix );
	mBuildMetadata = buildMetadata;
	mLabel         = label;
	mMajor         = Utils::Tools::stringToInt( major );
	mMinor         = Utils::Tools::stringToInt( minor );

	mIsValid = mMajor != 0 || mMinor != 0 || mBugfix != 0 || !mLabel.empty();
}

std::string SemanticVersionNumber::toString() const
{
	return Utils::Tools::toString( mMajor ) + "." +
	       Utils::Tools::toString( mMinor ) + "." +
	       Utils::Tools::toString( mBugfix ) +
	       ( !mLabel.empty() ? "-" + mLabel : "" ) +
	       ( !mBuildMetadata.empty() ? "+" + mBuildMetadata : "" );
}
