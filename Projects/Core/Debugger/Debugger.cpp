
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

void Debugger::breakOnException(bool state)
{
	(void)state;
}

BreakPointCollection::iterator Debugger::findBreakPoint(const Token& token)
{
	return mBreakPoints.find(BreakPoint(token.position()));
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

	BreakPoint breakpoint = BreakPoint(token.position());
	BreakPointCollection::iterator breakIt = mBreakPoints.find(breakpoint);

	bool stop = false;

	switch ( mNextAction ) {
		case NextAction::StepOver:
			stop = true;
			break;
		case NextAction::WaitForBreakPoint:
			if ( breakIt != mBreakPoints.end() ) {
				stop = true;
				breakpoint = *breakIt;
			}
			break;
		default:
			break;
	}

	if ( stop && mReceiver ) {
		mReceiver->notify(scope, breakpoint);
	}
}

void Debugger::notifyEnter(SymbolScope* scope, const Token& /*token*/)
{
	if ( mReceiver && mNextAction == NextAction::StepInto ) {
		mReceiver->notifyEnter(scope, immediateBreakPoint);
	}
}

void Debugger::notifyExit(SymbolScope* scope, const Token& /*token*/)
{
	if ( mReceiver && mNextAction == NextAction::StepOut ) {
		mReceiver->notifyExit(scope, immediateBreakPoint);
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

	mBreakPoints.erase(mBreakPoints.find(breakpoint));

	return size > mBreakPoints.size();
}

void Debugger::resume()
{
	mNextAction = NextAction::WaitForBreakPoint;
}

void Debugger::resumeWithoutBreaks()
{
	mNextAction = NextAction::None;
}

void Debugger::stepInto()
{
	mNextAction = NextAction::StepInto;
}

void Debugger::stepOut()
{
	mNextAction = NextAction::StepOut;
}

void Debugger::stepOver()
{
	mNextAction = NextAction::StepOver;
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
