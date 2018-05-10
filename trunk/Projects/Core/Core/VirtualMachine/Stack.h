
#ifndef ObjectiveScript_Core_VirtualMachine_Stack_h
#define ObjectiveScript_Core_VirtualMachine_Stack_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Common/Types.h>
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
	StackFrame* current() const;
	StackFrame* frame(Common::FrameId frameId) const;
	Common::FrameId getNumFrames() const;

	Runtime::ExceptionData& exception();

	void pop();
	void push(IScope* scope, const TokenList& tokens, const ParameterList &params);

protected:
	typedef std::list<StackFrame*> StackFrames;

protected:
	Runtime::ExceptionData mExceptionData;
	StackFrames mStackFrames;

private:
	Stack(Stack const&)/* = delete*/;
	void operator=(Stack const&)/* = delete*/;
};


}


#endif
