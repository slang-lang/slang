
// Header
#include "RemoteClient.h"

// Library includes
#include <iostream>

// Project includes
#include <Common/Settings.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/VirtualMachine/VirtualMachine.h>
#include <Debugger/Debugger.h>
#include "Protocol.h"

// Namespace declarations

// Extension includes
#include <Extensions.h>
#include <Tools/Strings.h>


namespace Slang {


RemoteClient::RemoteClient()
: mContinue(false),
  mRunning(true),
  mScope(nullptr),
  mVirtualMachine(0)
{
	mDebugger = &Core::Debugger::Instance();
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

	//std::string result;

	auto* r = dynamic_cast<VSCodeDebug::Request*>(request);
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

	std::string name;

	Symbol* symbol = getSymbol(name);
	if ( !symbol ) {

	}

	SendMessage(&response);
}

int RemoteClient::exec()
{
	// initial checks
	assert(mDebugger);
	assert(!mVirtualMachine);

	// start program execution
	while ( mRunning ) {
		notify(nullptr, Core::Debugger::immediateBreakPoint);
	}

	return 0;
}

Symbol* RemoteClient::getSymbol(std::string name) const
{
	std::string child;
	std::string parent;
	IScope* scope = mScope;

	do {
		if ( !scope ) {
			return nullptr;
		}

		Utils::Tools::split(name, parent, child);

		if ( !parent.empty() && !child.empty() ) {
			scope = dynamic_cast<Slang::Runtime::Object*>(scope->resolve(parent, false, Visibility::Private));
		}
		else {
			return scope->resolve(parent, false, Visibility::Private);
		}

		name = child;
	} while ( !name.empty() );

	return nullptr;
}

void RemoteClient::Initialize(const VSCodeDebug::Request& request)
{
	std::string paramStr = mSettings->filename();

	mParameters.clear();
	mParameters.push_back(Slang::Parameter::CreateRuntime(Slang::Runtime::IntegerObject::TYPENAME, 1));
	mParameters.push_back(Slang::Parameter::CreateRuntime(Slang::Runtime::StringObject::TYPENAME, paramStr));

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

int RemoteClient::notify(IScope* scope, const Core::BreakPoint& /*breakpoint*/)
{
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

	mScope = nullptr;

	return 0;
}

int RemoteClient::notifyEnter(IScope* scope, const Core::BreakPoint& breakpoint)
{
	return notify(scope, breakpoint);
}

int RemoteClient::notifyExceptionCatch(IScope *scope, const Core::BreakPoint &breakpoint)
{
	return notify(scope, breakpoint);
}

int RemoteClient::notifyExceptionThrow(IScope *scope, const Core::BreakPoint &breakpoint)
{
	return notify(scope, breakpoint);
}

int RemoteClient::notifyExit(IScope* scope, const Core::BreakPoint& breakpoint)
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

	mDebugger->breakOnExceptionCatch(mSettings->breakOnExceptionCatch());
	mDebugger->breakOnExceptionThrow(mSettings->breakOnExceptionThrow());
	mDebugger->init();

	mVirtualMachine = new VirtualMachine();
	for ( const auto& it : mSettings->libraryFolders() ) {
		mVirtualMachine->addLibraryFolder(it);
	}

	// add extensions
#ifdef USE_JSON_EXTENSION
	mVirtualMachine->addExtension(new Slang::Extensions::Json::JsonExtension());
#endif
#ifdef USE_SYSTEM_EXTENSION
	mVirtualMachine->addExtension(new Slang::Extensions::System::SystemExtension());
#endif

	try {
		Runtime::Object result;

		Script *script = mVirtualMachine->createScriptFromFile(mSettings->filename());
		assert(script);

		mVirtualMachine->run(script, mParameters, &result);

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
		mVirtualMachine = nullptr;
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
