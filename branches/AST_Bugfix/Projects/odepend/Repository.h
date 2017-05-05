
#ifndef ObjectiveScript_odepend_Repository_h
#define ObjectiveScript_odepend_Repository_h


// Library includes
#include <set>
#include <string>

// Project includes
#include <Json/Value.h>
#include "Module.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Repository
{
public:
	typedef std::set<Module> Modules;

public:
	Repository(const std::string& name);
	~Repository();

public:
	const Modules& getModules() const;

	const std::string& getName() const;

	const std::string& getURL() const;
	void setURL(const std::string& url);

	bool processIndex(const Json::Value &value);

private:
	std::string getLocalVersion(const std::string& name_short) const;

private:
	Modules mModules;
	std::string mName;
	std::string mURL;
};


}


#endif
