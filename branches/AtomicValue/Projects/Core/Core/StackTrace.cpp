
// Header
#include "StackTrace.h"

// Library includes
#include <cassert>
#include <iostream>

// Project includes

// Namespace declarations


namespace ObjectiveScript {


StackTrace::StackTrace()
{
}

StackTrace::~StackTrace()
{
}

StackTrace& StackTrace::GetInstance()
{
	static StackTrace instance;

	return instance;
}

void StackTrace::popStack()
{
	mStack.pop_back();
}

void StackTrace::print()
{
	int stackLevel = 0;

	for ( Stack::const_iterator it = mStack.begin(); it != mStack.end(); ++it ) {
		std::cout << stackLevel++ << ": " << (*it).mMethod << "(" << toString((*it).mParameters) << ")" << std::endl;
	}
}

void StackTrace::pushStack(const std::string &method, const ParameterList &params)
{
	Trace t;
	t.mMethod = method;
	t.mParameters = params;

	mStack.push_back(t);
}


}
