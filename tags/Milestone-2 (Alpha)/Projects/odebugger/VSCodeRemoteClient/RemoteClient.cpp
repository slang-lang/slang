
// Header
#include "RemoteClient.h"

// Library includes
#include <iostream>

// Project includes
#include <Common/Settings.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Script.h>
#include <Core/StackTrace.h>
#include <Core/VirtualMachine.h>
#include <Debugger/Debugger.h>
#include "Protocol.h"

// Namespace declarations


namespace ObjectiveScript {


RemoteClient::RemoteClient()
: mRunning(true),
  mScope(0),
  mVirtualMachine(0)
{
	mDebugger = &Core::Debugger::GetInstance();
}

RemoteClient::~RemoteClient()
{
}

void RemoteClient::Attach(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);
	response.success = true;

	SendMessage(&response);

	start();
}

void RemoteClient::Continue(const VSCodeDebug::Request& request)
{
	mDebugger->resume();

	mContinue = true;

	VSCodeDebug::Response response(request);
	response.success = true;

	SendMessage(&response);
}

void RemoteClient::Disconnect(const VSCodeDebug::Request& request)
{
	stop();

	mRunning = false;

	if ( mScope ) {
		// hack to exit debugger during an active debugging session
		throw Runtime::ControlFlow::ExitProgram;
	}

	VSCodeDebug::Response response(request);
	response.success = true;

	SendMessage(&response);
}

void RemoteClient::DispatchRequest(VSCodeDebug::ProtocolMessage* request)
{
	if ( !request ) {
		return;
	}

	std::string result;

	VSCodeDebug::Request* r = dynamic_cast<VSCodeDebug::Request*>(request);
	if ( r ) {
		if ( r->command == "attach" ) {
			Attach(*r);
		}
		else if ( r->command == "continue" ) {
			Continue(*r);
		}
		else if ( r->command == "disconnect" ) {
			Disconnect(*r);
		}
		else if ( r->command == "evaluate" ) {
			Evaluate(*r);
		}
		else if ( r->command == "initialize" ) {
			Initialize(*r);
		}
		else if ( r->command == "launch" ) {
			Launch(*r);
		}
		else if ( r->command == "next" ) {
			Next(*r);
		}
		else if ( r->command == "pause" ) {
			Pause(*r);
		}
		else if ( r->command == "scopes" ) {
			Scopes(*r);
		}
		else if ( r->command == "source" ) {
			Source(*r);
		}
		else if ( r->command == "setBreakpoints" ) {
			SetBreakpoints(*r);
		}
		else if ( r->command == "setExceptionBreakpoints" ) {
			SetExceptionBreakpoints(*r);
		}
		else if ( r->command == "setFunctionBreakpoints" ) {
			SetFunctionBreakpoints(*r);
		}
		else if ( r->command == "stepIn" ) {
			StepIn(*r);
		}
		else if ( r->command == "stepOut" ) {
			StepOut(*r);
		}
		else if ( r->command == "stackTrace" ) {
			StackTrace(*r);
		}
		else if ( r->command == "variables" ) {
			Variables(*r);
		}
		else if ( r->command == "threads" ) {
			Threads(*r);
		}
		else {
			// unknown command
		}
	}
}

void RemoteClient::Evaluate(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);

	SendMessage(&response);
}

int RemoteClient::exec()
{
	// initial checks
	assert(mDebugger);
	assert(!mVirtualMachine);

	// start program execution
	while ( mRunning ) {
		notify(0, Core::Debugger::immediateBreakPoint);
	}

	return 0;
}

void RemoteClient::Initialize(const VSCodeDebug::Request& request)
{
	std::string paramStr = mSettings->filename();

	mParameters.clear();
	mParameters.push_back(ObjectiveScript::Parameter("argc", ObjectiveScript::Runtime::IntegerObject::TYPENAME, 1));
	mParameters.push_back(ObjectiveScript::Parameter("argv", ObjectiveScript::Runtime::StringObject::TYPENAME, paramStr));

	VSCodeDebug::Response response(request);
	response.success = true;
	SendMessage(&response);

	VSCodeDebug::Event initialized("initialized");
	SendMessage(&initialized);
}

void RemoteClient::Launch(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);
	response.success = true;

	SendMessage(&response);

	start();
}

void RemoteClient::Next(const VSCodeDebug::Request& request)
{
	mDebugger->stepOver();

	mContinue = true;

	VSCodeDebug::Response response(request);
	response.success = true;

	SendMessage(&response);
}

