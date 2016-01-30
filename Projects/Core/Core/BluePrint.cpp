
// Header
#include "BluePrint.h"

// Library includes
#include <cassert>

// Project includes
#include "Consts.h"
#include "Object.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrint::BluePrint()
: MethodScope(ANONYMOUS_OBJECT, 0),
  BluePrintSymbol(ANONYMOUS_OBJECT),
  RTTI(ANONYMOUS_OBJECT, ANONYMOUS_OBJECT),
  mName(ANONYMOUS_OBJECT),
  mVisibility(Visibility::Public)
{
}

BluePrint::BluePrint(const std::string& type, const std::string& filename, const std::string& name)
: MethodScope(type, 0),
  BluePrintSymbol(type),
  RTTI(type, filename),
  mName(name),
  mVisibility(Visibility::Public)
{
}

BluePrint::~BluePrint()
{
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

const std::string& BluePrint::getFullyQualifiedName() const
{
	return mFullyQualifiedName;
}

void BluePrint::setFullyQualifiedName(const std::string& name)
{
	mFullyQualifiedName = name;
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

void BluePrint::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}

void BluePrint::setVisibility(Visibility::E v)
{
	mVisibility = v;
}


}
}
