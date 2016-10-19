
// Header
#include "BluePrintObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Object.h>
#include <Core/Common/Exceptions.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintObject::BluePrintObject()
: MethodScope(ANONYMOUS_OBJECT, 0),
  mVisibility(Visibility::Public)
{
	mName = ANONYMOUS_OBJECT;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

BluePrintObject::BluePrintObject(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  MethodScope(type, 0),
  mVisibility(Visibility::Public)
{
	mName = name;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

BluePrintObject::~BluePrintObject()
{
}

void BluePrintObject::addInheritance(const Ancestor& inheritance)
{
	if ( inheritance.name().empty() ) {
		throw Common::Exceptions::Exception("invalid inheritance added");
	}

	mInheritance.insert(inheritance);
}

Ancestors BluePrintObject::getAncestors() const
{
	Ancestors ancestors;

	for ( Ancestors::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->type() == Ancestor::Type::Extends ) {
			ancestors.insert((*it));
		}
	}

	return ancestors;
}

Ancestors BluePrintObject::getInheritance() const
{
	return mInheritance;
}

Ancestors BluePrintObject::getImplementations() const
{
	Ancestors implementations;

	for ( Ancestors::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->type() == Ancestor::Type::Implements ) {
			implementations.insert((*it));
		}
	}

	return implementations;
}

Runtime::AtomicValue BluePrintObject::getValue() const
{
	return mValue;
}

Visibility::E BluePrintObject::getVisibility() const
{
	return mVisibility;
}

bool BluePrintObject::isAbstract() const
{
	return getImplementationType() == ImplementationType::Abstract || getImplementationType() == ImplementationType::Interface;
}

bool BluePrintObject::isForwardDeclaration() const
{
	return getImplementationType() == ImplementationType::ForwardDeclaration;
}

bool BluePrintObject::isInterface() const
{
	return getImplementationType() == ImplementationType::Interface;
}

void BluePrintObject::setParent(IScope* parent)
{
	mParent = parent;
}

void BluePrintObject::setValue(Runtime::AtomicValue value)
{
	mValue = value;
}

void BluePrintObject::setVisibility(Visibility::E v)
{
	mVisibility = v;
}

std::string BluePrintObject::ToString(unsigned int indent) const
{
	return ::Utils::Tools::indent(indent) + Typename() + " " + getName();
}


}
}
