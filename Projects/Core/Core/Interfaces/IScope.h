
#ifndef ObjectiveScript_Core_Interfaces_IScope_h
#define ObjectiveScript_Core_Interfaces_IScope_h


// Library includes
#include <string>

// Project includes
#include <Core/Symbol.h>

// Forward declarations

// Namespace declarations


namespace Slang {


// Forward declarations
class Symbol;


class IScope
{
public:
	class IType
	{
	public:
		enum E {
			MethodScope,
			NamedScope,
			SymbolScope
		};
	};

	class IVisibility
	{
	public:
		enum E {
			Public,
			Protected,
			Private,
			All
		};
	};

public:
	virtual ~IScope() = default;

	virtual void define(const std::string& name, Symbol* symbol) = 0;
	virtual void defineExternal(const std::string& name, Symbol* symbol) = 0;
	virtual IScope* getEnclosingScope() const = 0;
	virtual std::string getFullScopeName() const = 0;
	virtual const std::string& getScopeName() const = 0;
	virtual IScope::IType::E getScopeType() const = 0;
	virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope, Visibility::E visibility) const = 0;
	virtual void undefine(const std::string& name) = 0;
};


}


#endif
