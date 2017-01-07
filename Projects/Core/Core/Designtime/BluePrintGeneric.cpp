
// Header
#include "BluePrintGeneric.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintGeneric::BluePrintGeneric()
: BluePrintSymbol(ANONYMOUS_OBJECT),
  mFilename(ANONYMOUS_OBJECT),
  mQualifiedTypename(ANONYMOUS_OBJECT),
  mUnqualifiedTypename(ANONYMOUS_OBJECT)
{
	mVisibility = Visibility::Public;
}

BluePrintGeneric::BluePrintGeneric(const std::string& unqualifiedTypename, const std::string& filename)
: BluePrintSymbol(unqualifiedTypename),
  mFilename(filename),
  mQualifiedTypename(unqualifiedTypename),
  mUnqualifiedTypename(unqualifiedTypename)
{
	mVisibility = Visibility::Public;
}

BluePrintGeneric::~BluePrintGeneric()
{
}

void BluePrintGeneric::addInheritance(const Designtime::Ancestor& inheritance)
{
	if ( inheritance.name().empty() ) {
		throw Common::Exceptions::Exception("invalid inheritance added");
	}

	mInheritance.insert(inheritance);
}

Ancestors BluePrintGeneric::getAncestors() const
{
	Ancestors ancestors;

	for ( Ancestors::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->ancestorType() == Ancestor::Type::Extends ) {
			ancestors.insert((*it));
		}
	}

	return ancestors;
}

Ancestors BluePrintGeneric::getInheritance() const
{
	return mInheritance;
}

Ancestors BluePrintGeneric::getImplementations() const
{
	Ancestors implementations;

	for ( Ancestors::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->ancestorType() == Ancestor::Type::Implements ) {
			implementations.insert((*it));
		}
	}

	return implementations;
}

const PrototypeConstraints& BluePrintGeneric::getPrototypeConstraints() const
{
	return mPrototypeConstraints;
}

const TokenList& BluePrintGeneric::getTokens() const
{
	return mTokens;
}

bool BluePrintGeneric::isAbstract() const
{
	return getImplementationType() == ImplementationType::Abstract || getImplementationType() == ImplementationType::Interface;
}

bool BluePrintGeneric::isForwardDeclaration() const
{
	return getImplementationType() == ImplementationType::ForwardDeclaration;
}

bool BluePrintGeneric::isInterface() const
{
	return getImplementationType() == ImplementationType::Interface;
}

bool BluePrintGeneric::isPrototype() const
{
	return !mPrototypeConstraints.empty();
}

void BluePrintGeneric::setPrototypeConstraints(const PrototypeConstraints& constraints)
{
	mPrototypeConstraints = constraints;
}

void BluePrintGeneric::setQualifiedTypename(const std::string& name)
{
	mQualifiedTypename = name;
}

void BluePrintGeneric::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}


}
}
