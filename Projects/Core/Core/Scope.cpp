
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


SymbolScope::SymbolScope(const std::string& name, IScope *parent)
: mParent(parent),
  mScopeName(name)
{
}

SymbolScope::~SymbolScope()
{
}

void SymbolScope::define(const std::string& name, Symbol *symbol)
{
	assert(symbol);

	if ( resolve(name, true) ) {
		// duplicate symbol defined
		throw Utils::Exceptions::DuplicateIdentifer("duplicate identifier defined: " + symbol->getName());
	}

	mSymbols.insert(std::make_pair(
		name, symbol
	));
}

IScope* SymbolScope::getEnclosingScope() const
{
	if ( mParent ) {
		return mParent;
	}

	return 0;
}

std::string SymbolScope::getFullName() const
{
	std::string scope;
	if ( mParent ) {
		scope = mParent->getFullName() + RESERVED_WORD_SCOPE_OPERATOR;
	}

	return scope + getScopeName();
}

const std::string& SymbolScope::getScopeName() const
{
	return mScopeName;
}

Symbol* SymbolScope::resolve(const std::string& name, bool onlyCurrentScope) const
{
	Symbols::const_iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		return it->second;
	}

	if ( mParent && !onlyCurrentScope ) {
		return mParent->resolve(name, onlyCurrentScope);
	}

	return 0;
}

void SymbolScope::undefine(const std::string& name, Symbol *symbol)
{
	Symbols::const_iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		mSymbols.erase(it);
	}
	else if ( mParent ) {
		return mParent->undefine(name, symbol);
	}
}



MethodScope::MethodScope(const std::string& name, IScope *parent)
: SymbolScope(name, parent)
{
}

MethodScope::~MethodScope()
{
}

void MethodScope::defineMethod(const std::string& name, Runtime::Method* method)
{
	assert(method);

	if ( MethodScope::resolveMethod(name, method->provideSignature(), true) ) {
		// duplicate method defined
		throw Utils::Exceptions::DuplicateIdentifer("duplicate method '" + method->getName() + "' added with same signature");
	}

	Symbols::iterator it = mSymbols.find(name);
	if ( it == mSymbols.end() ) {
		// define new symbol
		SymbolScope::define(name, method);
	}
	else {
		// override existing symbol
		it->second = method;
	}

	mMethods.insert(method);
}

MethodSymbol* MethodScope::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const
{
	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		Runtime::Method *method = (*it);

		if ( method->getName() == name && method->isSignatureValid(params) ) {
			return method;
		}
	}

	if ( mParent && !onlyCurrentScope ) {
		return static_cast<MethodScope*>(mParent)->resolveMethod(name, params, onlyCurrentScope);
	}

	return 0;
}

void MethodScope::undefineMethod(Runtime::Method* method)
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
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		undefine((*it)->getName(), (*it));

		delete (*it);
	}
	mMethods.clear();

	for ( Symbols::reverse_iterator it = mSymbols.rbegin(); it != mSymbols.rend(); ) {
		undefine(it->first, it->second);
	}
	mSymbols.clear();
}


}
