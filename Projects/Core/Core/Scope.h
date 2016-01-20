
#ifndef ObjectiveScript_Scope_h
#define ObjectiveScript_Scope_h


// Library include
#include <set>
#include <string>

// Project includes
#include "Parameter.h"
#include "Symbol.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Runtime {
	class Method;
}

class IScope
{
public:
	virtual ~IScope() { }

	virtual void define(const std::string& name, Symbol *symbol) = 0;
	virtual IScope* getEnclosingScope() const = 0;
	virtual const std::string& getScopeName() const = 0;
	virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope = false) const = 0;
	virtual void undefine(const std::string& name, Symbol *symbol) = 0;
};


class LocalScope : public IScope
{
public:
	LocalScope(const std::string& name, IScope *parent = 0);
	virtual ~LocalScope();

public:	// IScope implementation
	virtual void define(const std::string& name, Symbol *symbol);
	virtual IScope* getEnclosingScope() const;
	virtual const std::string& getScopeName() const;
	virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope = false) const;
	virtual void undefine(const std::string& name, Symbol *symbol);

protected:
	IScope *mParent;
	std::string mScopeName;
	Symbols mSymbols;

private:

};


class MethodScope : public LocalScope
{
public:
	typedef std::set<Runtime::Method*> MethodCollection;

public:
	MethodScope(const std::string& name, IScope *parent = 0);
	virtual ~MethodScope();

public:
	virtual void defineMethod(Runtime::Method* method);
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
};


}


#endif
