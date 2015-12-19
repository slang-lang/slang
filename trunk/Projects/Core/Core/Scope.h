
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

	virtual void define(Symbol *symbol) = 0;
	virtual const std::string& getName() const = 0;
	virtual IScope* getEnclosingScope() const = 0;
	virtual Symbol* resolve(const std::string& name) const = 0;
};


class LocalScope : public IScope
{
public:
	LocalScope(const std::string& name, IScope *parent = 0);
	virtual ~LocalScope();

public:	// IScope implementation
	void define(Symbol *symbol);
	const std::string& getName() const;
	IScope* getEnclosingScope() const;
	Symbol* resolve(const std::string& name) const;

protected:
	std::string mName;

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
