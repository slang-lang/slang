
#ifndef Slang_Core_Core_VirtualMachine_StackFrame_h
#define Slang_Core_Core_VirtualMachine_StackFrame_h


// Library includes
#include <string>

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Object.h>
#include <Core/Parameter.h>

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
class IScope;

class StackFrame
{
public:
	class Scope
	{
	public:
		Scope(IScope* scope, bool allowDelete, bool allowBreakAndContinue);

	public:
		bool mAllowBreakAndContinue;
		bool mAllowDelete;
		IScope* mScope;
	};
	typedef std::list<Scope> Scopes;

public:
	StackFrame(unsigned long level, IScope* scope, ParameterList params);
	~StackFrame();

public:
	bool allowBreakAndContinue() const;

	Runtime::Object& returnValue();

	IScope* getScope() const;
	void popScope();
	void pushScope(IScope* scope, bool allowDelete, bool allowBreakAndContinue);

	const TokenList& getTokens() const;
	void popTokens();
	void pushTokens(const TokenList& tokens);

	std::string toString() const;

private:
	void operator=(const StackFrame&)/* = delete*/;

private:
	unsigned int mLevel;
	ParameterList mParameters;
	Runtime::Object mReturnValue;
	IScope* mScope;
	Scopes mScopeStack;
	TokenStack mTokenStack;
};



}


#endif
