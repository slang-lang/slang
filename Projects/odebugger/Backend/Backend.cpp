
// Header
#include "Backend.h"

// Library includes

// Project includes
#include <Common/Settings.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Script.h>
#include <Core/StackTrace.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine.h>
#include <Debugger/Debugger.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>

// Extension includes
#include <Extensions.h>

// Namespace declarations


namespace ObjectiveScript {


Backend::Backend()
: mContinue(false),
  mDebugger(0),
  mRunning(true),
  mScope(0),
  mSettings(0),
  mTerminal(0),
  mVirtualMachine(0)
{
	mDebugger = &ObjectiveScript::Core::Debugger::GetInstance();
}

Backend::~Backend()
{
	shutdown();

	mDebugger = 0;
}

bool Backend::addBreakPoint(const StringList& tokens)
{
	if ( tokens.size() != 3 ) {
		mTerminal->writeln("invalid number of arguments!");
		return false;
	}

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token

	std::string file = (*it++);
	unsigned line = ::Utils::Tools::stringToInt((*it));

	mDebugger->addBreakPoint(Utils::Position(file, line));

	return true;
}

void Backend::connectSettings(Settings *settings)
{
	assert(settings);
	assert(!mSettings);

	mSettings = settings;
}

void Backend::connectTerminal(ITerminal* terminal)
{
	assert(terminal);
	assert(!mTerminal);

	mTerminal = terminal;
}

void Backend::continueExecution()
{
	mContinue = true;
}

int Backend::exec()
{
	assert(mDebugger);
	assert(!mVirtualMachine);

	// start program execution
	while ( mRunning ) {
		runCLI(0);
	}

	return 0;
}

std::string Backend::executeCommand(const StringList &tokens)
{
	StringList::const_iterator it = tokens.begin();

	if ( it != tokens.end() ) {
		std::string cmd = (*it++);

		if ( cmd == "break" || cmd == "b" ) {
			addBreakPoint(tokens);
		}
		else if ( cmd == "breakpoints" ) {
			printBreakPoints();
		}
		else if ( cmd == "continue" || cmd == "c" ) {
			mDebugger->resume();
			continueExecution();
		}
		else if ( cmd == "delete" || cmd == "d" ) {
			removeBreakPoint(tokens);
		}
		else if ( cmd == "execute" || cmd == "e" ) {
			executeSymbol(tokens);
		}
		else if ( cmd == "help" ) {
			printHelp();
		}
		else if ( cmd == "into" || cmd == "i" ) {
			mDebugger->stepInto();
			continueExecution();
		}
		else if ( cmd == "modify" || cmd == "m" ) {
			modifySymbol(tokens);
		}
		else if ( cmd == "next" || cmd == "n" ) {
			mDebugger->stepOver();
			continueExecution();
		}
		else if ( cmd == "out" || cmd == "o" ) {
			mDebugger->stepOut();
			continueExecution();
		}
		else if ( cmd == "print" || cmd == "p" ) {
			printSymbol(tokens);
		}
		else if ( cmd == "quit" || cmd == "q" ) {
			mRunning = false;

			if ( mScope ) {
				throw Runtime::ControlFlow::ExitProgram;
			}
		}
		else if ( cmd == "resume" || cmd == "r" ) {
			mDebugger->resumeWithoutBreaks();
			continueExecution();
		}
		else if ( cmd == "run" ) {
			run(tokens);
		}
		else {
			mTerminal->writeln("unknown command '" + cmd + "'");
		}
	}

	return "";
}

void Backend::executeSymbol(const StringList& tokens)
{
	if ( !mScope ) {
		mTerminal->writeln("no scope available!");
		return;
	}

	std::string name;

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token
	if ( it != tokens.end() ) {
		name = (*it);
	}

	std::string child;
	std::string parent;
	Symbol* symbol = 0;
	SymbolScope* scope = mScope;

	do {
		Tools::split(name, parent, child);

		if ( !parent.empty() && !child.empty() ) {
			scope = static_cast<ObjectiveScript::Runtime::Object*>(scope->resolve(parent, false));
		}
		else {
			symbol = scope->resolve(parent, false);
			if ( !symbol ) {
				mTerminal->writeln("could not resolve symbol '" + name + "'!");
				return;
			}

			if ( symbol->getType() != Symbol::IType::MethodSymbol ) {
				mTerminal->writeln("could not execute non-method symbol '" + name + "'!");
				return;
			}

			Runtime::Method* method = static_cast<Runtime::Method*>(symbol);
			try {
				Runtime::Object result;
				method->execute(ParameterList(), &result, Token());

				mTerminal->writeln(result.ToString());
			}
			catch ( std::exception &e ) {
				mTerminal->writeln(e.what());
			}
			catch ( ... ) {
				mTerminal->writeln("unknown exception occured");
			}
		}

		name = child;
	} while ( !name.empty() );
}

bool Backend::modifySymbol(const StringList& tokens)
{
	if ( !mScope ) {
		mTerminal->writeln("no scope available!");
		return false;
	}

	if ( tokens.size() != 3 ) {
		mTerminal->writeln("invalid number of arguments!");
		return false;
	}

	std::string name;

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token
	if ( it != tokens.end() ) {
		name = (*it++);
	}

	std::string child;
	std::string parent;
	Symbol* symbol = 0;
	SymbolScope* scope = mScope;

	do {
		Tools::split(name, parent, child);

		if ( !parent.empty() && !child.empty() ) {
			scope = static_cast<ObjectiveScript::Runtime::Object*>(scope->resolve(parent, false));
		}
		else {
			symbol = scope->resolve(parent, false);
			if ( !symbol ) {
				mTerminal->writeln("could not resolve symbol '" + name + "'!");
				return false;
			}

			Runtime::Object* object = static_cast<Runtime::Object*>(symbol);
			if ( !object->isAtomicType() ) {
				mTerminal->writeln("can not modify complex type '" + object->Typename() + "' ");
				return false;
			}

			object->setValue(Runtime::AtomicValue((*it)));
			return true;
		}

		name = child;
	} while ( !name.empty() );

	return false;
}

StringList Backend::parseCommands(const std::string& commands) const
{
	StringList params;

	// read in parameters
	unsigned count = 0;
	std::string token;

	while ( count < commands.size() ) {
		char c = commands[count];

		if ( c == ' ' ) {
			if ( !token.empty() ) {
				params.push_back(token);
			}
			token = "";
		}
		else {
			token += c;
		}

		count++;
	}

	// add last token
	if ( !token.empty() ) {
		params.push_back(token);
	}

	return params;
}

void Backend::prepare(const StringList& tokens)
{
	std::string paramStr = mSettings->filename();

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token
	while ( it != tokens.end() ) {
		paramStr += " " + (*it++);
	}

	mParameters.clear();
	mParameters.push_back(ObjectiveScript::Parameter("argc", ObjectiveScript::Runtime::IntegerObject::TYPENAME, 1));
	mParameters.push_back(ObjectiveScript::Parameter("argv", ObjectiveScript::Runtime::StringObject::TYPENAME, paramStr));
}

void Backend::printBreakPoints()
{
	Core::BreakPointList list = mDebugger->getBreakPoints();

	mTerminal->writeln("BreakPoints:");

	int idx = 1;
	for ( Core::BreakPointList::const_iterator it = list.begin(); it != list.end(); ++it ) {
		mTerminal->writeln(Tools::toString(idx) + ": " + it->toString());
		idx++;
	}
}

void Backend::printHelp()
{
	mTerminal->writeln("Generic commands:");

	mTerminal->writeln("\tbreak (b)");
	mTerminal->writeln("\tbreakpoints");
	mTerminal->writeln("\tdelete (d)");
	mTerminal->writeln("\thelp");
	mTerminal->writeln("\tquit (q)");
	mTerminal->writeln("\trun");

	if ( mScope ) {
		mTerminal->writeln("Debugging commands:");
		mTerminal->writeln("\tcontinue (c)");
		mTerminal->writeln("\texecute (e)");
		mTerminal->writeln("\tinto (i)");
		mTerminal->writeln("\tmodify (m)");
		mTerminal->writeln("\tnext (n)");
		mTerminal->writeln("\tout (o)");
		mTerminal->writeln("\tprint (p)");
		mTerminal->writeln("\tresume (r)");
	}
}

void Backend::printSymbol(const StringList& tokens)
{
	if ( !mScope ) {
		mTerminal->writeln("no scope available!");
		return;
	}

	std::string name;

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token
	if ( it != tokens.end() ) {
		name = (*it);
	}

	std::string child;
	std::string parent;
	Symbol* symbol = 0;
	SymbolScope* scope = mScope;

	do {
		Tools::split(name, parent, child);

		if ( !parent.empty() && !child.empty() ) {
			scope = static_cast<ObjectiveScript::Runtime::Object*>(scope->resolve(parent, false));
		}
		else {
			symbol = scope->resolve(parent, false);
			if ( !symbol ) {
				mTerminal->writeln("could not resolve symbol '" + name + "'!");
				return;
			}

			mTerminal->writeln(symbol->ToString());
		}

		name = child;
	} while ( !name.empty() );
}

bool Backend::removeBreakPoint(const StringList& tokens)
{
	if ( tokens.size() != 2 ) {
		mTerminal->writeln("invalid number of arguments!");
		return false;
	}

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token

	int idx = ::Utils::Tools::stringToInt((*it));

	Core::BreakPointList points = mDebugger->getBreakPoints();

	int count = 1;
	for ( Core::BreakPointList::const_iterator it = points.begin(); it != points.end(); ++it, ++count ) {
		if ( count == idx ) {
			mDebugger->removeBreakPoint((*it));
			return true;
		}
	}

	return false;
}

void Backend::run(const StringList& tokens)
{
	prepare(tokens);

	start();

	stop();
}

int Backend::runCLI(SymbolScope* scope)
{
	mContinue = false;
	mScope = scope;

	while ( mRunning && !mContinue ) {
		mTerminal->write(mSettings->prompt());

		std::string command = mTerminal->read();

		executeCommand(
			parseCommands(command)
		);
	}

	mScope = 0;

	return 0;
}

void Backend::shutdown()
{
	stop();

	mContinue = false;
	mDebugger->unregisterReceiver(this);
	mRunning = false;
	mScope = 0;
}

void Backend::start()
{
	stop();

	mDebugger->resume();
	StackTrace::GetInstance().clear();

	mVirtualMachine = new VirtualMachine();
	mVirtualMachine->setBaseFolder(mSettings->root());

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

	try {
		mTerminal->writeln("[Starting program: " + mSettings->filename() + "]");

		ObjectiveScript::Script *script = mVirtualMachine->createScriptFromFile(mSettings->filename(), mParameters);
		assert(script);

		// check if an instance ("main") of a Main object exists
		ObjectiveScript::Runtime::Object *main = static_cast<ObjectiveScript::Runtime::Object*>(script->resolve("main"));

		if ( !main || main->isAtomicType() ) {
			mTerminal->writeln("[Using structured execution mode]");

			ObjectiveScript::Runtime::IntegerObject result;
			script->execute("Main", mParameters, &result);

			mTerminal->writeln("[Process finished with exit code " + result.getValue().toStdString() + "]");
		}

		mTerminal->writeln("[Process exited normally]");
	}
	catch ( std::exception& e ) {
		mTerminal->writeln(e.what());
	}
}

void Backend::stop()
{
	if ( mVirtualMachine ) {
		delete mVirtualMachine;
		mVirtualMachine = 0;
	}
}


}
