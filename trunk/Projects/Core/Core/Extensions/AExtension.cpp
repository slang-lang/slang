
// Header
#include "AExtension.h"

// Library includes
#include <cassert>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


AExtension::AExtension(const std::string& name, const std::string& path)
: mName(name),
  mPath(path)
{
}

AExtension::~AExtension()
{
}

const std::string& AExtension::getName() const
{
	return mName;
}

const std::string& AExtension::getPath() const
{
	return mPath;
}


}
}