int RemoteClient::notify(SymbolScope* scope, const Core::BreakPoint& breakpoint)
{
(void)breakpoint;
	mContinue = false;
	mScope = scope;

/*
	// Condition check
	Core::Condition condition = breakpoint.getCondition();
	Symbol* lhs = getSymbol(condition.lhs());
	Symbol* rhs = getSymbol(condition.rhs());

	if ( !condition.lhs().empty() && !lhs ) {
		if ( addLiteralSymbol(condition.lhs(), condition.lhs()) ) {
			lhs = getCachedSymbol(condition.lhs());
		}
	}
	if ( !condition.rhs().empty() && !rhs ) {
		if ( addLiteralSymbol(condition.rhs(), condition.rhs()) ) {
			rhs = getCachedSymbol(condition.rhs());
		}
	}

	if ( condition.isValid() && !condition.evaluate(lhs, rhs) ) {
		mContinue = true;
		mScope = 0;
		return 0;
	}
*/

	mSettings->autoStop(false);

	while ( mRunning && !mContinue ) {
		read();	// read command from remote terminal
	}

	mScope = 0;

	return 0;
}

int RemoteClient::notifyEnter(SymbolScope* scope, const Core::BreakPoint& breakpoint)
{
	return notify(scope, breakpoint);
}

int RemoteClient::notifyException(SymbolScope* scope, const Core::BreakPoint& breakpoint)
{
	return notify(scope, breakpoint);
}

int RemoteClient::notifyExit(SymbolScope* scope, const Core::BreakPoint& breakpoint)
{
	return notify(scope, breakpoint);
}

void RemoteClient::Pause(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);

	SendMessage(&response);
}

std::string RemoteClient::read()
{
	std::string result;

	getline(std::cin >> std::ws, result);
	std::cin.clear();

	VSCodeDebug::MessageConverter converter;
	VSCodeDebug::ProtocolMessage* request = converter.convert(result);

	DispatchRequest(request);

	delete request;

	return "";
}

void RemoteClient::Scopes(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);

	SendMessage(&response);
}

void RemoteClient::SendErrorResponse()
{

}

void RemoteClient::SendMessage(VSCodeDebug::ProtocolMessage* message)
{
	if ( ! message ) {
		return;
	}

	std::cout << message->serialize().toString() << std::endl;
}

void RemoteClient::SetBreakpoints(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);

	SendMessage(&response);
}

void RemoteClient::SetExceptionBreakpoints(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);

	SendMessage(&response);
}

void RemoteClient::SetFunctionBreakpoints(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);

	SendMessage(&response);
}

void RemoteClient::Source(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);

	SendMessage(&response);
}

void RemoteClient::start()
{
	stop();

	mDebugger->breakOnException(mSettings->breakOnException());
	mDebugger->resume();
	StackTrace::GetInstance().clear();

	mVirtualMachine = new VirtualMachine();
	for ( StringSet::const_iterator it = mSettings->libraryFolders().begin(); it != mSettings->libraryFolders().end(); ++it ) {
		mVirtualMachine->addLibraryFolder((*it));
	}

/*
	// add extensions
#ifdef USE_APACHE_EXTENSION
	mVirtualMachine->addExtension(new ObjectiveScript::Extensions::Apache::ApacheExtension());
#endif
#ifdef USE_JSON_EXTENSION
	mVirtualMachine->addExtension(new ObjectiveScript::Extensions::Json::JsonExtension());
#endif
#ifdef USE_MYSQL_EXTENSION
	mVirtualMachine->addExtension(new ObjectiveScript::Extensions::Mysql::MysqlExtension());
#endif
#ifdef USE_SYSTEM_EXTENSION
	mVirtualMachine->addExtension(new ObjectiveScript::Extensions::System::SystemExtension());
#endif
*/

	try {
		ObjectiveScript::Script *script = mVirtualMachine->createScriptFromFile(mSettings->filename(), mParameters);
		assert(script);

		// check if an instance ("main") of a Main object exists
		ObjectiveScript::Runtime::Object *main = static_cast<ObjectiveScript::Runtime::Object*>(script->resolve("main"));

		if ( !main || main->isAtomicType() ) {
			ObjectiveScript::Runtime::IntegerObject result;
			script->execute("Main", mParameters, &result);
		}

		if ( mSettings->autoStop() ) {
			mRunning = false;
		}
	}
	catch ( std::exception& e ) {
		std::cout << e.what() << std::endl;
	}
}

void RemoteClient::stop()
{
	if ( mVirtualMachine ) {
		delete mVirtualMachine;
		mVirtualMachine = 0;
	}
}

void RemoteClient::StepIn(const VSCodeDebug::Request& request)
{
	mDebugger->stepInto();

	mContinue = true;

	VSCodeDebug::Response response(request);
	response.success = true;

	SendMessage(&response);
}

void RemoteClient::StepOut(const VSCodeDebug::Request& request)
{
	mDebugger->stepOut();

	mContinue = true;

	VSCodeDebug::Response response(request);
	response.success = true;

	SendMessage(&response);
}

void RemoteClient::StackTrace(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);

	SendMessage(&response);
}

void RemoteClient::Threads(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);

	SendMessage(&response);
}

void RemoteClient::Variables(const VSCodeDebug::Request& request)
{
	VSCodeDebug::Response response(request);

	SendMessage(&response);
}


}