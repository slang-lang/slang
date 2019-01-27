
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

Module::Module(const std::string& name_short, const std::string& version)
: mActionNeeded(Action::None),
  mShortName(name_short),
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

bool Module::isValid() const {
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
	mVersion = value["version"].asString();

	if ( value.isMember("target") ) {
		// directory
		if ( value["target"].isMember("directory") ) {
			mTargetDirectory = value["target"]["directory"].asString();
		}

		// URL
		if ( value["target"].isMember("url") ) {
			mURL = value["target"]["url"].asString();
		}
		else {
			mURL = mShortName + "_" + mVersion.toString() + ".tar.gz";
		}
	}
	else {
		mTargetDirectory = value["name_short"].asString();
	}

	return true;
}

std::string Module::toVersionString() const
{
	return mShortName + ":" + mVersion.toString();
}
