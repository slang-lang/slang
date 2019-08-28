
#ifndef ObjectiveScript_odebugger_LocalClient_LocalClient_h
#define ObjectiveScript_odebugger_LocalClient_LocalClient_h


// Library includes

// Project includes
#include <Common/AClient.h>
#include <Core/Common/Types.h>
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
namespace Runtime {
	class Namespace;
	class Object;
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

	void executeMethod(const StringList &tokens);
	MethodSymbol* getMethod(std::string name, const ParameterList& params) const;
	Symbol* getSymbol(std::string name) const;
	bool modifySymbol(const StringList& tokens);
	void setCurrentFrame(Common::FrameId frameId);
	void setCurrentFrame(const StringList& tokens);
	void setCurrentThread(Common::ThreadId threadId);
	void setCurrentThread(const StringList& tokens);

    void continueExecution();
	void run(const StringList &tokens);
	void shutdown();
    void start();
	void stop();

public:	// IReceiver implementation
	int notify(IScope* scope, const Core::BreakPoint& breakpoint);
	int notifyEnter(IScope* scope, const Core::BreakPoint& breakpoint);
	int notifyExceptionCatch(IScope *scope, const Core::BreakPoint &breakpoint);
	int notifyExceptionThrow(IScope *scope, const Core::BreakPoint &breakpoint);
	int notifyExit(IScope* scope, const Core::BreakPoint& breakpoint);

    int handleBreakpoint(IScope* scope, const Core::BreakPoint& breakpoint);

private:	// Configuration
	void loadConfig();
	void saveConfig();

private:	// Scopes
	MethodScope* getEnclosingMethodScope(IScope* scope) const;
	Runtime::Namespace* getEnclosingNamespace(IScope* scope) const;
	Runtime::Object* getEnclosingObject(IScope* scope) const;
	Common::Method* getMethodFromScope(IScope *scope) const;

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
    void printBreakPoints();
    void printScope(IScope* scope);
    void printStackTrace();
    void printSymbol(const StringList& tokens);
    void printThreads();
    void printWatches();
	std::string read();
	void toggleAutoList();
	void toggleAutoStart();
	void toggleAutoStop();
	void write(const std::string& text);
	void writeln(const std::string& text);

private:
	Core::BreakPoint mBreakpoint;
	bool mContinue;
	Common::FrameId mCurrentFrameId;
	Common::ThreadId mCurrentThreadId;
	Core::Debugger* mDebugger;
	ParameterList mParameters;
	bool mRunning;
	IScope* mScope;
	Symbols mSymbolCollection;
	VirtualMachine* mVirtualMachine;
	WatchCollection mWatches;
};


}


#endif
