
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
	deinit();
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
}

GlobalScope* Stack::globalScope() const
{
	return mGlobalScope;
}

void Stack::init()
{
	mGlobalScope = new GlobalScope();

	StackLevel* level = new StackLevel(mStack.size(), 0, ParameterList());
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

void Stack::push(Runtime::Method *method, const ParameterList &params)
{
	StackLevel* level = new StackLevel(mStack.size(), method, params);
	level->pushScope(method, false);
	level->pushTokens(method->getTokens());

	mStack.push_back(level);
}


}
