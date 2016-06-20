
#ifndef ObjectiveScript_odebugger_Application_Application_h
#define ObjectiveScript_odebugger_Application_Application_h


// Library includes

// Project includes
#include <Backend/Backend.h>
#include <Common/Settings.h>
#include <LocalClient/LocalClient.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


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
	Backend mBackend;
	LocalClient mLocalClient;
	Settings mSettings;
};


}


#endif
