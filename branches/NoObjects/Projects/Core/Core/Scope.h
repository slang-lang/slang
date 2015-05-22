
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

	virtual const std::string& getName() const = 0;
	virtual IScope* getEnclosingScope() const = 0;
	virtual void define(Symbol *symbol) = 0;
	virtual Symbol* resolve(const std::string& name) const = 0;
};


class LocalScope : public IScope
{
public:
	LocalScope(const std::string& name, IScope *parent = 0)
	: mName(name),
	  mParent(parent)
	{ }

	virtual ~LocalScope()
	{
		for ( Symbols::iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
			if ( it->second ) {
				delete it->second;
				it->second = 0;
			}
		}
		mSymbols.clear();
	}

public:	// IScope implementation
	const std::string& getName() const {
		return mName;
	}

	IScope* getEnclosingScope() const {
		if ( mParent ) {
			return mParent;
		}

		return 0;
	}

	void define(Symbol *symbol) {
		if ( mSymbols.find(symbol->getName()) != mSymbols.end() ) {
			// duplicate symbol defined
		}

		mSymbols.insert(std::make_pair(
			symbol->getName(), symbol
		));
	}

	Symbol* resolve(const std::string& name) const {
		Symbols::const_iterator it = mSymbols.find(name);
		if ( it != mSymbols.end() ) {
			return it->second;
		}

		if ( mParent ) {
			return mParent->resolve(name);
		}

		return 0;
	}

protected:

private:
	std::string mName;
	IScope *mParent;
	Symbols mSymbols;
};


class GlobalScope : public LocalScope
{
public:
	GlobalScope()
	: LocalScope("global", 0)
	{ }
	~GlobalScope()
	{ }
};


}


#endif
