
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
	class Event;
	class ProtocolMessage;
	class Request;
	class Response;
}

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Core {
	class IDebugger;
}
class VirtualMachine;

class RemoteClient : public AClient,
					 public Core::IReceiver
{
public:
	RemoteClient();
	~RemoteClient();

public:		// AClient implementation
	int exec();

public:	// IReceiver implementation
	int notify(SymbolScope* scope, const Core::BreakPoint& breakpoint);
	int notifyEnter(SymbolScope* scope, const Core::BreakPoint& breakpoint);
	int notifyExceptionCatch(SymbolScope *scope, const Core::BreakPoint &breakpoint);
	int notifyExceptionThrow(SymbolScope *scope, const Core::BreakPoint &breakpoint);
	int notifyExit(SymbolScope* scope, const Core::BreakPoint& breakpoint);

private:	// Visual Studio Code debugger interface
	void Attach(const VSCodeDebug::Request& request);
	void Continue(const VSCodeDebug::Request& request);
	void Disconnect(const VSCodeDebug::Request& request);
	void Evaluate(const VSCodeDebug::Request& request);
	void Initialize(const VSCodeDebug::Request& request);
	void Launch(const VSCodeDebug::Request& request);
	void Next(const VSCodeDebug::Request& request);
	void Pause(const VSCodeDebug::Request& request);
	void Scopes(const VSCodeDebug::Request& request);
	void Source(const VSCodeDebug::Request& request);
	void SetBreakpoints(const VSCodeDebug::Request& request);
	void SetExceptionBreakpoints(const VSCodeDebug::Request& request);
	void SetFunctionBreakpoints(const VSCodeDebug::Request& request);
	void StepIn(const VSCodeDebug::Request& request);
	void StepOut(const VSCodeDebug::Request& request);
	void StackTrace(const VSCodeDebug::Request& request);
	void Threads(const VSCodeDebug::Request& request);
	void Variables(const VSCodeDebug::Request& request);

private:
	void DispatchRequest(VSCodeDebug::ProtocolMessage* request);
	void SendErrorResponse();
	void SendMessage(VSCodeDebug::ProtocolMessage* message);

private:
	std::string read();
	void start();
	void stop();

private:
	bool mContinue;
	Core::IDebugger* mDebugger;
	ParameterList mParameters;
	bool mRunning;
	SymbolScope* mScope;
	VirtualMachine* mVirtualMachine;
};


}


#endif
