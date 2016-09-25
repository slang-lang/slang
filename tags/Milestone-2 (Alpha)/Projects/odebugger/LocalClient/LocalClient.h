
#ifndef ObjectiveScript_odebugger_LocalClient_LocalClient_h
#define ObjectiveScript_odebugger_LocalClient_LocalClient_h


// Library includes

// Project includes
#include <Common/AClient.h>
#include <Core/Parameter.h>
#include <Core/Scope.h>
#include <Core/Types.h>
#include <Debugger/BreakPoint.h>
#include <Debugger/IReceiver.h>
#include "Watch.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Core {
	class Debugger;
}
class VirtualMachine;

class LocalClient : public AClient,
					public Core::IReceiver
{
public:
	LocalClient();
	~LocalClient();

public:	// AClient implementation
	int exec();

public:
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
	void shutdown();
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

private:
	std::string executeCommand(const StringList &tokens);
	StringList parseCommands(const std::string& commands) const;
	void prepare(const StringList& tokens);
	void printHelp();
	std::string read();
	void start();
	void write(const std::string& text);
	void writeln(const std::string& text);

private:
	bool mContinue;
	Core::Debugger* mDebugger;
	ParameterList mParameters;
	bool mRunning;
	SymbolScope* mScope;
	Symbols mSymbolCollection;
	VirtualMachine* mVirtualMachine;
	WatchCollection mWatches;
};


}


#endif
