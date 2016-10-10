
#ifndef ObjectiveScript_Core_VirtualMachine_StackTrace_h
#define ObjectiveScript_Core_VirtualMachine_StackTrace_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "StackLevel.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class StackTrace
{
// Singleton
// {
public:
	static StackTrace& GetInstance();
// }

public:
	typedef std::list<StackLevel*> Stack;

public:
	~StackTrace();

public:
	StackLevel* current() const;

	void pop();
	void push(Runtime::Method *method, const ParameterList &params);

	void print();

private:
	StackTrace();

	StackTrace(StackTrace const&)/* = delete*/;
	void operator=(StackTrace const&)/* = delete*/;

private:
	Stack mStack;
};


}


#endif
