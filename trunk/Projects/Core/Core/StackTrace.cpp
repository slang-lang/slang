
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


StackTrace::StackLevel::StackLevel()
: mLevel(0)
{
}

StackTrace::StackLevel::StackLevel(const unsigned long level, const std::string& method, const ParameterList& params)
: mLevel(level),
  mMethod(method),
  mParameters(params)
{
}

std::string StackTrace::StackLevel::toString() const
{
	return "Frame " + Tools::ConvertToStdString(mLevel) + ": " + mMethod + "(" + ObjectiveScript::toString(mParameters) + ")";
}

StackTrace::StackTrace()
{
}

StackTrace::~StackTrace()
{
}

void StackTrace::clear()
{
	while ( !mStack.empty() ) {
		mStack.pop_back();
	}
}

StackTrace::StackLevel StackTrace::currentStackLevel() const
{
	if ( mStack.empty() ) {
		return StackTrace::StackLevel();
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
	mStack.pop_back();
}

void StackTrace::print()
{
	for ( Stack::const_iterator it = mStack.begin(); it != mStack.end(); ++it ) {
		std::cout << (*it).toString() << std::endl;
	}
}

void StackTrace::pushStack(const std::string &method, const ParameterList &params)
{
	mStack.push_back(
		StackLevel(mStack.size(), method, params)
	);
}


}
