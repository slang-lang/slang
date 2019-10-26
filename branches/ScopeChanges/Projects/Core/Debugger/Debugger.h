
#ifndef Debugger_Debugger_h
#define Debugger_Debugger_h


// Library includes

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Scope.h>
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
	static Debugger& Instance();
// }

public:
	void deinit();
	void init();
	bool useDebugger() const;

public:	// IDebugger implementation
	bool addBreakPoint(const BreakPoint& breakpoint);
	void clearBreakPoints();
	bool removeBreakPoint(const BreakPoint& breakpoint);

	void breakOnExceptionCatch(bool state);
	void breakOnExceptionThrow(bool state);

	const BreakPointCollection& getBreakPoints() const;
	bool isBreakPoint(const BreakPoint& breakpoint) const;

	NextAction::E nextAction() const;

	void notify(IScope* scope, const Token& token = Token());
	void notifyEnter(IScope* scope, const Token& token = Token());
	void notifyExceptionCatch(IScope* scope, const Token& token = Token());
	void notifyExceptionThrow(IScope* scope, const Token& token = Token());
	void notifyExit(IScope* scope, const Token& token = Token());

	void resume();
	void resumeWithoutBreaks();
	void stepInto();
	void stepOut();
	void stepOver();

public:
	bool registerReceiver(Core::IReceiver* receiver);
	bool unregisterReceiver(Core::IReceiver* receiver);

private:
	BreakPointCollection::iterator findBreakPoint(const Token& token);

private:
	Debugger();
	Debugger(const Debugger& );
	Debugger operator=(const Debugger& );
	~Debugger();

private:
	bool mBreakOnExceptionCatch;
	bool mBreakOnExceptionThrow;
	BreakPointCollection mBreakPoints;
	NextAction::E mNextAction;
	Core::IReceiver* mReceiver;
	bool mUseDebugger;
};



}
}


#endif
