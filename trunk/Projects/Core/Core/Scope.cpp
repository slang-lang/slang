
// Header
#include "Scope.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/VirtualMachine/Controller.h>
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


SymbolScope::SymbolScope(IScope *parent)
: mParent(parent),
  mScopeType(IType::SymbolScope)
{
}

SymbolScope::~SymbolScope()
{
	deinit();
}

void SymbolScope::define(const std::string& name, Symbol* symbol)
{
	assert(symbol);

	if ( resolve(name, true) ) {
		// duplicate symbol defined
		throw Common::Exceptions::DuplicateIdentifier("duplicate identifier defined: " + symbol->getName());
	}

	mSymbols.insert(std::make_pair(name, symbol));
}

void SymbolScope::deinit()
{
	Symbols tmpSymbols = mSymbols;

	for ( Symbols::iterator symIt = tmpSymbols.begin(); symIt != tmpSymbols.end(); ++symIt ) {
		mSymbols.erase(symIt->first);

		if ( /*symIt->first == "base" ||*/ symIt->first == "this" ) {
			continue;
		}

		delete symIt->second;
	}

	mParent = 0;
}

IScope* SymbolScope::getEnclosingScope() const
{
	return mParent;
}

std::string SymbolScope::getFullScopeName() const
{
	std::string scope;
	if ( mParent ) {
		scope = mParent->getFullScopeName();
		if ( !scope.empty() && !mScopeName.empty() ) {
			scope += RESERVED_WORD_SCOPE_OPERATOR;
		}
	}

	return scope + mScopeName;
}

const std::string& SymbolScope::getScopeName() const
{
	return mScopeName;
}

IScope::IType::E SymbolScope::getScopeType() const
{
	return mScopeType;
}

Symbol* SymbolScope::resolve(const std::string& name, bool onlyCurrentScope, Visibility::E visibility) const
{
	Symbols::const_iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		if ( it->second->getVisibility() >= visibility ) {
			return it->second;
		}
	}

	if ( mParent && !onlyCurrentScope ) {
		return mParent->resolve(name, onlyCurrentScope, visibility);
	}

	return 0;
}

void SymbolScope::undefine(const std::string& name, bool onlyCurrentScope)
{
	Symbols::iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		mSymbols.erase(it);
		return;
	}

	if ( mParent && !onlyCurrentScope ) {
		mParent->undefine(name, onlyCurrentScope);
	}
}


NamedScope::NamedScope(const std::string& name, IScope* parent)
: SymbolScope(parent)
{
	mScopeName = name;
	mScopeType = IType::NamedScope;
}

NamedScope::~NamedScope()
{
}


MethodScope::MethodScope(const std::string& name, IScope* parent)
: mParent(parent),
  mScopeName(name),
  mScopeType(IType::MethodScope)
{
}

MethodScope::~MethodScope()
{
	deinit();
}

SymbolScope::Symbols::const_iterator MethodScope::beginSymbols() const
{
	return mSymbols.begin();
}

MethodScope::MethodCollection::const_iterator MethodScope::beginMethods() const
{
	return mMethods.begin();
}

void MethodScope::define(const std::string& name, Symbol* symbol)
{
	assert(symbol);

	if ( mSymbols.find(name) != mSymbols.end() ) {
		// duplicate symbol defined
		throw Common::Exceptions::DuplicateIdentifier("duplicate identifier defined: " + symbol->getName());
	}

	mSymbols.insert(std::make_pair(name, symbol));
}

void MethodScope::defineMethod(const std::string& name, Common::Method* method)
{
	assert(method);

	if ( MethodScope::resolveMethod(name, method->provideSignature(), true) ) {
		// duplicate method defined
		throw Common::Exceptions::DuplicateIdentifier("duplicate method '" + method->getName() + "' added with same signature");
	}

	mMethods.insert(method);
}

void MethodScope::deinit()
{
	MethodCollection tmpMethods = mMethods;

	for ( MethodCollection::iterator methIt = tmpMethods.begin(); methIt != tmpMethods.end(); ++methIt ) {
		mMethods.erase((*methIt));
		delete (*methIt);
	}

	Symbols tmpSymbols = mSymbols;

	for ( Symbols::iterator symIt = tmpSymbols.begin(); symIt != tmpSymbols.end(); ++symIt ) {
		mSymbols.erase(symIt->first);

		if ( /*symIt->first == "base" ||*/ symIt->first == "this" ) {
			continue;
		}

		delete symIt->second;
	}

	mParent = 0;
}

MethodScope::MethodCollection::const_iterator MethodScope::endMethods() const
{
	return mMethods.end();
}

SymbolScope::Symbols::const_iterator MethodScope::endSymbols() const
{
	return mSymbols.end();
}

IScope* MethodScope::getEnclosingScope() const
{
	return mParent;
}

std::string MethodScope::getFullScopeName() const
{
	std::string scope;
	if ( mParent ) {
		scope = mParent->getFullScopeName();
		if ( !scope.empty() && !mScopeName.empty() ) {
			scope += RESERVED_WORD_SCOPE_OPERATOR;
		}
	}

	return scope + mScopeName;
}

const std::string& MethodScope::getScopeName() const
{
	return mScopeName;
}

IScope::IType::E MethodScope::getScopeType() const
{
	return mScopeType;
}

Symbol* MethodScope::resolve(const std::string& name, bool onlyCurrentScope, Visibility::E visibility) const
{
	Symbols::const_iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		if ( it->second->getVisibility() >= visibility ) {
			return it->second;
		}
	}

	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		Common::Method *method = (*it);

		if ( method->getVisibility() >= visibility ) {
			if ( method->getName() == name ) {
				return method;
			}
		}
	}

	if ( mParent && !onlyCurrentScope ) {
		return mParent->resolve(name, onlyCurrentScope, visibility);
	}

	return 0;
}

MethodSymbol* MethodScope::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope, Visibility::E visibility) const
{
	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		Common::Method *method = (*it);

		if ( method->getVisibility() >= visibility ) {
			if ( method->getName() == name && method->isSignatureValid(params) ) {
				return method;
			}
		}
	}

	if ( mParent && !onlyCurrentScope ) {
		return dynamic_cast<MethodScope*>(mParent)->resolveMethod(name, params, onlyCurrentScope, visibility);
	}

	return 0;
}

void MethodScope::undefine(const std::string& name, bool onlyCurrentScope)
{
	Symbols::iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		mSymbols.erase(it);
		return;
	}

	if ( mParent && !onlyCurrentScope ) {
		mParent->undefine(name, onlyCurrentScope);
	}
}

void MethodScope::undefineMethod(Common::Method* method)
{
	assert(method);

	undefine(method->getName());

	MethodCollection::const_iterator it = mMethods.find(method);
	if ( it != mMethods.end() ) {
		mMethods.erase(it);
	}
}


}
