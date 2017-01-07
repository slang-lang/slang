
#ifndef ObjectiveScript_Core_VirtualMachine_Stack_h
#define ObjectiveScript_Core_VirtualMachine_Stack_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Runtime/ExceptionData.h>
#include <Core/Scope.h>
#include "StackFrame.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Common {
	class Namespace;
}

class Stack
{
public:
	Stack();
	virtual ~Stack();

public:
	virtual void deinit();
	virtual void init();

public:
	StackFrame* current() const;

	Runtime::ExceptionData& exception();

	void pop();
	void push(IScope* scope, const ParameterList &params);

	void print();

public:
	MethodScope* globalScope() const;

protected:
	typedef std::list<StackFrame*> StackTrace;

protected:
	Runtime::ExceptionData mExceptionData;
	Common::Namespace* mGlobalScope;
	StackTrace mStack;

private:
	Stack(Stack const&)/* = delete*/;
	void operator=(Stack const&)/* = delete*/;
};


}


#endif
