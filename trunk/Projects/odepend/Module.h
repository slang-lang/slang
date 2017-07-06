
#ifndef ObjectiveScript_odepend_Module_h
#define ObjectiveScript_odepend_Module_h


// Library includes
#include <string>
#include <Json/Value.h>

// Project includes
#include "Dependency.h"
#include "Version.h"

// Forward declarations

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
	Module(const std::string& name_short, const std::string& version);
	~Module();

public:
	bool operator<(const Module& other) const;
	bool operator==(const Module& other) const;

public:
	bool loadFromJson(const Json::Value& value);
	std::string toVersionString() const;

public:
	Action::E mActionNeeded;
	std::string mDescription;
	Dependencies mDependencies;
	std::string mInstalledDirectory;
	std::string mLongName;
	std::string mShortName;
	std::string mTargetDirectory;
	std::string mURL;
	//std::string mVersion;
	SemanticVersionNumber mVersion;
};


#endif
