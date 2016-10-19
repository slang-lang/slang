
// Header
#include "BluePrintEnum.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Object.h>
#include <Core/Common/Exceptions.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintEnum::BluePrintEnum()
: MethodScope(ANONYMOUS_OBJECT, 0),
  mVisibility(Visibility::Public)
{
	mName = ANONYMOUS_OBJECT;
	mType = Symbol::IType::BluePrintEnumSymbol;
}

BluePrintEnum::BluePrintEnum(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  MethodScope(type, 0),
  mVisibility(Visibility::Public)
{
	mName = name;
	mType = Symbol::IType::BluePrintEnumSymbol;
}

BluePrintEnum::~BluePrintEnum()
{
}

void BluePrintEnum::addInheritance(const Designtime::Ancestor& inheritance)
{
	if ( inheritance.name().empty() ) {
		throw Common::Exceptions::Exception("invalid inheritance added");
	}

	mInheritance.insert(inheritance);
}

Ancestors BluePrintEnum::getAncestors() const
{
	Ancestors ancestors;

	for ( Ancestors::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->type() == Ancestor::Type::Extends ) {
			ancestors.insert((*it));
		}
	}

	return ancestors;
}

Ancestors BluePrintEnum::getInheritance() const
{
	return mInheritance;
}

Ancestors BluePrintEnum::getImplementations() const
{
	Ancestors implementations;

	for ( Ancestors::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->type() == Ancestor::Type::Implements ) {
			implementations.insert((*it));
		}
	}

	return implementations;
}

Visibility::E BluePrintEnum::getVisibility() const
{
	return mVisibility;
}

bool BluePrintEnum::isAbstract() const
{
	return getImplementationType() == ImplementationType::Abstract || getImplementationType() == ImplementationType::Interface;
}

bool BluePrintEnum::isForwardDeclaration() const
{
	return getImplementationType() == ImplementationType::ForwardDeclaration;
}

bool BluePrintEnum::isInterface() const
{
	return getImplementationType() == ImplementationType::Interface;
}

void BluePrintEnum::setParent(IScope* parent)
{
	mParent = parent;
}

void BluePrintEnum::setVisibility(Visibility::E v)
{
	mVisibility = v;
}

std::string BluePrintEnum::ToString(unsigned int indent) const
{
	return ::Utils::Tools::indent(indent) + Typename() + " " + getName();
}



}
}
