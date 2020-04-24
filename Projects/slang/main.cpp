
// Library includes

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/Common/Exceptions.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/Script.h>
#include <Core/Version.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/VirtualMachine/VirtualMachine.h>
#include <Tools/Printer.h>
#include <Tools/Strings.h>
#include <Utils.h>

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
StringSet mLibraryFolders;
Utils::Common::StdOutLogger mLogger;
Slang::ParameterList mParameters;
bool mSanityCheck = true;
bool mSyntaxCheck = false;


void printUsage()
{
	std::cout << "Usage: slang [options] [-f] <file> [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "-f | --file <file>         Parse and execute <file>" << std::endl;
	std::cout << "-h | --help                This help" << std::endl;
	std::cout << "-l | --library <library>   Library root path" << std::endl;
	std::cout << "-q | --quiet               Quiet mode, chats as less as possible" << std::endl;
	std::cout << "--skip-sanitycheck         Skips sanity check before parsing" << std::endl;
	std::cout << "--syntax <file>            Syntax check only" << std::endl;
	std::cout << "-v | --verbose             Verbose output" << std::endl;
	std::cout << "--version                  Version information" << std::endl;
	std::cout << std::endl;
}

void printVersion()
{
	std::cout << PRODUCT_NAME << " Interpreter " << PRODUCT_VERSION << " (cli)" << std::endl;
	std::cout << COPYRIGHT << std::endl;
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

				mLibraryFolders.insert(argv[i]);
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-q") || Utils::Tools::StringCompare(argv[i], "--quiet") ) {
				mLogger.setLoudness(Utils::Common::ILogger::LoudnessMute);

				Utils::PrinterDriver::Instance()->ActivatePrinter = false;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--skip-sanitycheck") ) {
				mSanityCheck = false;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--syntax") ) {
				mSyntaxCheck = true;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-v") || Utils::Tools::StringCompare(argv[i], "--verbose") ) {
				mLogger.setLoudness(Utils::Common::ILogger::LoudnessInfo);

				Utils::PrinterDriver::Instance()->ActivatePrinter = true;
				Utils::PrinterDriver::Instance()->PrintFileAndLine = true;
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
			paramStr += "\n";
			paramStr += argv[i];
		}
	}

	mParameters.push_back(Slang::Parameter::CreateRuntime(Slang::Runtime::IntegerObject::TYPENAME, (int)params.size()));
	mParameters.push_back(Slang::Parameter::CreateRuntime(Slang::Runtime::StringObject::TYPENAME, paramStr));
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

	Slang::VirtualMachine mVirtualMachine;
	for ( StringSet::const_iterator it = mLibraryFolders.cbegin(); it != mLibraryFolders.cend(); ++it ) {
		mVirtualMachine.addLibraryFolder((*it));
	}

	mVirtualMachine.settings().DoCollectErrors = true;
	mVirtualMachine.settings().DoSanityCheck = mSanityCheck;
	mVirtualMachine.settings().DoSyntaxCheck = mSyntaxCheck;

	// add extensions
#ifdef USE_JSON_EXTENSION
	mVirtualMachine.addExtension(new Slang::Extensions::Json::JsonExtension());
#endif
#ifdef USE_SYSTEM_EXTENSION
	mVirtualMachine.addExtension(new Slang::Extensions::System::SystemExtension());
#endif

	try {
		Slang::Runtime::Object result;

		Slang::Script* script = mVirtualMachine.createScriptFromFile(mFilename);
		assert(script);

		if ( mSyntaxCheck ) {
			std::cout << "Syntax check done, no errors found." << std::endl;
		}
		else {
			mVirtualMachine.run(script, mParameters, &result);

			if (result.getValue().type() == Slang::Runtime::AtomicValue::Type::INT ) {
				return result.getValue().toInt();
			}
		}

		return 0;
	}
	catch (Slang::Runtime::ControlFlow::E &e ) {
		if (e == Slang::Runtime::ControlFlow::ExitProgram ) {
			return 0;
		}

		OSerror("abnormal program termination!");
	}
	catch ( std::exception &e ) {	// catch every std::exception and all derived exception types
		OSerror(e.what());
	}
	catch ( ... ) {	// catch everything
		std::cout << "uncaught exception detected!" << std::endl;
	}

	return -1;
}
