
// Header
#include "Application.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/Utils/Utils.h>
#include <Debugger/Debugger.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Core/Runtime/ControlFlow.h>

// Namespace declarations


namespace ObjectiveScript {


Application::Application()
{
}

Application::~Application()
{
}

void Application::init(int argc, const char* argv[])
{
	processParameters(argc, argv);

	mBackend.connectSettings(&mSettings);
	mBackend.connectTerminal(&mLocalClient);

	Core::Debugger::GetInstance().registerReceiver(&mBackend);
}

int Application::exec()
{
	// only start if we have a filename set
	if ( mSettings.filename().empty() ) {
		printUsage();
		return 0;
	}

	// initial checks
	if ( !::Utils::Tools::Files::exists(mSettings.filename()) ) {
		OSerror("File '" + mSettings.filename() + "' does not exist!");
		return -1;
	}

	// start program execution
	int result = 0;
	try {
		result = mBackend.exec();
	}
	catch ( Runtime::ControlFlow::E /*e*/ ) {
		//
	}

	return result;
}

void Application::printUsage()
{
	std::cout << "Usage: odebugger [options] [-f] <file> [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "-f | --file <file>         Parse and execute <file>" << std::endl;
	std::cout << "-h | --help                This help" << std::endl;
	std::cout << "-l | --library <library>   Library root path" << std::endl;
	std::cout << "--version                  Version information" << std::endl;
	std::cout << std::endl;
}

void Application::printVersion()
{
	std::cout << "ObjectiveScript Debugger 0.4.1 (cli)" << std::endl;
	std::cout << "Copyright (c) 2014-2016 Michael Adelmann" << std::endl;
	std::cout << "" << std::endl;
}

void Application::processParameters(int argc, const char* argv[])
{
	for ( int i = 1; i < argc; i++ ) {
		if ( ::Utils::Tools::StringCompare(argv[i], "-f") || ::Utils::Tools::StringCompare(argv[i], "--file") ) {
			if ( argc <= ++i ) {
				OSerror("invalid number of parameters provided!");

				exit(-1);
			}

			mSettings.filename(argv[i]);
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

			mSettings.root(argv[i]);
		}
		else if ( ::Utils::Tools::StringCompare(argv[i], "--version") ) {
			printVersion();

			exit(0);
		}
		else if ( mSettings.filename().empty() ){
			mSettings.filename(argv[i]);
		}
	}
}


}
