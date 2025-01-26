
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

SemanticVersionNumber::SemanticVersionNumber( int major, int minor, int bugfix, std::string label, std::string buildMetadata )
: mBugfix( bugfix )
, mBuildMetadata( buildMetadata )
, mLabel( label )
, mMajor( major )
, mMinor( minor )
{
}

SemanticVersionNumber& SemanticVersionNumber::operator=( const std::string& version )
{
	parse( version );

	return *this;
}

bool SemanticVersionNumber::operator==( const SemanticVersionNumber& other ) const
{
	return mMajor         == other.mMajor
	    && mMinor         == other.mMinor
	    && mBugfix        == other.mBugfix
	    && mLabel         == other.mLabel
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
				if ( mLabel == other.mLabel ) {
					return mBuildMetadata < other.mBuildMetadata;
				}

				return !mLabel.empty();
			}

			return mBugfix < other.mBugfix;
		}

		return mMinor < other.mMinor;
	}

	return mMajor < other.mMajor;
}

bool SemanticVersionNumber::operator<( const std::string& other ) const
{
	return operator<( SemanticVersionNumber( other ) );
}

bool SemanticVersionNumber::isValid() const
{
	return mIsValid;
}

void SemanticVersionNumber::parse( std::string version )
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
	std::string tmp;

	/*
	Utils::Tools::splitBy( version, '.', major, version );
	Utils::Tools::splitBy( version, '.', minor, version );
	Utils::Tools::splitBy( version, '-', bugfix, tmp );
	if ( tmp.empty() ) {
		// no label separator found, try with build metadata separator
		Utils::Tools::splitBy( version, '-', version, label );
	}

	Utils::Tools::splitBy( version, '+', label, buildMetadata );
	*/

	// example: 1.2.3-alpha+001
	// 1 . 2.3-alpha+001
	Utils::Tools::splitBy( version, '.', major, version );
	// 2 . 3-alpha+001
	Utils::Tools::splitBy( version, '.', minor, version );
	// 3-alpha + 001
	Utils::Tools::splitBy( version, '+', label, buildMetadata );
	// 3 - alpha
	Utils::Tools::splitBy( label, '-', bugfix, label );

	mBugfix        = Utils::Tools::stringToInt( bugfix );
	mBuildMetadata = buildMetadata;
	mLabel         = label;
	mMajor         = Utils::Tools::stringToInt( major );
	mMinor         = Utils::Tools::stringToInt( minor );

	mIsValid = mMajor != 0 || mMinor != 0 || mBugfix != 0 || !mLabel.empty() || !mBuildMetadata.empty();
}

std::string SemanticVersionNumber::toString() const
{
	return Utils::Tools::toString( mMajor ) + "." +
	       Utils::Tools::toString( mMinor ) + "." +
	       Utils::Tools::toString( mBugfix ) +
	       ( !mLabel.empty() ? "-" + mLabel : "" ) +
	       ( !mBuildMetadata.empty() ? "+" + mBuildMetadata : "" );
}
