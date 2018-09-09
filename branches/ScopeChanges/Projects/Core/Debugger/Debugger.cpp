
// Header
#include "Debugger.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/VirtualMachine/Threads.h>
#include "IReceiver.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Core {


BreakPoint Debugger::immediateBreakPoint = BreakPoint();
Token Debugger::immediateBreakToken = Token();


Debugger::Debugger()
: mBreakOnExceptionCatch(false),
  mBreakOnExceptionThrow(false),
  mCurrentScope(0),
  mNextAction(NextAction::WaitForBreakPoint),
  mReceiver(0),
  mUseDebugger(false)
{
}

Debugger::~Debugger()
{
}

bool Debugger::addBreakPoint(const BreakPoint& breakpoint)
{
	BreakPointCollection::iterator it = mBreakPoints.find(breakpoint);

	if ( it != mBreakPoints.end() ) {
		mBreakPoints.erase(it);
	}

	mBreakPoints.insert(breakpoint);

	return true;
}

void Debugger::breakOnExceptionCatch(bool state)
{
	mBreakOnExceptionCatch = state;
}

void Debugger::breakOnExceptionThrow(bool state)
{
	mBreakOnExceptionThrow = state;
}

void Debugger::clearBreakPoints()
{
	mBreakPoints.clear();
}

void Debugger::deinit()
{
	// nothing to do here atm
}

BreakPointCollection::iterator Debugger::findBreakPoint(const Token& token)
{
	return mBreakPoints.find(BreakPoint(token.position()));
}

const BreakPointCollection& Debugger::getBreakPoints() const
{
	return mBreakPoints;
}

void Debugger::init()
{
	mUseDebugger = true;

	resetCurrentScope();
	resume();
}

Debugger& Debugger::Instance()
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

void Debugger::notify(IScope* scope, const Token& token)
{
	if ( !mReceiver || mNextAction == NextAction::None ) {
		return;
	}

	if ( !mCurrentScope ) {
		resetCurrentScope(scope);
	}

	BreakPoint breakpoint = BreakPoint(token.position());
	BreakPointCollection::iterator breakIt = mBreakPoints.find(breakpoint);

	bool stop = false;

	switch ( mNextAction ) {
		//case NextAction::StepInto:	// if there's nothing to step into, we just step over
		case NextAction::StepOver:
			stop = (scope == mCurrentScope);
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

	if ( stop ) {
		mReceiver->notify(scope, breakpoint);
	}
}

void Debugger::notifyEnter(IScope* scope, const Token& /*token*/)
{
	if ( mReceiver && mNextAction == NextAction::StepInto ) {
		resetCurrentScope();

		mReceiver->notifyEnter(scope, immediateBreakPoint);
	}
}

void Debugger::notifyExceptionCatch(IScope *scope, const Token &token)
{
	if ( mReceiver && mBreakOnExceptionCatch ) {
		resetCurrentScope();

		mReceiver->notifyExceptionCatch(scope, BreakPoint(token.position()));
	}
}

void Debugger::notifyExceptionThrow(IScope *scope, const Token &token)
{
	resetCurrentScope();	// reset scope no matter what next action is set

	if ( mReceiver && mBreakOnExceptionThrow ) {
		mReceiver->notifyExceptionThrow(scope, BreakPoint(token.position()));
	}
}

void Debugger::notifyExit(IScope* scope, const Token& /*token*/)
{
	resetCurrentScope();	// reset scope no matter what next action is set

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

void Debugger::resetCurrentScope(IScope* scope)
{
	mCurrentScope = scope;
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

bool Debugger::useDebugger() const
{
	return mUseDebugger;
}


}
}
