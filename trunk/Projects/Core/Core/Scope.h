
#ifndef ObjectiveScript_Scope_h
#define ObjectiveScript_Scope_h


// Library include
#include <set>
#include <string>

// Project includes
#include <Core/Interfaces/IScope.h>
#include "Parameter.h"
#include "Symbol.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class SymbolScope : public IScope
{
public:
	SymbolScope(const std::string& name, IScope *parent = 0);
	virtual ~SymbolScope();

public:	// IScope implementation
	virtual void define(const std::string& name, Symbol *symbol);
	virtual IScope* getEnclosingScope() const;
	virtual std::string getFullName() const;
	virtual std::string getFullScopeName() const;
	virtual const std::string& getScopeName() const;
	virtual IScope::IType::E getType() const;
	virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope = false) const;
	virtual void undefine(const std::string& name, Symbol *symbol);

protected:
	IScope *mParent;
	std::string mScopeName;
	IType::E mScopeType;
	Symbols mSymbols;
};


class MethodScope : public SymbolScope
{
public:
	typedef std::set<Runtime::Method*> MethodCollection;

public:
	MethodScope(const std::string& name, IScope *parent = 0);
	virtual ~MethodScope();

public:
	virtual void defineMethod(const std::string& name, Runtime::Method* method);
	virtual MethodSymbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope = false) const;
	virtual void undefineMethod(Runtime::Method* method);

protected:
	MethodCollection mMethods;
};


class GlobalScope : public MethodScope
{
public:
	GlobalScope();
	~GlobalScope();

public:
	std::string ToString() const;
};


}


#endif
