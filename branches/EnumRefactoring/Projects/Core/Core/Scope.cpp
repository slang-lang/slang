
// Header
#include "Scope.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/BluePrintEnum.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/VirtualMachine/Controller.h>
#include <Utils.h>
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
	if ( !symbol ) {
		throw Common::Exceptions::Exception("invalid symbol pointer provided");
	}

	if ( resolve(name, true, Visibility::Designtime) ) {
		// duplicate symbol defined
		throw Common::Exceptions::DuplicateIdentifier("duplicate identifier defined: " + symbol->getName());
	}

	mSymbols.insert(std::make_pair(name, symbol));
}

void SymbolScope::defineExternal(const std::string &name, Symbol *symbol)
{
	if ( !symbol ) {
		throw Common::Exceptions::Exception("invalid symbol pointer provided");
	}

	Symbols::iterator symIt = mExternalSymbols.find(name);
	if ( symIt != mExternalSymbols.end() ) {
		// duplicate symbol defined
		throw Common::Exceptions::DuplicateIdentifier("duplicate identifier defined: " + symbol->getName());
	}

	mExternalSymbols.insert(std::make_pair(name, symbol));
}

void SymbolScope::deinit()
{
	Symbols tmpSymbols = mSymbols;

	for ( Symbols::iterator symIt = tmpSymbols.begin(); symIt != tmpSymbols.end(); ++symIt ) {
		mSymbols.erase(symIt->first);

		if ( symIt->first == IDENTIFIER_THIS ) {
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
	// look up in local symbols
	Symbols::const_iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		if ( it->second->getVisibility() >= visibility ) {
			return it->second;
		}
	}

	// look up in external symbols
	it = mExternalSymbols.find(name);
	if ( it != mExternalSymbols.end() ) {
		if ( it->second->getVisibility() >= visibility ) {
			return it->second;
		}
	}

	// look up in parent's symbols
	if ( mParent && !onlyCurrentScope ) {
		return mParent->resolve(name, onlyCurrentScope, visibility);
	}

	return 0;
}

void SymbolScope::undefine(const std::string& name)
{
	Symbols::iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		mSymbols.erase(it);
		return;
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
	if ( !symbol ) {
		throw Common::Exceptions::Exception("invalid symbol pointer provided: " + name);
	}

	if ( mSymbols.find(name) != mSymbols.end() ) {
		// duplicate symbol defined
		throw Common::Exceptions::DuplicateIdentifier("duplicate identifier defined: " + name);
	}

	mSymbols.insert(std::make_pair(name, symbol));
}

void MethodScope::defineExternal(const std::string &name, Symbol *symbol)
{
	if ( !symbol ) {
		throw Common::Exceptions::Exception("invalid symbol pointer provided");
	}

	Symbols::const_iterator symIt = mExternalSymbols.find(name);
	if ( symIt != mExternalSymbols.end() ) {
		// duplicate symbol defined
		throw Common::Exceptions::DuplicateIdentifier("duplicate identifier defined: " + symbol->getName());
	}

	mExternalSymbols.insert(std::make_pair(name, symbol));
}

void MethodScope::defineExternalMethod(const std::string& /*name*/, Common::Method* method)
{
	if ( !method ) {
		throw Common::Exceptions::Exception("invalid method pointer provided");
	}

	mExternalMethods.insert(method);
}

void MethodScope::defineMethod(const std::string& name, Common::Method* method)
{
	if ( !method ) {
		throw Common::Exceptions::Exception("invalid method pointer provided");
	}

	if ( MethodScope::resolveMethod(name, method->provideSignature(), true) ) {
		// duplicate method defined
		throw Common::Exceptions::DuplicateIdentifier("duplicate method '" + method->getName() + "(" + toString(method->provideSignature()) + ")' added with same signature");
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

		if ( symIt->first == "base" || symIt->first == "this" ) {
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
	// look up in local symbols
	Symbols::const_iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		if ( it->second->getVisibility() >= visibility ) {
			return it->second;
		}
	}

	// look up in external symbols
	it = mExternalSymbols.find(name);
	if ( it != mExternalSymbols.end() ) {
		if ( it->second->getVisibility() >= visibility ) {
			return it->second;
		}
	}

	// look up in local methods
	for ( MethodCollection::const_iterator methodIt = mMethods.begin(); methodIt != mMethods.end(); ++methodIt ) {
		Common::Method *method = (*methodIt);

		if ( method->getVisibility() >= visibility ) {
			if ( method->getName() == name ) {
				return method;
			}
		}
	}

	// look up in external methods
	for ( MethodCollection::const_iterator methodIt = mExternalMethods.begin(); methodIt != mExternalMethods.end(); ++methodIt ) {
		Common::Method *method = (*methodIt);

		if ( method->getVisibility() >= visibility ) {
			if ( method->getName() == name ) {
				return method;
			}
		}
	}

	if ( visibility != Visibility::Designtime ) {
		Symbol* base = resolve(IDENTIFIER_BASE, true, Visibility::Designtime);
		if ( base ) {
			Symbol* result = 0;

			switch ( base->getSymbolType() ) {
				case Symbol::IType::BluePrintEnumSymbol: result = static_cast<Designtime::BluePrintEnum*>(base)->resolve(name, true, visibility); break;
				case Symbol::IType::BluePrintObjectSymbol: result = static_cast<Designtime::BluePrintObject*>(base)->resolve(name, true, visibility); break;
				case Symbol::IType::NamespaceSymbol: result = static_cast<Common::Namespace*>(base)->resolve(name, true, visibility); break;
				case Symbol::IType::ObjectSymbol: result = static_cast<Runtime::Object*>(base)->resolve(name, true, visibility); break;
				default: throw Common::Exceptions::Exception("invalid scope type");
			}

			if ( result ) {
				return result;
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

	if ( visibility != Visibility::Designtime ) {
		Symbol* base = resolve(IDENTIFIER_BASE, true, Visibility::Designtime);
		if ( base ) {
			MethodSymbol* result = 0;

			switch ( base->getSymbolType() ) {
				case Symbol::IType::BluePrintEnumSymbol: result = static_cast<Designtime::BluePrintEnum*>(base)->resolveMethod(name, params, true, visibility); break;
				case Symbol::IType::BluePrintObjectSymbol: result = static_cast<Designtime::BluePrintObject*>(base)->resolveMethod(name, params, true, visibility); break;
				case Symbol::IType::NamespaceSymbol: result = static_cast<Common::Namespace*>(base)->resolveMethod(name, params, true, visibility); break;
				case Symbol::IType::ObjectSymbol: result = static_cast<Runtime::Object*>(base)->resolveMethod(name, params, true, visibility); break;
				default: throw Common::Exceptions::Exception("invalid scope type");
			}

			if ( result ) {
				return result;
			}
		}
	}

	if ( mParent && !onlyCurrentScope ) {
		return dynamic_cast<MethodScope*>(mParent)->resolveMethod(name, params, onlyCurrentScope, visibility);
	}

	return 0;
}

void MethodScope::undefine(const std::string& name)
{
	Symbols::iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		mSymbols.erase(it);
		return;
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
