
#ifndef Slang_slang_pkg_Restriction_h
#define Slang_slang_pkg_Restriction_h


// Library includes
#include <set>
#include <string>
#include <utility>

// Project includes
#include "Version.h"

// Forward declarations

// Namespace declarations


class Restriction
{
public:
	Restriction(std::string module, SemanticVersionNumber version_min, SemanticVersionNumber version_max)
	: mMaxVersion(std::move(version_max)),
	  mMinVersion(std::move(version_min)),
	  mModule(std::move(module))
	{ }

	Restriction(std::string module, const std::string& version_min, const std::string& version_max)
	: mMaxVersion(SemanticVersionNumber(version_max)),
	  mMinVersion(SemanticVersionNumber(version_min)),
	  mModule(std::move(module))
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
