
#ifndef Slang_slang_pkg_Module_h
#define Slang_slang_pkg_Module_h


// Library includes
#include <set>
#include <string>

// Project includes
#include "Dependency.h"
#include "Version.h"

// Forward declarations
namespace Json {
	class Value;
}

// Namespace declarations


class Module
{
public:
	class Action
	{
	public:
		enum E {
			None,
			Update
		};
	};

public:
	Module();
	Module(std::string name_short, const std::string& version, std::string source);
	~Module() = default;

public:
	bool operator<(const Module& other) const;
	bool operator==(const Module& other) const;

public:
	bool isValid() const;
	bool loadFromJson(const Json::Value& value);
	std::string toVersionString() const;

public:
	Action::E mActionNeeded;
	std::string mDescription;
	Dependencies mDependencies;
	std::string mInstalledDirectory;
	std::string mLongName;
	std::string mShortName;
	std::string mSource;
	std::string mTargetDirectory;
	std::string mURL;
	SemanticVersionNumber mVersion;
};

typedef std::set<Module> Modules;


#endif

