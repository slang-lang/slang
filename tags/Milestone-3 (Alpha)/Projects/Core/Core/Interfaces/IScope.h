
#ifndef ObjectiveScript_Interfaces_IScope_h
#define ObjectiveScript_Interfaces_IScope_h


// Library includes
#include <string>

// Project includes
#include <Core/Symbol.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


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
			SymbolScope,
			UnknownScope
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
	virtual ~IScope() { }

	virtual void define(const std::string& name, Symbol* symbol) = 0;
	virtual IScope* getEnclosingScope() const = 0;
	virtual std::string getFullScopeName() const = 0;
	virtual const std::string& getScopeName() const = 0;
	virtual IScope::IType::E getScopeType() const = 0;
	virtual Symbol* resolve(const std::string& name, bool onlyCurrentScope = false, Visibility::E visibility = Visibility::Designtime) const = 0;
	virtual void undefine(const std::string& name, Symbol* symbol) = 0;
};


}


#endif
