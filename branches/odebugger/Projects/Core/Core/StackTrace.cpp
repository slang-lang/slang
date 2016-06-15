
// Header
#include "StackTrace.h"

// Library includes
#include <cassert>
#include <iostream>

// Project includes
#include <Core/Types.h>

// Namespace declarations


namespace ObjectiveScript {


StackTrace::StackLevel::StackLevel(const std::string& method, const ParameterList& params)
: mMethod(method),
  mParameters(params)
{
}

std::string StackTrace::StackLevel::toString() const
{
	return mMethod + "(" + ObjectiveScript::toString(mParameters) + ")";
}

StackTrace::StackTrace()
{
}

StackTrace::~StackTrace()
{
}

StackTrace::StackLevel StackTrace::currentStackLevel() const
{
	return mStack.back();
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
		std::cout << stackLevel++ << ": " << (*it).toString() << std::endl;
	}
}

void StackTrace::pushStack(const std::string &method, const ParameterList &params)
{
	mStack.push_back(
		StackLevel(method, params)
	);
}


}
