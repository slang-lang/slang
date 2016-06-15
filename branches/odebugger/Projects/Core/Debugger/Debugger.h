
#ifndef Debugger_Debugger_h
#define Debugger_Debugger_h


// Library includes

// Project includes
#include "BreakPoint.h"
#include "IDebugger.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Core {


class Debugger : public IDebugger
{
public:
	static BreakPoint immediateBreak;

// Singleton
// {
public:
	static Debugger& GetInstance();
// }

public:	// IDebugger implementation
	bool addBreakPoint(const BreakPoint& breakpoint);
	bool removeBreakPoint(const BreakPoint& breakpoint);

	bool isBreakPoint(const BreakPoint& breakpoint) const;
	NextAction::E nextAction() const;

	void notify(const BreakPoint& breakpoint = BreakPoint());

	void stepInto() { mNextAction = NextAction::StepInto; }
	void stepOut() { mNextAction = NextAction::StepOut; }
	void stepOver() { mNextAction = NextAction::StepOver; }
	void resume() { mNextAction = NextAction::WaitForBreakPoint; }

private:
	BreakPointList::const_iterator find(const BreakPoint& breakpoint) const;

private:
	Debugger();
	Debugger(const Debugger& );
	Debugger operator=(const Debugger& );
	~Debugger();

private:
	BreakPointList mBreakPoints;
	NextAction::E mNextAction;
};



}
}


#endif
