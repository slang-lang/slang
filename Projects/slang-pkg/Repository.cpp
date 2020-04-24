
// Header
#include "Repository.h"

// Library includes
#include <fstream>
#include <iostream>
#include <utility>
#include <Json/Json.h>

// Project includes
#include <Tools/Files.h>

// Namespace declarations


Repository::Repository(std::string name)
: mName(std::move(name))
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
	for ( const auto& mModule : mModules ) {
		if ( mModule.mShortName == module.mShortName ) {
			return true;
		}
	}

	return false;
}

bool Repository::getModule(const std::string& shortName, Module& module) const
{
	for ( const auto& mModule : mModules ) {
		if ( mModule.mShortName == shortName ) {
			module = mModule;
			return true;
		}
	}

	return false;
}

const Modules& Repository::getModules() const
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

	for ( const auto& it : modules.members() ) {
		std::string name_short = it["name"].asString();
		std::string source = it.isMember("source") ? it["source"].asString() : mURL;
		std::string version = it["version"].asString();

		Module module(name_short, version, source);

		mModules.insert(module);
	}

	return true;
}

void Repository::setURL(const std::string& url)
{
	mURL = url;
}
