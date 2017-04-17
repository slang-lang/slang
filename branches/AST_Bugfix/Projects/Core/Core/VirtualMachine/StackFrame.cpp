
// Header
#include "StackFrame.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


StackFrame::Scope::Scope(IScope* scope, bool allowDelete, bool allowBreakAndContinue)
: mAllowBreakAndContinue(allowBreakAndContinue),
  mAllowDelete(allowDelete),
  mScope(scope)
{
}


StackFrame::StackFrame(unsigned long level, IScope* scope, const ParameterList& params)
: mLevel(level),
  mParameters(params),
  mScope(scope)
{
}

StackFrame::~StackFrame()
{
}

bool StackFrame::allowBreakAndContinue() const
{
	return mScopeStack.back().mAllowBreakAndContinue;
}

IScope* StackFrame::getScope() const
{
	return mScopeStack.back().mScope;
}

const TokenList& StackFrame::getTokens() const
{
	return mTokenStack.back();
}

void StackFrame::popScope()
{
	Scope s = mScopeStack.back();

	mScopeStack.pop_back();

	if ( s.mAllowDelete ) {
		delete s.mScope;
	}
}

void StackFrame::popTokens()
{
	mTokenStack.pop_back();
}

void StackFrame::pushScope(IScope* scope, bool allowDelete, bool allowBreakAndContinue)
{
	mScopeStack.push_back(
		Scope(scope, allowDelete, allowBreakAndContinue)
	);
}

void StackFrame::pushTokens(const TokenList& tokens)
{
	mTokenStack.push_back(
		tokens
	);
}

Runtime::Object& StackFrame::returnValue()
{
	return mReturnValue;
}

std::string StackFrame::toString() const
{
	std::string result = "Frame " + Tools::toString(mLevel) + ": ";

	switch ( mScope->getScopeType() ) {
		case IScope::IType::MethodScope:
			result += mScope->getFullScopeName();
			break;
		case IScope::IType::NamedScope:
			result += mScope->getFullScopeName();
			break;
		case IScope::IType::SymbolScope:
			result += mScope->getFullScopeName();
			break;
	}

	return result;
}



}
