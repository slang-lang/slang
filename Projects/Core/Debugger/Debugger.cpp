
// Header
#include "Debugger.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/StackTrace.h>
#include "IReceiver.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Core {


BreakPoint Debugger::immediateBreakPoint = BreakPoint();
Token Debugger::immediateBreakToken = Token();


Debugger::Debugger()
: mNextAction(NextAction::WaitForBreakPoint),
  mReceiver(0)
{
}

Debugger::~Debugger()
{
}

bool Debugger::addBreakPoint(const BreakPoint& breakpoint)
{
	if ( isBreakPoint(breakpoint) ) {
		// duplicate break point
		return false;
	}

	mBreakPoints.insert(breakpoint);

	return true;
}

const BreakPointCollection& Debugger::getBreakPoints() const
{
	return mBreakPoints;
}

Debugger& Debugger::GetInstance()
{
	static Debugger mDebugger;

	return mDebugger;
}

bool Debugger::isBreakPoint(const BreakPoint& breakpoint) const
{
	return mBreakPoints.find(breakpoint) != mBreakPoints.end();
}

IDebugger::NextAction::E Debugger::nextAction() const
{
	return mNextAction;
}

void Debugger::notify(SymbolScope* scope, const Token& token)
{
	if ( !mReceiver || mNextAction == NextAction::None ) {
		return;
	}

	BreakPoint breakpoint(token.position());

	bool stop = false;

	switch ( mNextAction ) {
		case NextAction::StepOver:
			stop = true;
			break;
		case NextAction::WaitForBreakPoint:
			stop = isBreakPoint(breakpoint);
			break;
		default:
			break;
	}

	if ( stop && mReceiver ) {
		mReceiver->notify(scope, token);
	}
}

void Debugger::notifyEnter(SymbolScope* scope, const Token& token)
{
	if ( mReceiver && mNextAction == NextAction::StepInto ) {
		mReceiver->notifyEnter(scope, token);
	}
}

void Debugger::notifyExit(SymbolScope* scope, const Token& token)
{
	if ( mReceiver && mNextAction == NextAction::StepOut ) {
		mReceiver->notifyExit(scope, token);
	}
}

bool Debugger::registerReceiver(Core::IReceiver* receiver)
{
	// only one receiver can be registered at a time

	if ( !mReceiver ) {
		mReceiver = receiver;
		return true;
	}

	return false;
}

bool Debugger::removeBreakPoint(const BreakPoint& breakpoint)
{
	size_t size = mBreakPoints.size();

	//mBreakPoints.remove(breakpoint);
	mBreakPoints.erase(mBreakPoints.find(breakpoint));

	return size > mBreakPoints.size();
}

bool Debugger::unregisterReceiver(Core::IReceiver* receiver)
{
	// only the original receiver is allowed to unregister itself

	if ( mReceiver == receiver ) {
		mReceiver = 0;
		return true;
	}

	return false;
}


}
}
