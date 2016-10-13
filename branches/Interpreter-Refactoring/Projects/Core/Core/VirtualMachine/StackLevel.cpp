
// Header
#include "StackLevel.h"

// Library includes

// Project includes
#include <Core/Method.h>
#include <Core/Tools.h>
#include <Core/Types.h>

// Namespace declarations


namespace ObjectiveScript {


StackLevel::Scope::Scope(IScope* scope, bool allowDelete)
: mAllowDelete(allowDelete),
  mScope(scope)
{
}


StackLevel::StackLevel(unsigned long level, Runtime::Method* method, const ParameterList& params)
: mLevel(level),
  mMethod(method),
  mParameters(params)
{
}

Runtime::Method* StackLevel::getMethod() const
{
	return mMethod;
}

const ParameterList& StackLevel::getParameters() const
{
	return mParameters;
}

IScope* StackLevel::getScope() const
{
	return mScopeStack.back().mScope;
}

const TokenList& StackLevel::getTokens() const
{
	return mTokenStack.back();
}

void StackLevel::popScope()
{
	Scope s = mScopeStack.back();

	mScopeStack.pop_back();

	if ( s.mAllowDelete ) {
		delete s.mScope;
	}
}

void StackLevel::popTokens()
{
	mTokenStack.pop_back();
}

void StackLevel::pushScope(IScope* scope, bool allowDelete)
{
	mScopeStack.push_back(
		Scope(scope, allowDelete)
	);
}

void StackLevel::pushTokens(const TokenList& tokens)
{
	mTokenStack.push_back(
		tokens
	);
}

std::string StackLevel::toString() const
{
	if ( mMethod ) {
		return "Frame " + Tools::ConvertToStdString(mLevel) + ": " + mMethod->getFullScopeName() + "(" + ObjectiveScript::toString(mParameters) + ")";
	}

	return "Frame " + Tools::ConvertToStdString(mLevel);
}



}
