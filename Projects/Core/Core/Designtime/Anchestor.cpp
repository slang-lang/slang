
// Header
#include "Anchestor.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


Ancestor::Ancestor()
: mName(""),
  mVisibility(Visibility::Private)
{
}

Ancestor::Ancestor(const std::string& name, Visibility::E visibility)
: mName(name),
  mVisibility(visibility)
{
}

const std::string& Ancestor::name() const
{
	return mName;
}

Visibility::E Ancestor::visibility() const
{
	return mVisibility;
}


}
}
