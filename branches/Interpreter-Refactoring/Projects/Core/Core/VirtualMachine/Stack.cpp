
// Header
#include "Stack.h"

// Library includes
#include <cassert>
#include <iostream>

// Project includes
#include <Core/Tools.h>
#include <Core/Types.h>

// Namespace declarations


namespace ObjectiveScript {


Stack::Stack()
: mGlobalScope(0)
{
}

Stack::~Stack()
{
}

StackLevel* Stack::current() const
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

GlobalScope* Stack::globalScope() const
{
	return mGlobalScope;
}

void Stack::init()
{
	mGlobalScope = new GlobalScope();

	StackLevel* level = new StackLevel(mStack.size(), mGlobalScope, ParameterList());
	level->pushScope(mGlobalScope, false);
	level->pushTokens(TokenList());

	mStack.push_back(level);
}

void Stack::pop()
{
	StackLevel* level = mStack.back();
	level->popTokens();
	level->popScope();

	mStack.pop_back();

	delete level;
}

void Stack::print()
{
	for ( StackTrace::const_iterator it = mStack.begin(); it != mStack.end(); ++it ) {
		std::cout << (*it)->toString() << std::endl;
	}
}

void Stack::push(IScope* scope, const ParameterList &params)
{
	// create new stack level
	StackLevel* level = new StackLevel(mStack.size(), scope, params);
	// push its scope
	level->pushScope(scope, false);
	// in case its a method also push its tokens
	if ( dynamic_cast<Runtime::Method*>(scope) ) {
		level->pushTokens(dynamic_cast<Runtime::Method*>(scope)->getTokens());
	}

	mStack.push_back(level);
}


}
