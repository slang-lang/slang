
// Header
#include "BluePrint.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/Utils/Exceptions.h>
#include "Consts.h"
#include "Object.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrint::BluePrint()
: MethodScope(ANONYMOUS_OBJECT, 0),
  BluePrintSymbol(ANONYMOUS_OBJECT),
  mFilename(ANONYMOUS_OBJECT),
  mFullyQualifiedTypeName(ANONYMOUS_OBJECT),
  mName(ANONYMOUS_OBJECT),
  mTypename(ANONYMOUS_OBJECT),
  mVisibility(Visibility::Public)
{
}

BluePrint::BluePrint(const std::string& type, const std::string& filename, const std::string& name)
: MethodScope(type, 0),
  BluePrintSymbol(type),
  mFilename(filename),
  mFullyQualifiedTypeName(type),
  mName(name),
  mTypename(type),
  mVisibility(Visibility::Public)
{
}

BluePrint::~BluePrint()
{
}

void BluePrint::addInheritance(const Designtime::Ancestor& inheritance)
{
	if ( inheritance.name().empty() ) {
		throw Utils::Exceptions::Exception("invalid inheritance added");
	}

	mInheritance.insert(inheritance);
}

void BluePrint::cleanup()
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		undefine((*it)->getName(), (*it));

		delete (*it);
	}
	mMethods.clear();

	for ( Symbols::iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
		if ( it->first == KEYWORD_THIS || !it->second ) {
			continue;
		}

		if ( it->second->getType() == Symbol::IType::BluePrintSymbol ) {
			static_cast<BluePrint*>(it->second)->cleanup();
		}

		delete it->second;
	}
	mSymbols.clear();
}

Designtime::Ancestors BluePrint::getAncestors() const
{
	Designtime::Ancestors ancestors;

	for ( Designtime::Ancestors::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->type() == Designtime::Ancestor::Type::Extends ) {
			ancestors.insert((*it));
		}
	}

	return ancestors;
}

const std::string& BluePrint::getFullyQualifiedTypename() const
{
	return mFullyQualifiedTypeName;
}

Designtime::Ancestors BluePrint::getImplementations() const
{
	Designtime::Ancestors implementations;

	for ( Designtime::Ancestors::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->type() == Designtime::Ancestor::Type::Implements ) {
			implementations.insert((*it));
		}
	}

	return implementations;
}

const std::string& BluePrint::getName() const
{
	return mName;
}

const TokenList& BluePrint::getTokens() const
{
	return mTokens;
}

Visibility::E BluePrint::getVisibility() const
{
	return mVisibility;
}

bool BluePrint::isAbstract() const
{
	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->isAbstract() ) {
			return true;
		}
	}

	return false;
}

void BluePrint::setFullyQualifiedTypename(const std::string& name)
{
	mFullyQualifiedTypeName = name;
}

void BluePrint::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}

void BluePrint::setVisibility(Visibility::E v)
{
	mVisibility = v;
}

std::string BluePrint::ToString() const
{
	return Typename() + " " + getName();
}


}
}
