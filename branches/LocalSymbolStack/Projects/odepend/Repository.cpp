
// Header
#include "Repository.h"

// Library includes
#include <fstream>
#include <iostream>
#include <Json/Json.h>

// Project includes
#include <Tools/Files.h>

// Namespace declarations


Repository::Repository(const std::string& name)
: mName(name)
{
}

Repository::~Repository()
{
}

void Repository::addModule(const Module& module)
{
	if ( contains(module) ) {
		// prevent duplicates
		return;
	}

	mModules.insert(module);
}

bool Repository::contains(const Module& module) const
{
	for ( Modules::const_iterator it = mModules.begin(); it != mModules.end(); ++it ) {
		if ( it->mShortName == module.mShortName ) {
			return true;
		}
	}

	return false;
}

bool Repository::getModule(const std::string& shortName, Module& module) const
{
	for ( Modules::const_iterator it = mModules.begin(); it != mModules.end(); ++it ) {
		if ( it->mShortName == shortName ) {
			module = (*it);
			return true;
		}
	}

	return false;
}

const Repository::Modules& Repository::getModules() const
{
	return mModules;
}

const std::string& Repository::getName() const
{
	return mName;
}

const std::string& Repository::getURL() const
{
	return mURL;
}

bool Repository::processIndex(const Json::Value& value)
{
	if ( !value.isMember("modules") ) {
		return false;
	}

	Json::Value modules = value["modules"];

	for ( Json::Value::Members::const_iterator it = modules.members().begin(); it != modules.members().end(); ++it ) {
		std::string name_short = (*it)["name"].asString();
		std::string version = (*it)["version"].asString();

		Module module(name_short, version);

		mModules.insert(module);
	}

	return true;
}

void Repository::setURL(const std::string& url)
{
	mURL = url;
}