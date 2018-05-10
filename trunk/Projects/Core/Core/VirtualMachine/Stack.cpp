
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
{
}

Stack::~Stack()
{
	while ( !mStackFrames.empty() ) {
		pop();
	}
}

StackFrame* Stack::current() const
{
	if ( mStackFrames.empty() ) {
		return 0;
	}

	return mStackFrames.back();
}

Runtime::ExceptionData& Stack::exception()
{
	return mExceptionData;
}

StackFrame* Stack::frame(Common::FrameId frameId) const
{
	size_t idx = 0;
	for ( StackFrames::const_iterator it = mStackFrames.cbegin(); it != mStackFrames.cend(); ++it, ++idx ) {
		if ( idx == frameId ) {
			return (*it);
		}
	}

	return 0;
}

Common::FrameId Stack::getNumFrames() const
{
	return mStackFrames.size();
}

void Stack::pop()
{
	StackFrame* frame = mStackFrames.back();
	frame->popTokens();
	frame->popScope();

	mStackFrames.pop_back();

	delete frame;
}

void Stack::push(IScope* scope, const TokenList& tokens, const ParameterList &params)
{
	// create new stack frame
	StackFrame* frame = new StackFrame(mStackFrames.size(), scope, params);
	// push scope
	frame->pushScope(scope, false, false);
	// push tokens (although maybe none are present)
	frame->pushTokens(tokens);

	mStackFrames.push_back(frame);
}


}
