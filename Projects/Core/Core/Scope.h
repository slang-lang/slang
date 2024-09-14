
#ifndef Slang_Core_Core_Scope_h
#define Slang_Core_Core_Scope_h


// Defines
#include <Core/Defines.h>

// Library include
#include <map>
#include <set>
#include <string>

// Project includes
#include <Core/Interfaces/IScope.h>
#include "Parameter.h"

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
namespace Common {
	class Method;
}
class Symbol;


class SymbolScope : public IScope
{
public:
	typedef std::map<std::string, Symbol*> Symbols;

public:
	explicit SymbolScope(IScope* parent = nullptr);
	virtual ~SymbolScope();

public:	// IScope implementation
	virtual void define(const std::string& name, Symbol* symbol);
	virtual void defineExternal(const std::string& name, Symbol* symbol);
	virtual IScope* getEnclosingScope() const;
	virtual std::string getFullScopeName() const;
	virtual const std::string& getScopeName() const;
	virtual IScope::IType::E getScopeType() const;
	virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope = false, Visibility::E visibility = Visibility::Designtime) const;
	virtual void undefine(const std::string& name);

protected:
	Symbols mExternalSymbols;
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
	explicit NamedScope(const std::string& name, IScope* parent = nullptr);
};


class MethodScope : public IScope
{
public:
	typedef std::set<Common::Method*> MethodCollection;
	typedef std::map<std::string, Symbol*> Symbols;

public:
	explicit MethodScope(std::string name, IScope* parent = nullptr);
	virtual ~MethodScope();

public:	// IScope implementation
	virtual void define(const std::string& name, Symbol* symbol);
	virtual void defineExternal(const std::string& name, Symbol* symbol);
	virtual IScope* getEnclosingScope() const;
	virtual std::string getFullScopeName() const;
	virtual const std::string& getScopeName() const;
	virtual IScope::IType::E getScopeType() const;
	virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope = false, Visibility::E visibility = Visibility::Designtime) const;
	virtual void undefine(const std::string& name);

public: // MethodScope implementation
	virtual void defineExternalMethod(const std::string& name, Common::Method* method);
	virtual void defineMethod(const std::string& name, Common::Method* method);
	virtual MethodSymbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope = false, Visibility::E visibility = Visibility::Designtime) const;
	virtual void undefineMethod(Common::Method* method);

public:
	MethodCollection::const_iterator beginMethods() const;
	MethodCollection::const_iterator endMethods() const;

	Symbols::const_iterator beginSymbols() const;
	Symbols::const_iterator endSymbols() const;

protected:
	virtual void deinit();

protected:
	Symbols mExternalSymbols;
	MethodCollection mExternalMethods;
	MethodCollection mMethods;
	IScope *mParent;
	std::string mScopeName;
	IType::E mScopeType;
	Symbols mSymbols;
};


}


#endif
