
// Header
#include "Scope.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/Common/Exceptions.h>
#include "Method.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


SymbolScope::SymbolScope(const std::string& name, IScope *parent)
: mParent(parent),
  mScopeName(name),
  mScopeType(IType::SymbolScope)
{
}

SymbolScope::~SymbolScope()
{
	mParent = 0;
}

void SymbolScope::define(const std::string& name, Symbol* symbol)
{
	assert(symbol);

	if ( resolve(name, true) ) {
		// duplicate symbol defined
		throw Common::Exceptions::DuplicateIdentifier("duplicate identifier defined: " + symbol->getName());
	}

	mSymbols.insert(std::make_pair(
		name, symbol
	));
}

void SymbolScope::exportSymbols(Symbols& symbols)
{
	symbols = mSymbols;
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

	return scope + getScopeName();
}

const std::string& SymbolScope::getScopeName() const
{
	return mScopeName;
}

IScope::IType::E SymbolScope::getScopeType() const
{
	return mScopeType;
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

void SymbolScope::undefine(const std::string& name, Symbol* /*symbol*/)
{
	Symbols::iterator it = mSymbols.find(name);
	if ( it != mSymbols.end() ) {
		mSymbols.erase(it);
	}
}


MethodScope::MethodScope(const std::string& name, IScope* parent)
: SymbolScope(name, parent)
{
	mScopeType = IType::MethodScope;
}

MethodScope::~MethodScope()
{
}

void MethodScope::defineMethod(const std::string& name, Runtime::Method* method)
{
	assert(method);

	if ( MethodScope::resolveMethod(name, method->provideSignature(), true) ) {
		// duplicate method defined
		throw Common::Exceptions::DuplicateIdentifier("duplicate method '" + method->getName() + "' added with same signature");
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
: MethodScope("", 0)
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
		if ( it->second ) {
			switch ( it->second->getSymbolType() ) {
				case Symbol::IType::NamespaceSymbol:
					delete it->second;
					it->second = 0;
					break;
				default:
					break;
			}
		}

		undefine(it->first, it->second);
	}
	mSymbols.clear();
}

std::string GlobalScope::ToString() const
{
	std::string result = "{\n";

	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		result += "\t" + (*it)->ToString() + "\n";
	}

	for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
		switch ( it->second->getSymbolType() ) {
			case Symbol::IType::BluePrintEnumSymbol:
			case Symbol::IType::BluePrintObjectSymbol:
			case Symbol::IType::MethodSymbol:
			case Symbol::IType::UnknownSymbol:
				continue;
			case Symbol::IType::NamespaceSymbol:
			case Symbol::IType::ObjectSymbol:
				result += "\t" + it->second->ToString() + "\n";
				break;
		}
	}

	result += "}";

	return result;
}


}