
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
#include "Watch.h"

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

public:	// Setup
	void connectSettings(Settings* settings);
	void connectTerminal(ITerminal* terminal);

public:
	int exec();
	void shutdown();

public:		// IBackend implementation
	bool addBreakPoint(const StringList& tokens);
	bool removeBreakPoint(const StringList& tokens);

	void continueExecution();
	void executeSymbol(const StringList& tokens);
	Symbol* getSymbol(std::string name) const;
	bool modifySymbol(const StringList& tokens);
	void printBreakPoints();
	void printStackTrace();
	void printSymbol(const StringList& tokens);

	void run(const StringList &tokens);
	void stop();

public:	// IReceiver implementation
	int notify(SymbolScope* scope, const Core::BreakPoint& breakpoint);
	int notifyEnter(SymbolScope* scope, const Core::BreakPoint& breakpoint);
	int notifyException(SymbolScope* scope, const Core::BreakPoint& breakpoint);
	int notifyExit(SymbolScope* scope, const Core::BreakPoint& breakpoint);

private:	// Configuration
	void loadConfig();
	void saveConfig();

private:	// Watches
	bool addWatch(const StringList &tokens);
	void refreshWatches();
	bool removeWatch(const StringList &tokens);
	void toggleAutoWatch();

private:	// Symbol cache
	bool addLiteralSymbol(const std::string& name, const std::string& value);
	Symbol* getCachedSymbol(const std::string& name) const;
	void clearSymbolCache();

private:	// Terminal
	void write(std::string text);
	void writeln(std::string text);

private:
	std::string executeCommand(const StringList &tokens);
	StringList parseCommands(const std::string& commands) const;
	void prepare(const StringList& tokens);
	void printHelp();
	void start();

private:
	bool mAutoWatch;
	bool mBreakOnException;
	bool mContinue;
	Core::Debugger* mDebugger;
	ParameterList mParameters;
	bool mRunning;
	SymbolScope* mScope;
	Symbols mSymbolCollection;
	Settings* mSettings;
	ITerminal* mTerminal;
	VirtualMachine* mVirtualMachine;
	WatchCollection mWatches;
};


}


#endif
