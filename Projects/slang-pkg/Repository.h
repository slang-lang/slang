
#ifndef Slang_slang_pkg_Repository_h
#define Slang_slang_pkg_Repository_h


// Library includes
#include <string>

// Project includes
#include <Json/Value.h>
#include "Module.h"

// Forward declarations

// Namespace declarations


class Repository
{
public:
	explicit Repository( std::string name = "" );
	~Repository() = default;

public:
	void addModule(const Module& module);
	bool contains(const Module& module) const;
	bool getModule(const std::string& shortName, Module& module) const;

public:
	const Modules& getModules() const;

	const std::string& getName() const;

	const std::string& getURL() const;
	void setURL(const std::string& url);

	bool processIndex(const Json::Value& value);

private:
	Modules mModules;
	std::string mName;
	std::string mURL;
};


#endif
