
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

// Forward declarations
class Settings;

class AClient
{
public:
	AClient();
	virtual ~AClient();

public:
	virtual int exec() = 0;

public:
	void connectSettings(Settings* s);

protected:
	Settings* mSettings;
};

}


#endif