
// Header
#include "Scope.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


LocalScope::LocalScope(const std::string& name, IScope *parent)
: mScopeName(name),
  mParent(parent)
{
}

LocalScope::~LocalScope()
{
	for ( Symbols::iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
/*
		Symbol::IType::E type = it->second->getType();

		switch ( type ) {
			case Symbol::IType::UnknownSymbol:
				break;
			case Symbol::IType::BuildInTypeSymbol:
			case Symbol::IType::MemberSymbol:
			case Symbol::IType::MethodSymbol:
			case Symbol::IType::ObjectSymbol:
				break;
		}
*/
/*
		if ( it->second ) {
			delete it->second;
			it->second = 0;
		}
*/
	}
	mSymbols.clear();
}

void LocalScope::define(const std::string& name, Symbol *symbol)
{
	assert(symbol);

	if ( mSymbols.find(name) != mSymbols.end() ) {
		// duplicate symbol defined
		throw Utils::Exceptions::DuplicateIdentifer("duplicate identifier defined: " + symbol->getName());
	}

	mSymbols.insert(std::make_pair(
		name, symbol
	));
}

IScope* LocalScope::getEnclosingScope() const
{
	if ( mParent ) {
		return mParent;
	}

	return 0;
}

const std::string& LocalScope::getScopeName() const
{
	return mScopeName;
}

Symbol* LocalScope::resolve(const std::string& name, bool onlyCurrentScope) const
{
	Symbols::const_iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		return it->second;
	}

	if ( mParent && !onlyCurrentScope ) {
		return mParent->resolve(name);
	}

	return 0;
}

void LocalScope::undefine(const std::string& name, Symbol *symbol)
{
	assert(symbol);

	Symbols::const_iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		mSymbols.erase(it);
	}
}


GlobalScope::GlobalScope()
: LocalScope("global", 0)
{
}

GlobalScope::~GlobalScope()
{
}


}