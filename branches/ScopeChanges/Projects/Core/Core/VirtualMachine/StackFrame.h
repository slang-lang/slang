
#ifndef ObjectiveScript_Core_VirtualMachine_StackFrame_h
#define ObjectiveScript_Core_VirtualMachine_StackFrame_h


// Library includes
#include <string>
#include <vector>

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Object.h>
#include <Core/Parameter.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

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

	class StackItem
	{
	public:
		StackItem()
		: mItem(NULL)
		{ }

	public:
		IScope* mItem;
		std::string mName;
	};
	typedef std::vector<StackItem> CurrentStack;

public:
	StackFrame(unsigned long level, IScope* scope, const ParameterList& params);
	~StackFrame();

public:
	bool allowBreakAndContinue() const;

	Runtime::Object& returnValue();

	IScope* getScope() const;
	void popScope();
	void pushScope(IScope* scope, bool allowDelete, bool allowBreakAndContinue);

	size_t lookup(const std::string& name) const;
	IScope* peek(size_t index = size_t(-1)) const;
	size_t pushIdentifier(IScope* symbol, const std::string& name = "");
	void popStack();
	void pushStack();

	const TokenList& getTokens() const;
	void popTokens();
	void pushTokens(const TokenList& tokens);

	std::string toString() const;

private:
	void operator=(const StackFrame&)/* = delete*/;

private:
	CurrentStack mCurrentStack;
	unsigned int mLevel;
	ParameterList mParameters;
	Runtime::Object mReturnValue;
	IScope* mScope;
	Scopes mScopeStack;
	TokenStack mTokenStack;
};



}


#endif
