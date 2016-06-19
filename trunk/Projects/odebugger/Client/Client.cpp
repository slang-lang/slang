
// Header
#include "Client.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Script.h>
#include <Core/StackTrace.h>
#include <Core/Tools.h>
#include <Core/Utils/Utils.h>
#include <Core/VirtualMachine.h>
#include <Debugger/Debugger.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>

// Extension includes
#include <Extensions.h>

// Namespace declarations


namespace ObjectiveScript {


Client::Client()
: mDebugger(0),
  mRunning(false),
  mScope(0),
  mVirtualMachine(0)
{
	mDebugger = &ObjectiveScript::Core::Debugger::GetInstance();
}

Client::~Client()
{
	shutdown();

	mDebugger = 0;
}

void Client::addBreakPoint(const StringList& tokens)
{
	if ( tokens.size() != 3 ) {
		std::cout << "invalid number of arguments!" << std::endl;
		return;
	}

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token

	std::string file = (*it++);
	unsigned line = ::Utils::Tools::stringToInt((*it));

	mDebugger->addBreakPoint(Utils::Position(file, line));
}

void Client::continueExecution()
{
	mContinue = true;
}

int Client::exec()
{
	// only start if we have a filename set
	if ( mFilename.empty() ) {
		printUsage();
		return 0;
	}

	// initial checks
	if ( !::Utils::Tools::Files::exists(mFilename) ) {
		OSerror("File '" + mFilename + "' does not exist!");
		return -1;
	}

	assert(mDebugger);
	assert(!mVirtualMachine);

	// start program execution
	while ( mRunning ) {
		runCLI(0);
	}

	return 0;
}

std::string Client::executeCommand(const StringList &tokens)
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
		else if ( cmd == "kill" ) {
			stop();
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
			shutdown();
		}
		else if ( cmd == "resume" || cmd == "r" ) {
			mDebugger->resumeWithoutBreaks();
			continueExecution();
		}
		else if ( cmd == "run" ) {
			prepare(tokens);
			start();
			stop();
		}
		else {
			std::cout << "unknown command '" << cmd << "'" << std::endl;
		}
	}

	return "";
}

void Client::executeSymbol(const StringList& tokens)
{
	if ( !mScope ) {
		std::cout << "no scope available!" << std::endl;
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
				std::cout << "could not resolve symbol '" << name << "'!" << std::endl;
				return;
			}

			if ( symbol->getType() != Symbol::IType::MethodSymbol ) {
				std::cout << "could not execute non-method symbol '" << name << "'!" << std::endl;
				return;
			}

			Runtime::Method* method = static_cast<Runtime::Method*>(symbol);
			try {
				Runtime::Object result;
				method->execute(ParameterList(), &result, Token());

				std::cout << result.ToString() << std::endl;
			}
			catch ( std::exception &e ) {
				std::cout << e.what() << std::endl;
			}
			catch ( ... ) {
				std::cout << "unknown exception occured" << std::endl;
			}
		}

		name = child;
	} while ( !name.empty() );
}

void Client::modifySymbol(const StringList& tokens)
{
	if ( !mScope ) {
		std::cout << "no scope available!" << std::endl;
		return;
	}

	if ( tokens.size() != 3 ) {
		std::cout << "invalid number of arguments!" << std::endl;
		return;
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
				std::cout << "could not resolve symbol '" << name << "'!" << std::endl;
				return;
			}

			Runtime::Object* object = static_cast<Runtime::Object*>(symbol);
			if ( !object->isAtomicType() ) {
				std::cout << "can not modify complex type '" << object->Typename() << "' " << std::endl;
				return;
			}

			object->setValue(Runtime::AtomicValue((*it)));
		}

		name = child;
	} while ( !name.empty() );
}

void Client::init(int argc, const char* argv[])
{
	bool registered = mDebugger->registerReceiver(this);
	assert(registered);

	mRunning = true;

	processParameters(argc, argv);
}

StringList Client::parseCommands(const std::string& commands) const
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

void Client::prepare(const StringList& tokens)
{
	std::string paramStr = mFilename;

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token
	while ( it != tokens.end() ) {
		paramStr += " " + (*it++);
	}

	mParameters.clear();
	mParameters.push_back(ObjectiveScript::Parameter("argc", ObjectiveScript::Runtime::IntegerObject::TYPENAME, 1));
	mParameters.push_back(ObjectiveScript::Parameter("argv", ObjectiveScript::Runtime::StringObject::TYPENAME, paramStr));
}

void Client::printBreakPoints()
{
	Core::BreakPointList list = mDebugger->getBreakPoints();

	std::cout << "BreakPoints:" << std::endl;

	int idx = 1;
	for ( Core::BreakPointList::const_iterator it = list.begin(); it != list.end(); ++it ) {
		std::cout << idx << ": " << it->toString() << std::endl;
		idx++;
	}
}

