
// Library includes

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
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
	#include <cstdlib>

	#include <iostream>
	#include <crtdbg.h>
	#ifdef _DEBUG
	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
	#endif
	// Memory leak check - End

	//#include <vld.h>
#else
#	include <cstdlib>
#endif


std::string mFilename;
StringSet mLibraryFolders;
Utils::Common::StdOutLogger mLogger;
Slang::ParameterList mParameters;
bool mPrintDebugInfo = false;
bool mPrintSpecification = false;
bool mPrintTokens = false;
bool mPrintUsage = false;
bool mPrintVersion = false;
std::string mRequestedSpecification;
bool mSanityCheck = true;
bool mSyntaxCheck = false;


void printUsage()
{
	std::cout << "Usage: slang [options] [-f] <file> [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "--debug                    Show debug information" << std::endl;
	std::cout << "-f | --file <file>         Parse and execute <file>" << std::endl;
	std::cout << "-h | --help                This help" << std::endl;
	std::cout << "-l | --library <library>   Library root path" << std::endl;
	std::cout << "-q | --quiet               Quiet mode, chats as less as possible" << std::endl;
	std::cout << "--skip-sanitycheck         Skips sanity check before parsing" << std::endl;
	std::cout << "--spec [query]             Print specification, can be followed by an optional query" << std::endl;
	std::cout << "--syntax <file>            Syntax check only" << std::endl;
	std::cout << "--tokens                   Print out list of all tokens and halt execution" << std::endl;
	std::cout << "-v | --verbose             Verbose output" << std::endl;
	std::cout << "--version                  Version information" << std::endl;
	std::cout << std::endl;
}

void printVersion()
{
	std::cout << PRODUCT_NAME << " Interpreter " << PRODUCT_VERSION << " (cli)" << std::endl;
	std::cout << COPYRIGHT << std::endl;
	std::cout << std::endl;
}

void processParameters(int argc, const char* argv[])
{
	StringList params;
	std::string paramStr;

	bool scriptParams = false;

	for ( int i = 1; i < argc; i++ ) {
		if ( !scriptParams ) {
			if ( Utils::Tools::StringCompare(argv[i], "--debug") ) {
				mPrintDebugInfo = true;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-f") || Utils::Tools::StringCompare(argv[i], "--file") ) {
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
				mPrintUsage = true;
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

				Utils::Printer::Instance()->ActivatePrinter = false;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--skip-sanitycheck") ) {
				mSanityCheck = false;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--spec") ) {
				mPrintSpecification = true;

				if ( argc > ++i ) {
					mRequestedSpecification = argv[i];
				}
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--syntax") ) {
				mSyntaxCheck = true;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--tokens") ) {
				mPrintTokens = true;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-v") || Utils::Tools::StringCompare(argv[i], "--verbose") ) {
				mLogger.setLoudness(Utils::Common::ILogger::LoudnessInfo);

				Utils::Printer::Instance()->ActivatePrinter = true;
				Utils::Printer::Instance()->PrintFileAndLine = true;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--version") ) {
				mPrintVersion = true;
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

	mParameters.push_back(Slang::Parameter::CreateRuntime(Slang::Runtime::Int32Type::TYPENAME, static_cast<int32_t>(params.size())));
	mParameters.push_back(Slang::Parameter::CreateRuntime(Slang::Runtime::StringType::TYPENAME, paramStr));
}

int main(int argc, const char* argv[])
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	processParameters(argc, argv);

	Slang::VirtualMachine mVirtualMachine;

	// add extensions
#ifdef USE_SYSTEM_EXTENSION
	mVirtualMachine.addExtension(new Slang::Extensions::System::SystemExtension());
	mVirtualMachine.addExtension(new Slang::Extensions::LIBC::Extension());
#endif

	mVirtualMachine.settings().DoCollectErrors = true;
	mVirtualMachine.settings().DoSanityCheck = mSanityCheck;
	mVirtualMachine.settings().DoSyntaxCheck = mSyntaxCheck;
	mVirtualMachine.settings().PrintTokens   = mPrintTokens;

	mVirtualMachine.init();

	for ( const auto& library : mLibraryFolders ) {
		mVirtualMachine.addLibraryFolder( library );
	}

	if ( mPrintDebugInfo ) {
		mVirtualMachine.printLibraryFolders();
		mVirtualMachine.printExtensions();

		return 0;
	}
	else if ( mPrintSpecification ) {
		mVirtualMachine.printSpecification( mRequestedSpecification );

		return 0;
	}
	else if ( mPrintVersion ) {
		printVersion();

		return 0;
	}
	else if ( mPrintUsage || mFilename.empty() ) {
		printUsage();

		return 0;
	}

	try {
		auto* script = mVirtualMachine.createScriptFromFile(mFilename);
		assert(script);

		if ( mPrintTokens ) {
			// we are done after printing our tokens
		}
		else if ( mSyntaxCheck ) {
			std::cout << "Syntax check done, no errors found." << std::endl;
		}
		else {
			Slang::Runtime::Object result;
			mVirtualMachine.run(script, mParameters, &result);

			if ( result.getValue().type() == Slang::Runtime::AtomicValue::Type::INT ) {
				return result.getValue().toInt();
			}
		}

		return 0;
	}
	catch ( Slang::Runtime::ControlFlow::E &e ) {
		if ( e == Slang::Runtime::ControlFlow::ExitProgram ) {
			return 0;
		}
		else if ( e == Slang::Runtime::ControlFlow::Throw ) {
			OSerror( "Exception thrown in " << Slang::Controller::Instance().thread( 0 )->exception().getPosition().toString() << std::endl
			         << Slang::Controller::Instance().thread( 0 )->exception().getData()->ToString() );
		}
		else {
			OSerror( "abnormal program termination!" );
		}
	}
	catch ( std::exception &e ) {	// catch every std::exception and all derived exception types
		OSerror(e.what());
	}
	catch ( ... ) {	// catch everything
		std::cout << "uncaught exception detected!" << std::endl;
	}

	return -1;
}
