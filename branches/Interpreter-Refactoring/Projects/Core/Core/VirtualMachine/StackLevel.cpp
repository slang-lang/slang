
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


StackLevel::StackLevel(unsigned long level, IScope* scope, const ParameterList& params)
: mLevel(level),
  mParameters(params),
  mScope(scope)
{
}

StackLevel::~StackLevel()
{
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
	std::string result = "Frame " + Tools::ConvertToStdString(mLevel);

	if ( mScope && mScope->getScopeType() == IScope::IType::NamedScope ) {
		result += ": " + mScope->getFullScopeName();

		if ( dynamic_cast<Runtime::Method*>(mScope) ) {
			result += dynamic_cast<Runtime::Method*>(mScope)->ToString();
		}
	}

	return result;
}



}
