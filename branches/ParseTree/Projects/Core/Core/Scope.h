
#ifndef ObjectiveScript_Core_Scope_h
#define ObjectiveScript_Core_Scope_h


// Library include
#include <map>
#include <set>
#include <string>
#include <unordered_map>
//#include <unordered_set>

// Project includes
#include <Core/Interfaces/IScope.h>
#include "Parameter.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Common {
	class Method;
}
class Symbol;

class SymbolScope : public IScope
{
public:
	explicit SymbolScope(IScope* parent = 0);
	virtual ~SymbolScope();

public:	// IScope implementation
	virtual void define(const std::string& name, Symbol* symbol);
	virtual IScope* getEnclosingScope() const;
	virtual std::string getFullScopeName() const;
	virtual const std::string& getScopeName() const;
	virtual IScope::IType::E getScopeType() const;
	virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope = false, Visibility::E visibility = Visibility::Designtime) const;
	virtual void undefine(const std::string& name, bool onlyCurrentScope = true);

protected:
	typedef std::map<std::string, Symbol*> Symbols;
	//typedef std::unordered_map<std::string, Symbol*> Symbols;

protected:
	IScope *mParent;
	std::string mScopeName;
	IType::E mScopeType;
	Symbols mSymbols;

private:
	void deinit();
};


class NamedScope : public SymbolScope
{
public:
	NamedScope(const std::string& name, IScope* parent = 0);
	virtual ~NamedScope();

private:
	void deinit();
};


class MethodScope : public NamedScope
{
public:
	typedef std::set<Common::Method*> MethodCollection;
	//typedef std::unordered_set<Common::Method*> MethodCollection;

public:
	MethodScope(const std::string& name, IScope* parent = 0);
	virtual ~MethodScope();

public:
	virtual void defineMethod(const std::string& name, Common::Method* method);
	virtual MethodSymbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope = false, Visibility::E visibility = Visibility::Designtime) const;
	virtual void undefineMethod(Common::Method* method);

protected:
	MethodCollection mMethods;

private:
	void deinit();
};


}


#endif
