
#ifndef ObjectiveScript_odepend_Module_h
#define ObjectiveScript_odepend_Module_h


// Library includes
#include <string>

// Project includes
#include "Dependency.h"

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
	Module(const std::string& name_short, const std::string& version);
	~Module();

public:
	bool operator<(const Module& other) const;
	bool operator==(const Module& other) const;

public:
	Action::E mActionNeeded;
	std::string mDescription;
	Dependencies mDependencies;
	std::string mInstalledDirectory;
	std::string mLongName;
	std::string mShortName;
	std::string mURL;
	std::string mVersion;
};


#endif
