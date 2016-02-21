//
// Created by Michael Adelmann on 21/02/16.
//

#ifndef OBJECTIVESCRIPT_ISCOPE_H
#define OBJECTIVESCRIPT_ISCOPE_H


// Library includes

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
    virtual ~IScope() { }

    virtual void define(const std::string& name, Symbol *symbol) = 0;
    virtual IScope* getEnclosingScope() const = 0;
    virtual std::string getFullName() const = 0;
    virtual const std::string& getScopeName() const = 0;
    virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope = false) const = 0;
    virtual void undefine(const std::string& name, Symbol *symbol) = 0;
};


class IObjectScope : public IScope
{
    virtual ~IObjectScope() { }

    virtual MethodSymbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope = false) const;
};


}


#endif //OBJECTIVESCRIPT_ISCOPE_H
