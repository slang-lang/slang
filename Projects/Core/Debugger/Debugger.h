
#ifndef Debugger_Debugger_h
#define Debugger_Debugger_h


// Library includes

// Project includes
#include <Core/Scope.h>
#include <Core/Token.h>
#include "BreakPoint.h"
#include "IDebugger.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Core {

// Forward declarations
class IReceiver;

class Debugger : public IDebugger
{
public:
	static BreakPoint immediateBreakPoint;
	static Token immediateBreakToken;

// Singleton
// {
public:
	static Debugger& GetInstance();
// }

public:	// IDebugger implementation
	bool addBreakPoint(const BreakPoint& breakpoint);
	bool removeBreakPoint(const BreakPoint& breakpoint);

	const BreakPointList& getBreakPoints() const;
	bool isBreakPoint(const BreakPoint& breakpoint) const;
	NextAction::E nextAction() const;

	void notify(SymbolScope* scope, const Token& token = Token());
	void notifyEnter(SymbolScope* scope, const Token& token = Token());
	void notifyExit(SymbolScope* scope, const Token& token = Token());

	void stepInto() { mNextAction = NextAction::StepInto; }
	void stepOut() { mNextAction = NextAction::StepOut; }
	void stepOver() { mNextAction = NextAction::StepOver; }
	void resume() { mNextAction = NextAction::WaitForBreakPoint; }
	void resumeWithoutBreaks() { mNextAction = NextAction::None; }

public:
	bool registerReceiver(Core::IReceiver* receiver);
	bool unregisterReceiver(Core::IReceiver* receiver);

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
	Core::IReceiver* mReceiver;
};



}
}


#endif
