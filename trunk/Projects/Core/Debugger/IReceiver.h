
#ifndef Debugger_IReceiver_h
#define Debugger_IReceiver_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declaration
class SymbolScope;

namespace Core {

// Forward declaration
class BreakPoint;

class IReceiver
{
public:
	virtual ~IReceiver() { }

	virtual int notify(SymbolScope* scope, const BreakPoint& breakpoint) = 0;
	virtual int notifyEnter(SymbolScope* scope, const BreakPoint& breakpoint) = 0;
	virtual int notifyException(SymbolScope* scope, const BreakPoint& breakpoint) = 0;
	virtual int notifyExit(SymbolScope* scope, const BreakPoint& breakpoint) = 0;
};


}
}


#endif
