
#ifndef ObjectiveScript_Core_VirtualMachine_Stack_h
#define ObjectiveScript_Core_VirtualMachine_Stack_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "StackLevel.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Stack
{
// Singleton
// {
public:
	static Stack& Instance();
// }

public:
	typedef std::list<StackLevel*> StackTrace;

public:
	Stack();
	~Stack();

public:
	StackLevel* current() const;

	void pop();
	void push(Runtime::Method *method, const ParameterList &params);

	void print();

private:
	Stack(Stack const&)/* = delete*/;
	void operator=(Stack const&)/* = delete*/;

private:
	StackTrace mStack;
};


}


#endif
