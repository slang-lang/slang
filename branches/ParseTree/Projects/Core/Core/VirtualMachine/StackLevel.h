
#ifndef ObjectiveScript_Core_VirtualMachine_StackLevel_h
#define ObjectiveScript_Core_VirtualMachine_StackLevel_h


// Library includes
#include <string>

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Parameter.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IScope;

class StackLevel
{
public:
	class Scope
	{
	public:
		Scope(IScope* scope, bool allowDelete);

	public:
		bool mAllowDelete;
		IScope* mScope;
	};
	typedef std::list<Scope> Scopes;

public:
	StackLevel(unsigned long level, IScope* scope, const ParameterList& params);
	~StackLevel();

public:
	IScope* getScope() const;
	void popScope();
	void pushScope(IScope* scope, bool allowDelete);

	const TokenList& getTokens() const;
	void popTokens();
	void pushTokens(const TokenList& tokens);

	std::string toString() const;

private:
	void operator=(const StackLevel&)/* = delete*/;

private:
	unsigned long mLevel;
	ParameterList mParameters;
	IScope* mScope;
	Scopes mScopeStack;
	TokenStack mTokenStack;
};



}


#endif
