
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

Ancestor::Ancestor(const std::string& name, Type::E type, Visibility::E visibility, const PrototypeConstraints& constraints)
: mName(name),
  mPrototypeConstraints(constraints),
  mType(type),
  mVisibility(visibility)
{
}

bool Ancestor::operator<(const Ancestor& other) const
{
	if ( type() == other.type() ) {
		if ( name() == other.name() ) {
			if ( visibility() == other.visibility() ) {
				return constraints() == other.constraints();
			}

			return visibility() < other.visibility();
		}

		return name() < other.name();
	}

	return type() < other.type();
}

bool Ancestor::operator==(const Ancestor& other) const
{
	if ( name() != other.name() ) {
		return false;
	}

	return type() == other.type() && visibility() == other.visibility();
}

const PrototypeConstraints& Ancestor::constraints() const
{
	return mPrototypeConstraints;
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
