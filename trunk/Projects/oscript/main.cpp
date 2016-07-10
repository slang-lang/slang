
// Library includes

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Script.h>
#include <Core/StackTrace.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Core/VirtualMachine.h>
#include <Tools/Printer.h>
#include <Tools/Strings.h>

// Extension includes
#include <Extensions.h>

// Namespace declarations

#ifdef __APPLE__
#elif defined _WIN32
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
#else
#	include <stdlib.h>
#endif


std::string mFilename;
Utils::Common::StdOutLogger mLogger;
ObjectiveScript::ParameterList mParameters;
std::string mRoot;


void printUsage()
{
	std::cout << "Usage: oscript [options] [-f] <file> [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "-f | --file <file>         Parse and execute <file>" << std::endl;
	std::cout << "-h | --help                This help" << std::endl;
	std::cout << "-l | --library <library>   Library root path" << std::endl;
	std::cout << "-q | --quiet               Quiet mode, chats as less as possible" << std::endl;
	std::cout << "-v | --verbose             Verbose output" << std::endl;
	std::cout << "--version                  Version information" << std::endl;
	std::cout << std::endl;
}

void printVersion()
{
	std::cout << "ObjectiveScript Interpreter 0.3.7 (cli)" << std::endl;
	std::cout << "Copyright (c) 2014-2016 Michael Adelmann" << std::endl;
	std::cout << "" << std::endl;
}

void processParameters(int argc, const char* argv[])
{
	StringList params;
	std::string paramStr;

	bool scriptParams = false;

	for ( int i = 1; i < argc; i++ ) {
		if ( !scriptParams ) {
			if ( Utils::Tools::StringCompare(argv[i], "-f") || Utils::Tools::StringCompare(argv[i], "--file") ) {
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;

					exit(-1);
				}

				mFilename = argv[i];
				params.push_back(mFilename);
				paramStr += mFilename;

				// all parameters that follow are designated for our script
				scriptParams = true;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-h") || Utils::Tools::StringCompare(argv[i], "--help") ) {
				printUsage();

				exit(0);
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-l") || Utils::Tools::StringCompare(argv[i], "--library") ) {
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;

					exit(-1);
				}

				mRoot = argv[i];
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-q") || Utils::Tools::StringCompare(argv[i], "--quiet") ) {
				mLogger.setLoudness(Utils::Common::ILogger::LoudnessMute);

				Utils::PrinterDriver::getInstance()->ActivatePrinter = false;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-v") || Utils::Tools::StringCompare(argv[i], "--verbose") ) {
				mLogger.setLoudness(Utils::Common::ILogger::LoudnessInfo);

				Utils::PrinterDriver::getInstance()->ActivatePrinter = true;
				Utils::PrinterDriver::getInstance()->PrintFileAndLine = true;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--version") ) {
				printVersion();

				exit(0);
			}
			else if ( mFilename.empty() ){
				mFilename = argv[i];
				params.push_back(mFilename);
				paramStr += mFilename;

				// all parameters that follow are designated for our script
				scriptParams = true;
			}
		}
		else {
			params.push_back(argv[i]);
			paramStr += ", ";
			paramStr += argv[i];
		}
	}

	mParameters.push_back(ObjectiveScript::Parameter("argc", ObjectiveScript::Runtime::IntegerObject::TYPENAME, (int)params.size()));
	mParameters.push_back(ObjectiveScript::Parameter("argv", ObjectiveScript::Runtime::StringObject::TYPENAME, paramStr.c_str()));
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

	ObjectiveScript::VirtualMachine mVirtualMachine;
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

	try {
		ObjectiveScript::Script *script = mVirtualMachine.createScriptFromFile(mFilename, mParameters);
		assert(script);

		// check if an instance ("main") of a Main object exists
		ObjectiveScript::Runtime::Object *main = static_cast<ObjectiveScript::Runtime::Object*>(script->resolve("main"));

		if ( !main || main->isAtomicType() ) {
			ObjectiveScript::Runtime::IntegerObject result;
			script->execute("Main", mParameters, &result);
			return result.getValue().toInt();
		}
	}
	catch ( std::exception& e ) {	// catch every std::exception and all derived exception types
		OSerror(e.what());

		ObjectiveScript::StackTrace::GetInstance().print();
	}
	catch ( ObjectiveScript::Runtime::ControlFlow::E e ) {
		if ( e != ObjectiveScript::Runtime::ControlFlow::ExitProgram ) {
			OSerror("abnormal program termination!");

			ObjectiveScript::StackTrace::GetInstance().print();
		}
	}
	catch ( ... ) {	// catch everything
		std::cout << "uncaught exception detected" << std::endl;
	}

	return 0;
}
