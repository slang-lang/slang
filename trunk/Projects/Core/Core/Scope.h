
#ifndef ObjectiveScript_Scope_h
#define ObjectiveScript_Scope_h


// Library include
#include <string>

// Project includes
#include "Symbol.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class IScope
{
public:
	virtual ~IScope() { }

	virtual void define(const std::string& name, Symbol *symbol) = 0;
	virtual IScope* getEnclosingScope() const = 0;
	virtual const std::string& getScopeName() const = 0;
	virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope = false) const = 0;
};


class LocalScope : public IScope
{
public:
	LocalScope(const std::string& name, IScope *parent = 0);
	virtual ~LocalScope();

public:	// IScope implementation
	void define(const std::string& name, Symbol *symbol);
	IScope* getEnclosingScope() const;
	const std::string& getScopeName() const;
	Symbol* resolve(const std::string& name, bool onlyCurrentScope = false) const;

protected:
	std::string mScopeName;

private:
	IScope *mParent;
	Symbols mSymbols;
};


class GlobalScope : public LocalScope
{
public:
	GlobalScope();
	~GlobalScope();
};


}


#endif
