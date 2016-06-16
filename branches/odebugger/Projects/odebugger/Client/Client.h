
#ifndef Client_Client_h
#define Client_Client_h


// Library includes

// Project includes
#include <Core/Parameter.h>
#include <Core/Types.h>
#include <Debugger/IReceiver.h>
#include <Core/Scope.h>
#include "Settings.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Core {
	class Debugger;
}
class VirtualMachine;

class Client : private Core::IReceiver
{
public:
	Client();
	~Client();

public:
	void init(int argc, const char* argv[]);
	int exec();
	void shutdown();

	void printHelp();
	void printUsage();
	void printVersion();

private:	// IReceiver implementation
	int runCLI(SymbolScope* scope);

private:
	void continueExecution();
	std::string execute(const std::string& commands);
	void printSymbol(const StringList& tokens);
	void processParameters(int argc, const char* argv[]);
	void prepare(const StringList& tokens);
	void start();
	void stop();

private:
	bool mContinue;
	Core::Debugger* mDebugger;
	std::string mFilename;
	ParameterList mParameters;
	std::string mRoot;
	bool mRunning;
	SymbolScope* mScope;
	Settings mSettings;
	VirtualMachine* mVirtualMachine;
};


}


#endif
