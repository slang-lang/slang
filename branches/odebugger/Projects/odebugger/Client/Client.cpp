
// Header
#include "Client.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Utils/Utils.h>
#include <Core/VirtualMachine.h>
#include <Debugger/Debugger.h>
#include <Debugger/IReceiver.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>

// Extension includes
#ifdef USE_APACHE_EXTENSION
#	include <Apache/ApacheExtension.h>
#endif
#ifdef USE_JSON_EXTENSION
#	include <JSON/JsonExtension.h>
#endif
#ifdef USE_MYSQL_EXTENSION
#	include <Mysql/MysqlExtension.h>
#endif
#ifdef USE_SYSTEM_EXTENSION
#	include <System/SystemExtension.h>
#endif

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

/*
	// add dummy break point
	mDebugger->addBreakPoint(Core::BreakPoint(
		Utils::Position(mFilename, 7)
	));
*/

	// start program execution
	while ( mRunning ) {
		runCLI(0);
	}

	return 0;
}

void Client::init(int argc, const char* argv[])
{
	mDebugger->registerReceiver(this);

	mRunning = true;

	processParameters(argc, argv);
}

std::string Client::execute(const std::string& commands)
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

	// analyse parameters
	StringList::const_iterator it = params.begin();
	if ( it != params.end() ) {
		std::string cmd = (*it++);

		if ( cmd == "break" || cmd == "b" ) {
			addBreakPoint(params);
		}
		else if ( cmd == "breakpoints" ) {
			printBreakPoints();
		}
		else if ( cmd == "continue" || cmd == "c" ) {
			mDebugger->resume();
			continueExecution();
		}
		else if ( cmd == "delete" || cmd == "d" ) {
			removeBreakPoint(params);
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
		else if ( cmd == "next" || cmd == "n" ) {
			mDebugger->stepOver();
			continueExecution();
		}
		else if ( cmd == "out" || cmd == "o" ) {
			mDebugger->stepOut();
			continueExecution();
		}
		else if ( cmd == "print" || cmd == "p" ) {
			printSymbol(params);
		}
		else if ( cmd == "quit" || cmd == "q" ) {
			shutdown();
		}
		else if ( cmd == "run" || cmd == "r" ) {
			prepare(params);
			start();
			std::cout << "program terminated successfully" << std::endl;
			stop();
		}
		else {
			std::cout << "unknown command '" << cmd << "'" << std::endl;
		}
	}

	return "";
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
		std::cout << idx << ": " << it->getFilename() << ":" << it->getLine() << std::endl;
		idx++;
	}
}

void Client::printHelp()
{
	std::cout << "Commands:" << std::endl;
	std::cout << "\tbreak (b)" << std::endl;
	std::cout << "\tbreakpoints" << std::endl;
	std::cout << "\tcontinue (c)" << std::endl;
	std::cout << "\tdelete (d)" << std::endl;
	std::cout << "\thelp" << std::endl;
	std::cout << "\tinto (i)" << std::endl;
	std::cout << "\tkill" << std::endl;
	std::cout << "\tnext (n)" << std::endl;
	std::cout << "\tout (o)" << std::endl;
	std::cout << "\tprint (p)" << std::endl;
	std::cout << "\tquit (q)" << std::endl;
	std::cout << "\trun (r)" << std::endl;
	std::cout << std::endl;
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

	Symbol* symbol = mScope->resolve(name, false);
	if ( !symbol ) {
		std::cout << "could not resolve symbol '" << name << "'!" << std::endl;
		return;
	}

	std::cout << symbol->ToString() << std::endl;
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
	std::cout << "ObjectiveScript Debugger 0.0.0 (cli)" << std::endl;
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

		execute(command);
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

	mVirtualMachine->createScriptFromFile(mFilename, mParameters);
}

void Client::stop()
{
	delete mVirtualMachine;
	mVirtualMachine = 0;
}


}
