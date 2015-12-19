
// Header
#include "Scope.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


LocalScope::LocalScope(const std::string& name, IScope *parent)
: mName(name),
  mParent(parent)
{
}

LocalScope::~LocalScope()
{
	for ( Symbols::iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
		if ( it->second ) {
			delete it->second;
			it->second = 0;
		}
	}
	mSymbols.clear();
}

void LocalScope::define(Symbol *symbol)
{
	if ( mSymbols.find(symbol->getName()) != mSymbols.end() ) {
		// duplicate symbol defined
	}

	mSymbols.insert(std::make_pair(
		symbol->getName(), symbol
	));
}

const std::string& LocalScope::getName() const
{
	return mName;
}

IScope* LocalScope::getEnclosingScope() const
{
	if ( mParent ) {
		return mParent;
	}

	return 0;
}

Symbol* LocalScope::resolve(const std::string& name) const
{
	Symbols::const_iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		return it->second;
	}

	if ( mParent ) {
		return mParent->resolve(name);
	}

	return 0;
}


GlobalScope::GlobalScope()
: LocalScope("global", 0)
{
}

GlobalScope::~GlobalScope()
{
}


}
