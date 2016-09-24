
#ifndef ObjectiveScript_odebugger_RemoteClient_RemoteClient_h
#define ObjectiveScript_odebugger_RemoteClient_RemoteClient_h


// Library includes
#include <string>

// Project includes
#include <Common/AClient.h>
#include <Core/Parameter.h>
#include <Core/Types.h>
#include <Debugger/IReceiver.h>

// Forward declarations
namespace VSCodeDebug {
	class ProtocolMessage;
}

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Core {
	class IDebugger;
}
class Settings;
class VirtualMachine;

class RemoteClient : public AClient,
					 public Core::IReceiver
{
public:
	RemoteClient();
	~RemoteClient();

public:
	void connectSettings(Settings* s);

	int exec();

public:		// ITerminal implementation
	std::string read();
	void write(const std::string& /*text*/) { }
	void writeln(const std::string& /*text*/) { }

public:	// IReceiver implementation
	int notify(SymbolScope* scope, const Core::BreakPoint& breakpoint);
	int notifyEnter(SymbolScope* scope, const Core::BreakPoint& breakpoint);
	int notifyException(SymbolScope* scope, const Core::BreakPoint& breakpoint);
	int notifyExit(SymbolScope* scope, const Core::BreakPoint& breakpoint);

private:	// Visual Studio Code debugger interface
	void Attach();
	void Continue();
	void Disconnect();
	void Evaluate();
	void Initialize();
	void Launch();
	void Next();
	void Pause();
	void Scopes();
	void Source();
	void SetBreakpoints();
	void SetExceptionBreakpoints();
	void SetFunctionBreakpoints();
	void StepIn();
	void StepOut();
	void StackTrace();
	void Threads();
	void Variables();

private:
	void DispatchRequest(VSCodeDebug::ProtocolMessage* request);
	void SendErrorResponse();
	void SendResponse();

private:
	void start();
	void stop();

private:
	bool mContinue;
	Core::IDebugger* mDebugger;
	ParameterList mParameters;
	bool mRunning;
	SymbolScope* mScope;
	Settings* mSettings;
	VirtualMachine* mVirtualMachine;
};


}


#endif
