
#ifndef ObjectiveScript_Stack_h
#define ObjectiveScript_Stack_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Parameter.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IScope;
class LocalScope;

class Stack
{
public:
	Stack(const std::string& name, const ParameterList& params);
	~Stack();

public:	// Scope
	IScope* pushScope(const std::string& name);
	void popScope();

	void print();

private:
	typedef std::list<LocalScope*> ScopeStack;

private:
	LocalScope* getCurrentScope() const;

private:
	std::string mName;
	ParameterList mParameters;
	ScopeStack mScopeStack;
};

typedef std::list<Stack*> StackList;


class StackTrace
{
public:
	StackTrace();
	~StackTrace();

public:
	void pushStack(const std::string& name, const ParameterList& params);
	void popStack();

	void print();

private:
	StackList mStack;
};


}


#endif
