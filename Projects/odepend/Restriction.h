
#ifndef Slang_odepend_Restriction_h
#define Slang_odepend_Restriction_h


// Library includes
#include <set>
#include <string>

// Project includes
#include "Version.h"

// Forward declarations

// Namespace declarations


class Restriction
{
public:
	Restriction(const std::string& module, const SemanticVersionNumber& version_min, const SemanticVersionNumber& version_max)
	: mMaxVersion(version_max),
	  mMinVersion(version_min),
	  mModule(module)
	{ }

	Restriction(const std::string& module, const std::string& version_min, const std::string& version_max)
	: mMaxVersion(SemanticVersionNumber(version_max)),
	  mMinVersion(SemanticVersionNumber(version_min)),
	  mModule(module)
	{ }

public:
	bool operator<(const Restriction& other) const {
		return mModule < other.mModule;
	}

public:
	SemanticVersionNumber mMaxVersion;
	SemanticVersionNumber mMinVersion;
	std::string mModule;
};

typedef std::set<Restriction> Restrictions;


#endif
