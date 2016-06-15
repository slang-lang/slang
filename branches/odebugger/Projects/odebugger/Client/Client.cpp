
// Header
#include "Client.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
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
: mRunning(false)
{
	mDebugger = &ObjectiveScript::Core::Debugger::GetInstance();
	mDebugger->stepInto();
}

Client::~Client()
{
	mDebugger = 0;
}

void Client::init(int argc, const char* argv[])
{
	mRunning = true;

/*
	StringList params;

	// read in parameters
	for ( int i = 0; i < argc; i++ ) {
		params.push_back(argv[i]);
	}

	// analyse parameters
	StringList::const_iterator it = params.begin();
	it++;
	while (  it != params.end() ) {
		// TODO: parse parameters
	}
*/

	processParameters(argc, argv);

	mVirtualMachine.setBaseFolder(mRoot);

	// add extensions
#ifdef USE_APACHE_EXTENSION
	mVirtualMachine.addExtension(new ObjectiveScript::Extensions::Apache::ApacheExtension());
#endif
#ifdef USE_JSON_EXTENSION
	mVirtualMachine.addExtension(new ObjectiveScript::Extensions::Json::JsonExtension());
#endif
#ifdef USE_MYSQL_EXTENSION
	mVirtualMachine.addExtension(new ObjectiveScript::Extensions::Mysql::MysqlExtension());
#endif
#ifdef USE_SYSTEM_EXTENSION
	mVirtualMachine.addExtension(new ObjectiveScript::Extensions::System::SystemExtension());
#endif
}

void Client::exec()
{
	assert(mDebugger);

	// add dummy break point
	mDebugger->addBreakPoint(ObjectiveScript::Core::BreakPoint(
			ObjectiveScript::Utils::Position(mFilename, 7)
	));

	while ( mRunning ) {
		std::string command;

		std::cout << mSettings.prompt();

		getline(std::cin >> std::ws, command);
		std::cin.clear();

		std::string result = execute(command);
		if ( !result.empty() ) {
			std::cout << result << std::endl;
		}
	}
}

std::string Client::execute(const std::string& cmd)
{
	if ( cmd == "into" ) {
		mDebugger->stepInto();
	}
	else if ( cmd == "out" ) {
		mDebugger->stepOut();
	}
	else if ( cmd == "over" ) {
		mDebugger->stepOut();
	}
	else if ( cmd == "quit" ) {
		mRunning = false;
	}
	else if ( cmd == "resume" ) {
		mDebugger->resume();
	}
	else if ( cmd == "start" ) {
		start();
	}

	return "";
}

void Client::processParameters(int argc, const char* argv[])
{
	for ( int i = 1; i < argc; i++ ) {
		if ( ::Utils::Tools::StringCompare(argv[i], "-f") || ::Utils::Tools::StringCompare(argv[i], "--file") ) {
			if ( argc <= ++i ) {
				std::cout << "invalid number of parameters provided!" << std::endl;

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
				std::cout << "invalid number of parameters provided!" << std::endl;

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

	mParameters.push_back(ObjectiveScript::Parameter("argc", ObjectiveScript::Runtime::IntegerObject::TYPENAME, 1));
	mParameters.push_back(ObjectiveScript::Parameter("argv", ObjectiveScript::Runtime::StringObject::TYPENAME, mFilename));
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

void Client::shutdown()
{

}

void Client::start()
{
	mVirtualMachine.createScriptFromFile(mFilename, mParameters);
}



}
