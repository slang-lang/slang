
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
  mSettings(0),
  mVirtualMachine(0)
{
	mDebugger = &Core::Debugger::GetInstance();
}

RemoteClient::~RemoteClient()
{
}

void RemoteClient::Attach()
{
	start();
}

void RemoteClient::connectSettings(Settings* s)
{
	mSettings = s;
}

void RemoteClient::Continue()
{
	mDebugger->resume();

	mContinue = true;
}

void RemoteClient::Disconnect()
{
	stop();

	mRunning = false;

	if ( mScope ) {
		// hack to exit debugger during an active debugging session
		throw Runtime::ControlFlow::ExitProgram;
	}
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
			Attach();
		}
		else if ( r->command == "continue" ) {
			Continue();
		}
		else if ( r->command == "disconnect" ) {
			Disconnect();
		}
		else if ( r->command == "evaluate" ) {
			Evaluate(/*request*/);
		}
		else if ( r->command == "initialize" ) {
			Initialize(/*request*/);
		}
		else if ( r->command == "launch" ) {
			Launch();
		}
		else if ( r->command == "next" ) {
			Next();
		}
		else if ( r->command == "pause" ) {
			Pause();
		}
		else if ( r->command == "scopes" ) {
			Scopes();
		}
		else if ( r->command == "source" ) {
			Source(/*request*/);
		}
		else if ( r->command == "setBreakpoints" ) {
			SetBreakpoints(/*request*/);
		}
		else if ( r->command == "setExceptionBreakpoints" ) {
			SetExceptionBreakpoints(/*request*/);
		}
		else if ( r->command == "setFunctionBreakpoints" ) {
			SetFunctionBreakpoints(/*request*/);
		}
		else if ( r->command == "stepIn" ) {
			StepIn();
		}
		else if ( r->command == "stepOut" ) {
			StepOut();
		}
		else if ( r->command == "stackTrace" ) {
			StackTrace();
		}
		else if ( r->command == "variables" ) {
			Variables();
		}
		else if ( r->command == "threads" ) {
			Threads();
		}
		else {
			// unknown command
		}
	}
}

void RemoteClient::Evaluate()
{

}

int RemoteClient::exec()
{
	// initial checks
	assert(mDebugger);
	assert(!mVirtualMachine);

	// store previous autostart value
	bool autostart = mSettings->autoStart();

	//loadConfig();

	// set autostart even though disabled by configuration
	mSettings->autoStart(autostart || mSettings->autoStart());

	// register SIGINT handle
	//signal(SIGINT, handleSIGINT);

	// start program execution
	while ( mRunning ) {
		notify(0, Core::Debugger::immediateBreakPoint);
	}

	// unregister SIGINT handler
	//signal(SIGINT, 0);

	return 0;
}

void RemoteClient::Initialize()
{
	std::string paramStr = mSettings->filename();

	mParameters.clear();
	mParameters.push_back(ObjectiveScript::Parameter("argc", ObjectiveScript::Runtime::IntegerObject::TYPENAME, 1));
	mParameters.push_back(ObjectiveScript::Parameter("argv", ObjectiveScript::Runtime::StringObject::TYPENAME, paramStr));
}

void RemoteClient::Launch()
{
	start();
}

void RemoteClient::Next()
{
	mDebugger->stepOver();

	mContinue = true;
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
	writeln("[Stepping into " + StackTrace::GetInstance().currentStackLevel().toString() + "]");

	return notify(scope, breakpoint);
}

int RemoteClient::notifyException(SymbolScope* scope, const Core::BreakPoint& breakpoint)
{
	writeln("[Exception has been thrown in " + StackTrace::GetInstance().currentStackLevel().toString() + "]");

	return notify(scope, breakpoint);
}

int RemoteClient::notifyExit(SymbolScope* scope, const Core::BreakPoint& breakpoint)
{
	writeln("[Stepping out of " + StackTrace::GetInstance().currentStackLevel().toString() + "]");

	return notify(scope, breakpoint);
}

void RemoteClient::Pause()
{

}

std::string RemoteClient::read()
{
	std::string result;

	getline(std::cin >> std::ws, result);
	std::cin.clear();

	VSCodeDebug::MessageConverter converter;
	VSCodeDebug::ProtocolMessage* request = converter.convert(result);

	DispatchRequest(request);

	return "";
}

void RemoteClient::Scopes()
{

}

void RemoteClient::SendErrorResponse()
{

}

void RemoteClient::SendResponse()
{
/*
	VSCodeDebug::MessageConverter converter;
	VSCodeDebug::ProtocolMessage* response = converter.convert("response " + text);

	VSCodeDebug::Response* r = dynamic_cast<VSCodeDebug::Response*>(response);
	if ( r ) {
		Json::Value result;

		result.addMember("success", r->success);


		std::cout << result.toString() << std::endl;
	}
*/
}

void RemoteClient::SetBreakpoints()
{

}

void RemoteClient::SetExceptionBreakpoints()
{

}

void RemoteClient::SetFunctionBreakpoints()
{

}

void RemoteClient::Source()
{

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
		writeln(e.what());
	}
}

void RemoteClient::stop()
{
	if ( mVirtualMachine ) {
		delete mVirtualMachine;
		mVirtualMachine = 0;
	}
}

void RemoteClient::StepIn()
{
	mDebugger->stepInto();

	mContinue = true;
}

void RemoteClient::StepOut()
{
	mDebugger->stepOut();

	mContinue = true;
}

void RemoteClient::StackTrace()
{

}

void RemoteClient::Threads()
{

}

void RemoteClient::Variables()
{

}


}
