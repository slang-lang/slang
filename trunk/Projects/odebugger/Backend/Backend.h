
#ifndef ObjectiveScript_odebugger_Backend_Backend_h
#define ObjectiveScript_odebugger_Backend_Backend_h


// Library includes

// Project includes
#include <Core/Parameter.h>
#include <Core/Scope.h>
#include <Core/Types.h>
#include <Debugger/BreakPoint.h>
#include <Debugger/IReceiver.h>
#include <Interfaces/ITerminal.h>
#include "IBackend.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Core {
	class Debugger;
}
class Settings;
class VirtualMachine;

class Backend : public IBackend,
				public Core::IReceiver
{
public:
	Backend();
	~Backend();

public:
	void connectSettings(Settings* settings);
	void connectTerminal(ITerminal* terminal);
	int exec();
	void shutdown();

public:		// IBackend implementation
	bool addBreakPoint(const StringList& tokens);
	bool removeBreakPoint(const StringList& tokens);

	void continueExecution();
	void executeSymbol(const StringList& tokens);
	bool modifySymbol(const StringList& tokens);
	void printBreakPoints();
	void printSymbol(const StringList& tokens);

	void run(const StringList &tokens);
	void stop();

public:	// IReceiver implementation
	int runCLI(SymbolScope* scope);

private:
	std::string executeCommand(const StringList &tokens);
	StringList parseCommands(const std::string& commands) const;
	void prepare(const StringList& tokens);
	void printHelp();
	void start();

private:
	bool mContinue;
	Core::Debugger* mDebugger;
	ParameterList mParameters;
	bool mRunning;
	SymbolScope* mScope;
	Settings* mSettings;
	ITerminal* mTerminal;
	VirtualMachine* mVirtualMachine;
};


}


#endif
