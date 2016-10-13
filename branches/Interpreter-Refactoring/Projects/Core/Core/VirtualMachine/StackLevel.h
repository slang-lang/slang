
#ifndef ObjectiveScript_Core_VirtualMachine_StackLevel_h
#define ObjectiveScript_Core_VirtualMachine_StackLevel_h


// Library includes
#include <string>

// Project includes
#include <Core/Parameter.h>
#include <Core/Token.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IScope;
namespace Runtime {
	class Method;
}


typedef std::list<IScope*> ScopeStack;


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
	StackLevel(unsigned long level, Runtime::Method* method, const ParameterList& params);

public:
	Runtime::Method* getMethod() const;

	const ParameterList& getParameters() const;

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
	Runtime::Method* mMethod;
	ParameterList mParameters;
	Scopes mScopeStack;
	TokenStack mTokenStack;
};



}


#endif
