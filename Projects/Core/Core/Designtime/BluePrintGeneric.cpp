
// Header
#include "BluePrintGeneric.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>

#include <utility>

// Namespace declarations


namespace Slang {
namespace Designtime {


BluePrintGeneric::BluePrintGeneric()
: BlueprintSymbol(ANONYMOUS_OBJECT),
  mFilename(ANONYMOUS_OBJECT),
  mIsAtomicType(false),
  mQualifiedTypename(ANONYMOUS_OBJECT),
  mUnqualifiedTypename(ANONYMOUS_OBJECT)
{
}

BluePrintGeneric::BluePrintGeneric(const std::string& unqualifiedTypename, std::string filename)
: BlueprintSymbol(unqualifiedTypename),
  mFilename(std::move(filename)),
  mIsAtomicType(false),
  mQualifiedTypename(unqualifiedTypename),
  mUnqualifiedTypename(unqualifiedTypename)
{
}

void BluePrintGeneric::addInheritance(const Designtime::Ancestor& inheritance)
{
	if ( inheritance.name().empty() ) {
		throw Common::Exceptions::Exception("invalid inheritance added");
	}

	mInheritance.insert(inheritance);
}

const std::string& BluePrintGeneric::Filename() const
{
	return mFilename;
}

const std::string& BluePrintGeneric::QualifiedTypename() const
{
	return mQualifiedTypename;
}

Ancestors BluePrintGeneric::getAncestors() const
{
	Ancestors ancestors;

	for ( const auto& it : mInheritance ) {
		if ( it.ancestorType() == Ancestor::Type::Extends ) {
			ancestors.insert(it);
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

	for ( const auto& it : mInheritance ) {
		if ( it.ancestorType() == Ancestor::Type::Implements ) {
			implementations.insert(it);
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

bool BluePrintGeneric::inheritsFrom(const std::string& type) const
{
	for ( const auto& it : mInheritance ) {
		if ( it.name() == type ) {
			return true;
		}
	}

	return false;
}

bool BluePrintGeneric::isAtomicType() const
{
	return mIsAtomicType;
}

bool BluePrintGeneric::isAbstract() const
{
	return mImplementationType == ImplementationType::Abstract || mBluePrintType == BlueprintType::Interface;
}

bool BluePrintGeneric::isInterface() const
{
	return mBluePrintType == BlueprintType::Interface;
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
