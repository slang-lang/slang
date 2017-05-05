
// Header
#include "Module.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Module::Module(const std::string& name_short, const std::string& remote_version)
: mActionNeeded(Action::None),
  mRemoteVersion(remote_version),
  mShortName(name_short)
{
}

Module::~Module()
{
}

bool Module::operator<(const Module& other) const
{
	return mShortName < other.mShortName;
}

const std::string& Module::getURL() const
{
	return mURL;
}

void Module::setURL(const std::string& url)
{
	mURL = url;
}


}
