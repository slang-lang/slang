
// Header
#include "Ancestor.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


Ancestor::Ancestor()
: mAncestorType(Type::Unknown),
  mTypeDeclaration("", PrototypeConstraints()),
  mVisibility(Visibility::Private)
{
}

Ancestor::Ancestor(const Common::TypeDeclaration& typeDeclaration, Type::E ancestorType, Visibility::E visibility)
: mAncestorType(ancestorType),
  mTypeDeclaration(typeDeclaration),
  mVisibility(visibility)
{
}

bool Ancestor::operator<(const Ancestor& other) const
{
	if ( ancestorType() == other.ancestorType() ) {
		if ( name() == other.name() ) {
			if ( visibility() == other.visibility() ) {
				return constraints() == other.constraints();
			}

			return visibility() < other.visibility();
		}

		return name() < other.name();
	}

	return ancestorType() < other.ancestorType();
}

bool Ancestor::operator==(const Ancestor& other) const
{
	if ( name() != other.name() ) {
		return false;
	}

	return ancestorType() == other.ancestorType() && visibility() == other.visibility();
}

Ancestor::Type::E Ancestor::ancestorType() const
{
	return mAncestorType;
}

const PrototypeConstraints& Ancestor::constraints() const
{
	return mTypeDeclaration.mConstraints;
}

const std::string& Ancestor::name() const
{
	return mTypeDeclaration.mName;
}

const Common::TypeDeclaration& Ancestor::typeDeclaration() const
{
	return mTypeDeclaration;
}

Visibility::E Ancestor::visibility() const
{
	return mVisibility;
}


}
}
