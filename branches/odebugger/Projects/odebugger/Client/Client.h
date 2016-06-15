
#ifndef Client_Client_h
#define Client_Client_h


// Library includes

// Project includes
#include <Core/VirtualMachine.h>
#include <Debugger/Debugger.h>
#include "Settings.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Client
{
public:
	Client();
	~Client();

public:
	void init(int argc, const char* argv[]);
	void exec();
	void printUsage();
	void printVersion();
	void shutdown();

private:
	std::string execute(const std::string& cmd);
	void processParameters(int argc, const char* argv[]);
	void start();

private:
	Core::Debugger* mDebugger;
	std::string mFilename;
	ParameterList mParameters;
	std::string mRoot;
	bool mRunning;
	Settings mSettings;
	VirtualMachine mVirtualMachine;
};


}


#endif
