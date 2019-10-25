
// Header
#include "Module.h"

// Library includes
#include <Json/Value.h>

// Project includes

// Namespace declarations


Module::Module()
: mActionNeeded(Action::None)
{
}

Module::Module(const std::string& name_short, const std::string& version, const std::string& source)
: mActionNeeded(Action::None),
  mShortName(name_short),
  mSource(source),
  mVersion(version)
{
}

Module::~Module()
{
}

bool Module::operator<(const Module& other) const
{
	return mShortName < other.mShortName;
}

bool Module::operator==(const Module& other) const
{
	return mShortName == other.mShortName;
}

bool Module::isValid() const
{
	return mVersion.isValid();
}

bool Module::loadFromJson(const Json::Value& value)
{
	if ( value.size() <= 0 ) {
		return false;
	}

	mDescription = value["description"].asString();
	mLongName = value["name"].asString();
	mShortName = value["name_short"].asString();
	mSource = value.isMember("source") ? value["source"].asString() : "";
	mVersion = value["version"].asString();

	if ( value.isMember("dependencies") ) {
		Json::Value dependencies = value["dependencies"];

		for ( Json::Value::Members::const_iterator depIt = dependencies.members().begin(); depIt != dependencies.members().end(); ++depIt ) {
			Json::Value dependency = (*depIt);

			std::string moduleName = dependency["module"].asString();
			std::string source = dependency.isMember("source") ? dependency["source"].asString() : "";
			std::string version_max = dependency.isMember("version_max") ? dependency["version_max"].asString() : "";
			std::string version_min = dependency.isMember("version_min") ? dependency["version_min"].asString() : "";

			mDependencies.insert(
				Dependency(moduleName, version_min, version_max, source)
			);
		}
	}

	// short name is the default value for the target directory
	mTargetDirectory = value["name_short"].asString();

	if ( value.isMember("target") ) {
		// override directory if present
		if ( value["target"].isMember("directory") ) {
			mTargetDirectory = value["target"]["directory"].asString();
		}

		// URL
		if ( value["target"].isMember("url") ) {
			mURL = value["target"]["url"].asString();
		}
	}

	return true;
}

std::string Module::toVersionString() const
{
	return mShortName + ":" + mVersion.toString();
}
