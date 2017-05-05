
#ifndef ObjectiveScript_odepend_Dependency_h
#define ObjectiveScript_odepend_Dependency_h


// Library includes
#include <set>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


class Dependency
{
public:
	Dependency(const std::string& module, const std::string& version_min, const std::string& version_max = "")
	: mMaxVersion(version_max),
	  mMinVersion(version_min),
	  mModule(module)
	{ }

public:
	bool operator<(const Dependency& other) const {
		return mModule < other.mModule;
	}

public:
	std::string mMaxVersion;
	std::string mMinVersion;
	std::string mModule;
};

typedef std::set<Dependency> Dependencies;


#endif
