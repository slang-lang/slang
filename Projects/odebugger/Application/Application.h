
#ifndef ObjectiveScript_odebugger_Application_Application_h
#define ObjectiveScript_odebugger_Application_Application_h


// Library includes

// Project includes
#include <Common/AClient.h>
#include <Common/Settings.h>

// Forward declarations

// Namespace declarations


namespace Slang {


class Application
{
public:
	Application();
	~Application();

public:
	void init(int argc, const char* argv[]);
	int exec();

private:
	void printUsage();
	void printVersion();
	void processParameters(int argc, const char* argv[]);

private:
	AClient* mClient;
	Settings mSettings;
};


}


#endif
