
#ifndef ObjectiveScript_odebugger_Backend_IBackend_h
#define ObjectiveScript_odebugger_Backend_IBackend_h


// Library includes

// Project includes
#include <Core/Types.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class IBackend
{
public:
	virtual ~IBackend() { }

	virtual bool addBreakPoint(const StringList& tokens) = 0;
	virtual bool removeBreakPoint(const StringList& tokens) = 0;

	virtual void continueExecution() = 0;
	virtual void executeSymbol(const StringList& tokens) = 0;
	virtual bool modifySymbol(const StringList& tokens) = 0;
	virtual void printBreakPoints() = 0;
	virtual void printSymbol(const StringList& tokens) = 0;

	virtual void run(const StringList &tokens) = 0;
	virtual void stop() = 0;
};


}



#endif
