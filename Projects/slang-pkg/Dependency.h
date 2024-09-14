
#ifndef Slang_slang_pkg_Dependency_h
#define Slang_slang_pkg_Dependency_h


// Library includes
#include <set>
#include <string>
#include <utility>

// Project includes

// Forward declarations

// Namespace declarations


class Dependency
{
public:
	Dependency(std::string module, std::string version_min, std::string version_max, std::string source)
	: mMaxVersion(std::move(version_max)),
	  mMinVersion(std::move(version_min)),
	  mModule(std::move(module)),
	  mSource(std::move(source))
	{ }

public:
	bool operator<(const Dependency& other) const {
		return mModule < other.mModule;
	}

public:
	std::string mMaxVersion;
	std::string mMinVersion;
	std::string mModule;
	std::string mSource;
};

typedef std::set<Dependency> Dependencies;


#endif
