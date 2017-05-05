
// Header
#include "Repository.h"

// Library includes
#include <fstream>
#include <iostream>
#include <Json/Json.h>

// Project includes
#include <Tools/Files.h>

// Namespace declarations


namespace ObjectiveScript {


Repository::Repository(const std::string& name)
: mName(name)
{
}

Repository::~Repository()
{
}

std::string Repository::getLocalVersion(const std::string& name_short) const
{
	std::string filename = "tmp/modules/" + name_short + ".json";

	if ( !::Utils::Tools::Files::exists(filename) ) {
		// no configuration file exists
		return "";
	}

	std::fstream stream;
	stream.open(filename.c_str(), std::ios::in);	// open for reading
	std::string data((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());	// read stream
	stream.close();

	Json::Value config = Json::Parser::parse(data);
	if ( config.isMember("version") ) {
		return config["version"].asString();
	}

	return "";
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

bool Repository::processIndex(const Json::Value &value)
{
	if ( !value.isMember("modules") ) {
		return false;
	}

	Json::Value modules = value["modules"];

	for ( Json::Value::Members::const_iterator it = modules.members().begin(); it != modules.members().end(); ++it ) {
		std::string name_short = (*it)["name"].asString();
		std::string remote_version = (*it)["version"].asString();

		Module module(name_short, remote_version);
		module.mLocalVersion = getLocalVersion(name_short);

		if ( !module.mLocalVersion.empty() ) {
			module.mActionNeeded = module.mLocalVersion < module.mRemoteVersion ? Module::Action::Update : Module::Action::None;
		}

		std::cout << "Module: " << module.mShortName << std::endl;
		std::cout << "Version (remote): " << module.mRemoteVersion << std::endl;
		std::cout << "Version (local): " << module.mLocalVersion << std::endl;

		mModules.insert(module);
	}

	return true;
}

void Repository::setURL(const std::string& url)
{
	mURL = url;
}


}
