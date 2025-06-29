
#ifndef _SemVer_Version_h_
#define _SemVer_Version_h_


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations



/*
 * Represents a comparable version number defined by the defacto versioning standard "semantic versioning"
 * Refer to https://semver.org/ for details about semantic versioning.
 */
class SemanticVersionNumber
{
public:
	SemanticVersionNumber() = default;
	explicit SemanticVersionNumber( const std::string& version );
	SemanticVersionNumber( int major, int minor, int bugfix, std::string label = "", std::string buildMetadata = "" );

public:
	SemanticVersionNumber& operator=( const std::string& version );
	bool operator==( const SemanticVersionNumber& other ) const;
	bool operator==( const std::string& other ) const;
	bool operator!=( const SemanticVersionNumber& other ) const;
	bool operator!=( const std::string& other ) const;
	bool operator<( const SemanticVersionNumber& other ) const;
	bool operator<( const std::string& other ) const;

public:
	bool isValid() const;
	std::string toString() const;

	/*
	 * returns the next bugfix version based on the current version
	 */
	SemanticVersionNumber nextBugfix() const {
		return SemanticVersionNumber( mMajor, mMinor, mBugfix + 1 );
	}

	/*
	 * returns the next major version based on the current version
	 */
	SemanticVersionNumber nextMajor() const {
		return SemanticVersionNumber( mMajor + 1, 0, 0 );
	}

	/*
	 * returns the next minor version based on the current version
	 */
	SemanticVersionNumber nextMinor() const {
		return SemanticVersionNumber( mMajor, mMinor + 1, 0 );
	}

private:
	void parse( std::string version );

private:
	int mBugfix{ 0 };
	std::string mBuildMetadata;
	std::string mLabel;
	bool mIsValid{ false };
	int mMajor{ 0 };
	int mMinor{ 0 };
};


#endif
