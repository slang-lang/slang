
// Header
#include "Debugger.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/StackTrace.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Core {


BreakPoint Debugger::immediateBreak = BreakPoint();


Debugger::Debugger()
: mNextAction(NextAction::None)
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

	mBreakPoints.push_back(breakpoint);

	return true;
}

BreakPointList::const_iterator Debugger::find(const BreakPoint& breakpoint) const
{
	for ( BreakPointList::const_iterator it = mBreakPoints.begin(); it != mBreakPoints.end(); ++it ) {
		if ( (*it) == breakpoint ) {
			return it;
		}
	}

	return mBreakPoints.end();
}

Debugger& Debugger::GetInstance()
{
	static Debugger mDebugger;

	return mDebugger;
}

bool Debugger::isBreakPoint(const BreakPoint& breakpoint) const
{
	BreakPointList::const_iterator it = find(breakpoint);

	return it != mBreakPoints.end();
}

IDebugger::NextAction::E Debugger::nextAction() const
{
	return mNextAction;
}

void Debugger::notify(const BreakPoint& breakpoint)
{
	if ( mNextAction == NextAction::None ) {
		// no planned action
		return;
	}

	if ( !isBreakPoint(breakpoint) && !(breakpoint == immediateBreak) ) {
		// this is no (immediate) breakpoint
		return;
	}

	if ( breakpoint == immediateBreak ) {
		switch ( mNextAction ) {
			case NextAction::StepInto: std::cout << "Stepping into " << StackTrace::GetInstance().currentStackLevel().toString() << std::endl; break;
			case NextAction::StepOut: std::cout << "Stepping out " << StackTrace::GetInstance().currentStackLevel().toString() << std::endl; break;
			default: break;
		}
	}
	else {
		std::cout << "Breakpoint " << breakpoint.getFilename() << ", " << breakpoint.getLine() << " reached" << std::endl;
	}
}

bool Debugger::removeBreakPoint(const BreakPoint& breakpoint)
{
	size_t size = mBreakPoints.size();

	mBreakPoints.remove(breakpoint);

	return size > mBreakPoints.size();
}


}
}
