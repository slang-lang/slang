
// Header
#include "Application.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/Runtime/ControlFlow.h>
#include <Core/Version.h>
#include <Debugger/Debugger.h>
#include <LocalClient/LocalClient.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Utils.h>
#include <VSCodeRemoteClient/RemoteClient.h>

// Namespace declarations


namespace ObjectiveScript {


Application::Application()
: mClient(0)
{
}

Application::~Application()
{
	if ( mClient ) {
		delete mClient;
		mClient = 0;
	}
}

void Application::init(int argc, const char* argv[])
{
	processParameters(argc, argv);

	if ( mSettings.remoteClient() ) {
		RemoteClient* client = new RemoteClient();

		Core::Debugger::Instance().registerReceiver(client);

		mClient = client;
	}
	else {
		LocalClient* client = new LocalClient();

		Core::Debugger::Instance().registerReceiver(client);

		mClient = client;
	}

	mClient->connectSettings(&mSettings);
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
	int result = -1;
	try {
		result = mClient->exec();
	}
	catch ( ObjectiveScript::Runtime::ControlFlow::E &e ) {
		if ( e != ObjectiveScript::Runtime::ControlFlow::ExitProgram ) {
			OSerror("abnormal program termination!");
		}
	}
	catch ( std::exception &e ) {	// catch every std::exception and all derived exception types
		OSerror(e.what());
	}
	catch ( ... ) {	// catch everything
		std::cout << "uncaught exception detected!" << std::endl;
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
	std::cout << "-r | --run                 Auto start debugging" << std::endl;
	std::cout << "--remote                   Enable remote client" << std::endl;
	std::cout << "--runandquit               Auto start debugging and quit debugger after successful execution" << std::endl;
	std::cout << "--version                  Version information" << std::endl;
	std::cout << std::endl;
}

void Application::printVersion()
{
	std::cout << PRODUCT_NAME << " Debugger " << PRODUCT_VERSION << " (cli)" << std::endl;
	std::cout << COPYRIGHT << std::endl;
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

			mSettings.addLibraryFolder(argv[i]);
		}
		else if ( ::Utils::Tools::StringCompare(argv[i], "--remote") ) {
			mSettings.remoteClient(true);
		}
		else if ( ::Utils::Tools::StringCompare(argv[i], "--version") ) {
			printVersion();

			exit(0);
		}
		else if ( ::Utils::Tools::StringCompare(argv[i], "-r") || ::Utils::Tools::StringCompare(argv[i], "--run") ) {
			mSettings.autoStart(true);
		}
		else if ( ::Utils::Tools::StringCompare(argv[i], "--runandquit") ) {
			mSettings.autoStart(true);
			mSettings.autoStop(true);
		}
		else if ( mSettings.filename().empty() ){
			mSettings.filename(argv[i]);
		}
	}
}


}
