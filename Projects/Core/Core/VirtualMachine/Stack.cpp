
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
	if ( mStack.empty() ) {
		return 0;
	}

	return mStack.back();
}

void Stack::deinit()
{
	assert( !mStack.empty() );

	while ( !mStack.empty() ) {
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
	StackFrame* level = mStack.back();
	level->popTokens();
	level->popScope();

	mStack.pop_back();

	delete level;
}

void Stack::print()
{
	if ( mStack.empty() ) {
		return;
	}

	StackTrace::const_iterator it = mStack.begin();
	++it;	// skip frame 0 (global scope)

	for ( ; it != mStack.end(); ++it ) {
		std::cout << (*it)->toString() << std::endl;
	}
}

void Stack::push(IScope* scope, const ParameterList &params)
{
	TokenList tokens;
	if ( dynamic_cast<Common::Method*>(scope) ) {
		tokens = dynamic_cast<Common::Method*>(scope)->getTokens();
	}

	// create new stack level
	StackFrame* level = new StackFrame(mStack.size(), scope, params);
	// push scope
	level->pushScope(scope, false);
	// push tokens (although maybe none are present)
	level->pushTokens(tokens);

	mStack.push_back(level);
}


}
