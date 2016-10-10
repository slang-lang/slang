
// Header
#include "StackTrace.h"

// Library includes
#include <cassert>
#include <iostream>

// Project includes
#include <Core/Tools.h>
#include <Core/Types.h>

// Namespace declarations


namespace ObjectiveScript {


StackTrace::StackTrace()
{
}

StackTrace::~StackTrace()
{
	while ( !mStack.empty() ) {
		pop();
	}
}

StackLevel* StackTrace::current() const
{
	if ( mStack.empty() ) {
		return 0;
	}

	return mStack.back();
}

StackTrace& StackTrace::GetInstance()
{
	static StackTrace instance;

	return instance;
}

void StackTrace::pop()
{
	StackLevel* level = mStack.back();
	level->popTokens();
	level->popScope();

	mStack.pop_back();

	delete level;
}

void StackTrace::print()
{
	for ( Stack::const_iterator it = mStack.begin(); it != mStack.end(); ++it ) {
		std::cout << (*it)->toString() << std::endl;
	}
}

void StackTrace::push(Runtime::Method *method, const ParameterList &params)
{
	StackLevel* level = new StackLevel(mStack.size(), method, params);
	level->pushScope(method, false);
	level->pushTokens(method->getTokens());

	mStack.push_back(level);
}


}
