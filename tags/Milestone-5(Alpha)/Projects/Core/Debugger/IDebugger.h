
#ifndef Debugger_IDebugger_h
#define Debugger_IDebugger_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class SymbolScope;
class Token;

namespace Core {

// Forward declarations
class BreakPoint;

class IDebugger
{
public:
	class NextAction
	{
	public:
		enum E {
			None,
			StepInto,
			StepOut,
			StepOver,
			WaitForBreakPoint
		};
	};

public:
	virtual ~IDebugger() { }

	virtual bool addBreakPoint(const BreakPoint& breakpoint) = 0;
	virtual void clearBreakPoints() = 0;
	virtual bool removeBreakPoint(const BreakPoint& breakpoint) = 0;

	virtual void breakOnExceptionCatch(bool state) = 0;
	virtual void breakOnExceptionThrow(bool state) = 0;

	virtual bool isBreakPoint(const BreakPoint& breakpoint) const = 0;
	virtual NextAction::E nextAction() const = 0;

	virtual void notify(IScope* scope, const Token& token) = 0;
	virtual void notifyEnter(IScope* scope, const Token& token) = 0;
	virtual void notifyExceptionCatch(IScope *scope, const Token &token) = 0;
	virtual void notifyExceptionThrow(IScope *scope, const Token &token) = 0;
	virtual void notifyExit(IScope* scope, const Token& token) = 0;

	virtual void resume() = 0;
	virtual void resumeWithoutBreaks() = 0;
	virtual void stepInto() = 0;
	virtual void stepOut() = 0;
	virtual void stepOver() = 0;
};


}
}


#endif
