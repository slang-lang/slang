
// Library includes

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Parameter.h>
#include <Core/Script.h>
#include <Core/Types.h>
#include <Core/VirtualMachine.h>
#include <Tools/Printer.h>
#include <Tools/Strings.h>

// Namespace declarations

#ifdef _WIN32
	// Memory leak check - Begin
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>

	#include <iostream>
	#include <crtdbg.h>
	#ifdef _DEBUG
	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
	#endif
	// Memory leak check - End

	//#include <vld.h>
#endif


std::string mFilename;
Utils::Common::StdOutLogger mLogger;
ObjectiveScript::ParameterList mParameters;
std::string mRoot;


void printUsage()
{
	std::cout << "Usage: oscript [options] [-f] <file> [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "-f | --file <file>    Parse and execute <file>" << std::endl;
	std::cout << "-h | --help           This help" << std::endl;
	std::cout << "-q                    Quiet mode, chats as less as possible" << std::endl;
	std::cout << "-r | --root           Library root path" << std::endl;
	std::cout << "-v                    Verbose output" << std::endl;
	std::cout << "--version             Version information" << std::endl;
	std::cout << std::endl;
}

void printVersion()
{
	std::cout << "ObjectiveScript Interpreter 0.0.1 (cli)" << std::endl;
	std::cout << "Copyright (c) 2015-2016 Michael Adelmann" << std::endl;
	std::cout << "" << std::endl;
}

void processParameters(int argc, const char* argv[])
{
	StringList params;
	std::string paramStr;

	if ( argc > 1 ) {
		for (int i = 1; i < argc; i++) {
			if ( Utils::Tools::StringCompare(argv[i], "-f") || Utils::Tools::StringCompare(argv[i], "--file") ) {
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;

					exit(-1);
				}

				mFilename = argv[i];
				params.push_back(mFilename);
				paramStr += mFilename;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-h") || Utils::Tools::StringCompare(argv[i], "--help") ) {
				printUsage();

				exit(0);
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-q") ) {
				mLogger.setLoudness(Utils::Common::ILogger::LoudnessMute);
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-r") || Utils::Tools::StringCompare(argv[i], "--root") ) {
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;

					exit(-1);
				}

				mRoot = argv[i];
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-v") ) {
				mLogger.setLoudness(Utils::Common::ILogger::LoudnessInfo);
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--version") ) {
				printVersion();

				exit(0);
			}
			else if ( mFilename.empty() ){
				mFilename = argv[i];
				params.push_back(mFilename);
				paramStr += mFilename;
			}
			else {
				params.push_back(argv[i]);
				paramStr += ", ";
				paramStr += argv[i];
			}
		}
	}

	mParameters.push_back(ObjectiveScript::Parameter("argc", ObjectiveScript::NumberObject::TYPENAME, Utils::Tools::toString(params.size())));
	mParameters.push_back(ObjectiveScript::Parameter("argv", ObjectiveScript::StringObject::TYPENAME, paramStr));
}

int main(int argc, const char* argv[])
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	processParameters(argc, argv);

	if ( mFilename.empty() ) {
		printUsage();

		return 0;
	}

	Utils::Printer& mPrinter = Utils::PrinterDriver::getInstance();
	mPrinter.ActivatePrinter = true;
	mPrinter.AutomaticLineBreak = true;
	mPrinter.PrintFileAndLine = true;

	ObjectiveScript::VirtualMachine mVirtualMachine;
	mVirtualMachine.setBaseFolder(mRoot);

	try {
		mVirtualMachine.create(mFilename, mParameters);
		// our script automatically executes it's Main object constructor,
		// so there is no need to execute a method explicitly
	}
	catch ( std::exception& e ) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
