
#ifndef Core_Debugger_Debugger_h
#define Core_Debugger_Debugger_h


// Library includes

// Project includes
#include <Core/Common/Token.h>
#include <Core/Scope.h>
#include "BreakPoint.h"
#include "IDebugger.h"

// Forward declarations

// Namespace declarations


namespace Slang {
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
	bool addBreakPoint(const BreakPoint& breakpoint) override;
	void clearBreakPoints() override;
	bool removeBreakPoint(const BreakPoint& breakpoint) override;

	void breakOnExceptionCatch(bool state) override;
	void breakOnExceptionThrow(bool state) override;

	const BreakPointCollection& getBreakPoints() const;
	bool isBreakPoint(const BreakPoint& breakpoint) const override;

	NextAction::E nextAction() const override;

	void notify(IScope* scope, const Token& token = Token()) override;
	void notifyEnter(IScope* scope, const Token& token = Token()) override;
	void notifyExceptionCatch(IScope* scope, const Token& token = Token()) override;
	void notifyExceptionThrow(IScope* scope, const Token& token = Token()) override;
	void notifyExit(IScope* scope, const Token& token = Token()) override;

	void resume() override;
	void resumeWithoutBreaks() override;
	void stepInto() override;
	void stepOut() override;
	void stepOver() override;

public:
	bool registerReceiver(Core::IReceiver* receiver);
	bool unregisterReceiver(Core::IReceiver* receiver);

private:
	BreakPointCollection::iterator findBreakPoint(const Token& token);

private:
	Debugger();
	Debugger(const Debugger& );
	Debugger operator=(const Debugger& );
	~Debugger() override = default;

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
