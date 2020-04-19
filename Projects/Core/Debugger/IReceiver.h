
#ifndef Debugger_IReceiver_h
#define Debugger_IReceiver_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declaration
class IScope;

namespace Core {

// Forward declaration
class BreakPoint;

class IReceiver
{
public:
	virtual ~IReceiver() { }

	virtual int notify(IScope* scope, const BreakPoint& breakpoint) = 0;
	virtual int notifyEnter(IScope* scope, const BreakPoint& breakpoint) = 0;
	virtual int notifyExceptionCatch(IScope *scope, const BreakPoint &breakpoint) = 0;
	virtual int notifyExceptionThrow(IScope *scope, const BreakPoint &breakpoint) = 0;
	virtual int notifyExit(IScope* scope, const BreakPoint& breakpoint) = 0;
};


}
}


#endif
