
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

	if ( resolve(name, true) ) {
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

std::string LocalScope::getFullName() const
{
	std::string scope;
	if ( mParent ) {
		scope = mParent->getFullName() + RESERVED_WORD_SCOPE_OPERATOR;
	}

	return scope + getScopeName();
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
		return mParent->resolve(name, onlyCurrentScope);
	}

	return 0;
}

void LocalScope::undefine(const std::string& name, Symbol *symbol)
{
	Symbols::const_iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		mSymbols.erase(it);
	}
	else if ( mParent ) {
		return mParent->undefine(name, symbol);
	}
}



ObjectScope::ObjectScope(const std::string& name, IScope *parent)
: LocalScope(name, parent)
{
}

ObjectScope::~ObjectScope()
{
}

void ObjectScope::defineMethod(const std::string& name, Runtime::Method* method)
{
	assert(method);

	if ( ObjectScope::resolveMethod(name, method->provideSignature(), true) ) {
		// duplicate method defined
		throw Utils::Exceptions::DuplicateIdentifer("duplicate method '" + method->getName() + "' added with same signature");
	}

	Symbols::iterator it = mSymbols.find(name);
	if ( it == mSymbols.end() ) {
		// define new symbol
		LocalScope::define(name, method);
	}
	else {
		// override existing symbol
		it->second = method;
	}

	mMethods.insert(method);
}

MethodSymbol* ObjectScope::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const
{
(void)onlyCurrentScope;

	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		Runtime::Method *method = (*it);

		if ( method->getName() == name && method->isSignatureValid(params) ) {
			return method;
		}
	}

/*
	if ( mParent && !onlyCurrentScope ) {
		static_cast<ObjectScope*>(mParent)->resolveMethod(name, params, onlyCurrentScope);
	}
*/

	return 0;
}

void ObjectScope::undefineMethod(Runtime::Method* method)
{
	assert(method);

	undefine(method->getName(), method);

	MethodCollection::const_iterator it = mMethods.find(method);
	if ( it != mMethods.end() ) {
		mMethods.erase(it);
	}
}


GlobalScope::GlobalScope()
: ObjectScope("global", 0)
{
}
GlobalScope::~GlobalScope()
{
}


}
