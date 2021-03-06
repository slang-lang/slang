
#ifndef Slang_slang_pkg_Version_h
#define Slang_slang_pkg_Version_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations



/*
 * Represents a comparable version number defined by the defacto versioning standard "semantic versioning"
 */
class SemanticVersionNumber
{
public:
	SemanticVersionNumber();
	explicit SemanticVersionNumber(const std::string& version);

public:
	SemanticVersionNumber& operator=(const std::string& version);
	bool operator==(const SemanticVersionNumber& other) const;
	bool operator==(const std::string& other) const;
	bool operator<(const SemanticVersionNumber& other) const;

public:
	bool isValid() const;
	std::string toString() const;

private:
	void parse(const std::string& version);

private:
	int mBugfix;
	std::string mLabel;
	bool mIsValid;
	int mMajor;
	int mMinor;
};


#endif
