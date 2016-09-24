
#ifndef ObjectiveScript_odebugger_Common_AClient_h
#define ObjectiveScript_odebugger_Common_AClient_h


// Library includes
#include <string>

// Project includes
#include <Core/Types.h>
#include <Interfaces/ITerminal.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class AClient : public ITerminal
{
public:
	AClient();
	virtual ~AClient();

public:
	virtual int exec() = 0;
};

}


#endif
