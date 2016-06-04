
#ifndef ObjectiveScript_Interfaces_IScope_h
#define ObjectiveScript_Interfaces_IScope_h


// Library includes
#include <string>

// Project includes
#include <Core/Parameter.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


// Forward declarations
namespace Runtime {
    class Method;
}
class MethodSymbol;
class Symbol;


class IScope
{
public:
	class IType {
	public:
		typedef enum {
			MethodScope,
			SymbolScope,
			UnknownScope
		} E;
	};

public:
    virtual ~IScope() { }

    virtual void define(const std::string& name, Symbol *symbol) = 0;
    virtual IScope* getEnclosingScope() const = 0;
    virtual std::string getFullName() const = 0;
    virtual const std::string& getScopeName() const = 0;
	virtual IScope::IType::E getType() const = 0;
    virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope = false) const = 0;
    virtual void undefine(const std::string& name, Symbol *symbol) = 0;
};


class IObjectScope : public IScope
{
public:
    virtual ~IObjectScope() { }

	virtual void defineMethod(const std::string& name, Runtime::Method* method) = 0;
	virtual MethodSymbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const = 0;
	virtual void undefineMethod(Runtime::Method* method) = 0;
};


}


#endif
