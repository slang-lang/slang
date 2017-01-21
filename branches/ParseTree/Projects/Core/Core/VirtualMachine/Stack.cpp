
// Header
#include "Stack.h"

// Library includes
#include <cassert>
#include <iostream>

// Project includes
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


Stack::Stack()
: mGlobalScope(0)
{
}

Stack::~Stack()
{
}

StackFrame* Stack::current() const
{
	if ( mStackFrames.empty() ) {
		return 0;
	}

	return mStackFrames.back();
}

void Stack::deinit()
{
	assert( !mStackFrames.empty() );

	while ( !mStackFrames.empty() ) {
		pop();
	}

	delete mGlobalScope;
	mGlobalScope = 0;
}

Runtime::ExceptionData& Stack::exception()
{
	return mExceptionData;
}

MethodScope* Stack::globalScope() const
{
	return mGlobalScope;
}

void Stack::init()
{
	assert(!mGlobalScope);
	mGlobalScope = new Common::Namespace(VALUE_NONE, 0);

	push(mGlobalScope, ParameterList());
}

void Stack::pop()
{
	StackFrame* frame = mStackFrames.back();
	frame->popTokens();
	frame->popScope();

	mStackFrames.pop_back();

	delete frame;
}

void Stack::print()
{
	if ( mStackFrames.empty() ) {
		return;
	}

	StackFrames::const_iterator it = mStackFrames.begin();
	++it;	// skip frame 0 (global scope)

	for ( ; it != mStackFrames.end(); ++it ) {
		std::cout << (*it)->toString() << std::endl;
	}
}

void Stack::push(IScope* scope, const ParameterList &params)
{
	TokenList tokens;
	if ( dynamic_cast<Common::Method*>(scope) ) {
		tokens = dynamic_cast<Common::Method*>(scope)->getTokens();
	}

	// create new stack frame
	StackFrame* frame = new StackFrame(mStackFrames.size(), scope, params);
	// push scope
	frame->pushScope(scope, false);
	// push tokens (although maybe none are present)
	frame->pushTokens(tokens);

	mStackFrames.push_back(frame);
}


}
