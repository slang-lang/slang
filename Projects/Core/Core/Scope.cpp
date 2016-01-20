
// Header
#include "Scope.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/Utils/Exceptions.h>
#include "Method.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


LocalScope::LocalScope(const std::string& name, IScope *parent)
: mParent(parent),
  mScopeName(name)
{
}

LocalScope::~LocalScope()
{
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



MethodScope::MethodScope(const std::string& name, IScope *parent)
: LocalScope(name, parent)
{
}

MethodScope::~MethodScope()
{
}

void MethodScope::defineMethod(Method* method)
{
	assert(method);

	MethodCollection::iterator tmpIt;
	if ( resolveMethod(method->getName(), method->provideSignature(), true) ) {
		throw Utils::Exceptions::DuplicateIdentifer("duplicate method '" + method->getName() + "' added with same signature");
	}

	Symbols::iterator it = mSymbols.find(method->getName());
	if ( it == mSymbols.end() ) {
		LocalScope::define(method->getName(), method);
	}
	else {
		it->second = method;
	}

	mMethods.insert(method);
}

MethodSymbol* MethodScope::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const
{
	std::string member, parent;
	Tools::split(name, parent, member);

	Symbol *result = LocalScope::resolve(parent, onlyCurrentScope);
	if ( result && result->getType() == Symbol::IType::ObjectSymbol ) {
		return static_cast<Object*>(result)->resolveMethod(member, params);
	}

	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		Method *method = (*it);

		if ( method->getName() == name && method->isSignatureValid(params) ) {
			return method;
		}
	}

	return 0;
}

void MethodScope::undefineMethod(Method* method)
{
	assert(method);

	undefine(method->getName(), method);

	MethodCollection::const_iterator it = mMethods.find(method);
	if ( it != mMethods.end() ) {
		mMethods.erase(it);
	}
}


GlobalScope::GlobalScope()
: MethodScope("global", 0)
{
}
GlobalScope::~GlobalScope()
{
}


}
