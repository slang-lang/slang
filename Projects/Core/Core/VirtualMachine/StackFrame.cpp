
// Header
#include "StackFrame.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Tools.h>
#include <Core/Types.h>
#include <Tools/Strings.h>
#include <Utils.h>

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
	mScope = 0;
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

size_t StackFrame::lookup(const std::string& name) const
{
	size_t index = mCurrentStack.size() - 1;

	for ( CurrentStack::const_reverse_iterator it = mCurrentStack.rbegin(); it != mCurrentStack.rend(); ++it ) {
		if ( it->mName == name ) {
			return index;
		}

		index--;
	}

	return size_t(-1);
}

IScope* StackFrame::peek(size_t index) const
{
	if ( index == size_t(-1) ) {
assert(0);
		return mCurrentStack.back().mItem;
	}

	if ( index >= mCurrentStack.size() ) {
		OSerror("peek with invalid index: " + std::to_string(index) + " vs " + std::to_string(mCurrentStack.size()));
		throw NULL;
	}

	return mCurrentStack[index].mItem;
}

void StackFrame::popScope()
{
	Scope s = mScopeStack.back();

	mScopeStack.pop_back();

	if ( s.mAllowDelete ) {
		delete s.mScope;
	}
}

void StackFrame::popStack()
{
	while ( !mCurrentStack.empty() && mCurrentStack.back().mItem != NULL ) {
		mCurrentStack.pop_back();
	}

	if ( !mCurrentStack.empty() && mCurrentStack.back().mItem == NULL ) {
		mCurrentStack.pop_back();
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

size_t StackFrame::pushIdentifier(IScope* symbol, const std::string& name)
{
	size_t index = mCurrentStack.size();

	StackItem item;
	item.mItem = symbol;
	item.mName = name;

	mCurrentStack.push_back(item);

	return index;
}

void StackFrame::pushStack()
{
	mCurrentStack.push_back(StackItem());
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
	std::string result = "Frame " + Utils::Tools::toString(mLevel) + ": \n";

	size_t index = 0;
	for ( CurrentStack::const_iterator it = mCurrentStack.cbegin(); it != mCurrentStack.cend(); ++it ) {
		result += "(" + std::to_string(index) + "): " + it->mName + "\n";

		index++;
	}

	switch ( mScope->getScopeType() ) {
		case IScope::IType::MethodScope:
			result += mScope->getFullScopeName();
			break;
		case IScope::IType::NamedScope:
			result += mScope->getFullScopeName() + "(" + ObjectiveScript::toString(mParameters) + ")";
			break;
		case IScope::IType::SymbolScope:
			result += mScope->getFullScopeName();
			break;
	}

	return result;
}



}
