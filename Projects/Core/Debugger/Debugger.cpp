
// Header
#include "Debugger.h"

// Library includes

// Project includes
#include "IReceiver.h"

// Namespace declarations


namespace Slang {
namespace Core {


BreakPoint Debugger::immediateBreakPoint = BreakPoint();
Token Debugger::immediateBreakToken = Token();


Debugger::Debugger()
: mBreakOnExceptionCatch(false),
  mBreakOnExceptionThrow(false),
  mNextAction(NextAction::WaitForBreakPoint),
  mReceiver(nullptr),
  mUseDebugger(false)
{
}

bool Debugger::addBreakPoint(const BreakPoint& breakpoint)
{
	auto it = mBreakPoints.find(breakpoint);

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

	BreakPoint breakpoint(token.position());
	auto breakIt = mBreakPoints.find(breakpoint);

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

	if ( stop ) {
		mReceiver->notify(scope, breakpoint);
	}
}

void Debugger::notifyEnter(IScope* scope, const Token& token)
{
	if ( mReceiver && mNextAction == NextAction::StepInto ) {
		mReceiver->notifyEnter(scope, BreakPoint( token.position() ) );
	}
}

void Debugger::notifyExceptionCatch(IScope *scope, const Token& token)
{
	if ( mReceiver && mBreakOnExceptionCatch ) {
		mReceiver->notifyExceptionCatch(scope, BreakPoint( token.position() ) );
	}
}

void Debugger::notifyExceptionThrow(IScope *scope, const Token& token)
{
	if ( mReceiver && mBreakOnExceptionThrow ) {
		mReceiver->notifyExceptionThrow(scope, BreakPoint( token.position() ));
	}
}

void Debugger::notifyExit(IScope* scope, const Token& token)
{
	if ( mReceiver && mNextAction == NextAction::StepOut ) {
		mReceiver->notifyExit(scope, BreakPoint( token.position() ) );
	}
}

bool Debugger::registerReceiver(IReceiver* receiver)
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

bool Debugger::unregisterReceiver(IReceiver* receiver)
{
	// only the original receiver is allowed to unregister itself

	if ( mReceiver == receiver ) {
		mReceiver = nullptr;
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
