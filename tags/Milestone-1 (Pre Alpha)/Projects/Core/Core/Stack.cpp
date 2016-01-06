
// Header
#include "Stack.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/Utils/Exceptions.h>
#include "Scope.h"

// Namespace declarations


namespace ObjectiveScript {


Stack::Stack(const std::string& name, const ParameterList& params)
: mName(name),
  mParameters(params)
{
	// push initial scope
	pushScope(name);
}

Stack::~Stack()
{
	for ( ScopeStack::reverse_iterator it = mScopeStack.rbegin(); it != mScopeStack.rend(); ++it ) {
		delete (*it);
	}
	mScopeStack.clear();
}

LocalScope* Stack::getCurrentScope() const
{
	if ( mScopeStack.empty() ) {
		return 0;
	}

	return mScopeStack.back();
}

void Stack::popScope()
{
	if ( mScopeStack.empty() ) {
		// we reach the bottom of our stack, here's nothing to pop anymore
		return;
	}

	LocalScope *scope = mScopeStack.back();
	mScopeStack.pop_back();

	delete scope;
}

void Stack::print()
{
	for ( ScopeStack::const_iterator it = mScopeStack.begin(); it != mScopeStack.end(); ++it ) {
		std::cout << "Scope(" << (*it)->getScopeName() << ")" << std::endl;
	}
}

IScope* Stack::pushScope(const std::string& name)
{
	LocalScope *scope = new LocalScope(name, getCurrentScope());

	mScopeStack.push_back(scope);
	return scope;
}


StackTrace::StackTrace()
{
}

StackTrace::~StackTrace()
{
	for ( StackList::reverse_iterator it = mStack.rbegin(); it != mStack.rend(); ++it ) {
		delete (*it);
	}
	mStack.clear();
}

void StackTrace::popStack()
{
	if ( mStack.empty() ) {
		throw Utils::Exceptions::Exception("cannot pop stack beyond bottom");
	}

	Stack *stack = mStack.back();
	delete stack;

	mStack.pop_back();
}

void StackTrace::print()
{
	for ( StackList::const_iterator it = mStack.begin(); it != mStack.end(); ++it ) {
		(*it)->print();
	}
}

void StackTrace::pushStack(const std::string& name, const ParameterList& params)
{
	Stack *stack = new Stack(name, params);

	mStack.push_back(stack);
}


}
