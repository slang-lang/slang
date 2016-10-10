
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
}

void StackTrace::clear()
{
	while ( !mStack.empty() ) {
		popStack();
	}
}

StackLevel* StackTrace::currentStackLevel() const
{
	if ( mStack.empty() ) {
		return 0;
	}

	return mStack.back();
}

const StackTrace::Stack& StackTrace::getStack() const
{
	return mStack;
}

StackTrace& StackTrace::GetInstance()
{
	static StackTrace instance;

	return instance;
}

void StackTrace::popStack()
{
	StackLevel* level = mStack.back();

	mStack.pop_back();

	delete level;
}

void StackTrace::print()
{
	for ( Stack::const_iterator it = mStack.begin(); it != mStack.end(); ++it ) {
		std::cout << (*it)->toString() << std::endl;
	}
}

void StackTrace::pushStack(Runtime::Method* method, const ParameterList &params)
{
	mStack.push_back(
		new StackLevel(mStack.size(), method, params)
	);
}


}