void Client::printHelp()
{
	std::cout << "Generic commands:" << std::endl;

	std::cout << "\tbreak (b)" << std::endl;
	std::cout << "\tbreakpoints" << std::endl;
	std::cout << "\tdelete (d)" << std::endl;
	std::cout << "\thelp" << std::endl;
	std::cout << "\tquit (q)" << std::endl;
	std::cout << "\trun" << std::endl;

	if ( mScope ) {
		std::cout << "Debugging commands:" << std::endl;
		std::cout << "\tcontinue (c)" << std::endl;
		std::cout << "\texecute (e)" << std::endl;
		std::cout << "\tinto (i)" << std::endl;
		std::cout << "\tkill" << std::endl;
		std::cout << "\tmodify (m)" << std::endl;
		std::cout << "\tnext (n)" << std::endl;
		std::cout << "\tout (o)" << std::endl;
		std::cout << "\tprint (p)" << std::endl;
		std::cout << "\tresume (r)" << std::endl;
	}
}

void Client::printSymbol(const StringList& tokens)
{
	if ( !mScope ) {
		std::cout << "no scope available!" << std::endl;
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
				std::cout << "could not resolve symbol '" << name << "'!" << std::endl;
				return;
			}

			std::cout << symbol->ToString() << std::endl;
		}

		name = child;
	} while ( !name.empty() );
}

void Client::printUsage()
{
	std::cout << "Usage: odebugger [options] [-f] <file> [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "-f | --file <file>    Parse and execute <file>" << std::endl;
	std::cout << "-h | --help           This help" << std::endl;
	std::cout << "-l | --library        Library root path" << std::endl;
	std::cout << "--version             Version information" << std::endl;
	std::cout << std::endl;
}

void Client::printVersion()
{
	std::cout << "ObjectiveScript Debugger 0.3.3 (cli)" << std::endl;
	std::cout << "Copyright (c) 2014-2016 Michael Adelmann" << std::endl;
	std::cout << "" << std::endl;
}

void Client::processParameters(int argc, const char* argv[])
{
	for ( int i = 1; i < argc; i++ ) {
		if ( ::Utils::Tools::StringCompare(argv[i], "-f") || ::Utils::Tools::StringCompare(argv[i], "--file") ) {
			if ( argc <= ++i ) {
				OSerror("invalid number of parameters provided!");

				exit(-1);
			}

			mFilename = argv[i];
		}
		else if ( ::Utils::Tools::StringCompare(argv[i], "-h") || ::Utils::Tools::StringCompare(argv[i], "--help") ) {
			printUsage();

			exit(0);
		}
		else if ( ::Utils::Tools::StringCompare(argv[i], "-l") || ::Utils::Tools::StringCompare(argv[i], "--library") ) {
			if ( argc <= ++i ) {
				OSerror("invalid number of parameters provided!");

				exit(-1);
			}

			mRoot = argv[i];
		}
		else if ( ::Utils::Tools::StringCompare(argv[i], "--version") ) {
			printVersion();

			exit(0);
		}
		else if ( mFilename.empty() ){
			mFilename = argv[i];
		}
	}
}

void Client::removeBreakPoint(const StringList& tokens)
{
	if ( tokens.size() != 2 ) {
		std::cout << "invalid number of arguments!" << std::endl;
		return;
	}

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token

	int idx = ::Utils::Tools::stringToInt((*it));

	Core::BreakPointList points = mDebugger->getBreakPoints();

	int count = 1;
	for ( Core::BreakPointList::const_iterator it = points.begin(); it != points.end(); ++it, ++count ) {
		if ( count == idx ) {
			mDebugger->removeBreakPoint((*it));
			break;
		}
	}
}

int Client::runCLI(SymbolScope* scope)
{
	mContinue = false;
	mScope = scope;

	while ( mRunning && !mContinue ) {
		std::string command;

		std::cout << mSettings.prompt();

		getline(std::cin >> std::ws, command);
		std::cin.clear();

		executeCommand(
			parseCommands(command)
		);
	}

	mScope = 0;

	return 0;
}

void Client::shutdown()
{
	stop();

	mContinue = false;
	mDebugger->unregisterReceiver(this);
	mRunning = false;
	mScope = 0;
}

void Client::start()
{
	if ( mVirtualMachine ) {
		stop();
	}

	mDebugger->resume();
	StackTrace::GetInstance().clear();

	mVirtualMachine = new VirtualMachine();
	mVirtualMachine->setBaseFolder(mRoot);

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
		std::cout << "[Starting program: " << mFilename << "]" << std::endl;

		ObjectiveScript::Script *script = mVirtualMachine->createScriptFromFile(mFilename, mParameters);
		assert(script);

		// check if an instance ("main") of a Main object exists
		ObjectiveScript::Runtime::Object *main = static_cast<ObjectiveScript::Runtime::Object*>(script->resolve("main"));

		if ( !main || main->isAtomicType() ) {
			std::cout << "[Using structured execution mode]" << std::endl;

			ObjectiveScript::Runtime::IntegerObject result;
			script->execute("Main", mParameters, &result);

			std::cout << "[Process finished with exit code " << result.getValue().toStdString() << "]" <<  std::endl;
		}

		std::cout << "[Process exited normally]" << std::endl;
	}
	catch ( std::exception& e ) {
		std::cout << e.what() << std::endl;
	}
}

void Client::stop()
{
	delete mVirtualMachine;
	mVirtualMachine = 0;
}


}
