
#ifndef ObjectiveScript_Core_VirtualMachine_Stack_h
#define ObjectiveScript_Core_VirtualMachine_Stack_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Scope.h>
#include "StackLevel.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Stack
{
public:
	Stack();
	~Stack();

public:
	void deinit();
	void init();

public:
	StackLevel* current() const;

	void pop();
	void push(IScope* scope, const ParameterList &params);

	void print();

public:
	GlobalScope* globalScope() const;

private:
	typedef std::list<StackLevel*> StackTrace;

private:
	Stack(Stack const&)/* = delete*/;
	void operator=(Stack const&)/* = delete*/;

private:
	GlobalScope* mGlobalScope;
	StackTrace mStack;
};


}


#endif
