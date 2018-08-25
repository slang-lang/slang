
// Header
#include "Module.h"

// Library includes

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

bool Module::loadFromJson(const Json::Value& value)
{
	mDescription = value["description"].asString();
	mLongName = value["name"].asString();
	mShortName = value["name_short"].asString();
	mVersion = value["version"].asString();

	if ( value.isMember("target") ) {
		mTargetDirectory = value["target"]["directory"].asString();
	}

	return true;
}

std::string Module::toVersionString() const
{
	return mShortName + ":" + mVersion.toString();
}
