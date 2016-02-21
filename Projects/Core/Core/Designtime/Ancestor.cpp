
// Header
#include "Ancestor.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


Ancestor::Ancestor()
: mName(""),
  mType(Type::Unknown),
  mVisibility(Visibility::Private)
{
}

Ancestor::Ancestor(const std::string& name, Type::E type, Visibility::E visibility)
: mName(name),
  mType(type),
  mVisibility(visibility)
{
}

const std::string& Ancestor::name() const
{
	return mName;
}

Ancestor::Type::E Ancestor::type() const
{
	return mType;
}

Visibility::E Ancestor::visibility() const
{
	return mVisibility;
}


}
}
