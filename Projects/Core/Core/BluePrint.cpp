
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

void BluePrint::addAnchestor(const std::string& ancestor)
{
	if ( ancestor.empty() ) {
		throw Utils::Exceptions::Exception("invalid ancestor added");
	}

	mAncestors.push_back(ancestor);
}

void BluePrint::addImplementation(const std::string &implementation)
{
	if ( implementation.empty() ) {
		throw Utils::Exceptions::Exception("invalid implemantation added");
	}

	mImplementations.push_back(implementation);
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

const StringList& BluePrint::getAncestors() const
{
	return mAncestors;
}

const std::string& BluePrint::getFullyQualifiedTypename() const
{
	return mFullyQualifiedTypeName;
}

const StringList& BluePrint::getImplementations() const
{
	return mImplementations;
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
