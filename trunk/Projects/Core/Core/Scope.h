
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


class LocalScope : public IScope
{
public:
	LocalScope(const std::string& name, IScope *parent = 0);
	virtual ~LocalScope();

public:	// IScope implementation
	virtual void define(const std::string& name, Symbol *symbol);
	virtual IScope* getEnclosingScope() const;
	virtual std::string getFullName() const;
	virtual const std::string& getScopeName() const;
	virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope) const;
	virtual void undefine(const std::string& name, Symbol *symbol);

protected:
	IScope *mParent;
	std::string mScopeName;
	Symbols mSymbols;
};


class ObjectScope : public LocalScope
{
public:
	typedef std::set<Runtime::Method*> MethodCollection;

public:
	ObjectScope(const std::string& name, IScope *parent = 0);
	virtual ~ObjectScope();

public:
	virtual void defineMethod(const std::string& name, Runtime::Method* method);
	virtual MethodSymbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const;
	virtual void undefineMethod(Runtime::Method* method);

protected:
	MethodCollection mMethods;
};


class GlobalScope : public ObjectScope
{
public:
	GlobalScope();
	~GlobalScope();
};


}


#endif
