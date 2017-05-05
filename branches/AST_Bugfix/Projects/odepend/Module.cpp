
// Header
#include "Module.h"

// Library includes

// Project includes

// Namespace declarations


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
