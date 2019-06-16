
// Header
#include "AExtension.h"

// Library includes
#include <cassert>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


AExtension::AExtension(const std::string& name)
: mName(name)
{
}

AExtension::~AExtension()
{
}

const std::string& AExtension::getName() const
{
	return mName;
}


}
}
