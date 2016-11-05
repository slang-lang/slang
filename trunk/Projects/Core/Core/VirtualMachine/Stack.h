
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

// Forward declarations
namespace Runtime {
	class Namespace;
}

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
	MethodScope* globalScope() const;

private:
	typedef std::list<StackLevel*> StackTrace;

private:
	Stack(Stack const&)/* = delete*/;
	void operator=(Stack const&)/* = delete*/;

private:
	Runtime::Namespace* mGlobalScope;
	StackTrace mStack;
};


}


#endif
