
// Header
#include "AExtension.h"

// Library includes
#include <cassert>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


AExtension::AExtension(const std::string& name)
: mInitialized(false),
  mName(name)
{
}

AExtension::~AExtension()
{
}

const std::string& AExtension::getName() const
{
	return mName;
}

void AExtension::initialize(IScope* scope)
{
(void)scope;

	mInitialized = true;
}

void AExtension::provideMethods(ExtensionMethods& /*methods*/)
{
}

}
}
