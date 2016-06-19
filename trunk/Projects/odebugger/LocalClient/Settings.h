
#ifndef ObjectiveScript_Debugger_LocalClient_Settings_h
#define ObjectiveScript_Debugger_LocalClient_Settings_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Settings
{
public:
	Settings()
	{
		mPrompt = "odebugger> ";
	}

public:
	const std::string& prompt() {
		return mPrompt;
	}

private:
	std::string mPrompt;
};


}


#endif
