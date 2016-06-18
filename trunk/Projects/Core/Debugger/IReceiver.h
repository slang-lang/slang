
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


class IReceiver
{
public:
	virtual ~IReceiver() { }

	virtual int runCLI(SymbolScope* scope) = 0;
};


}
}


#endif
