
// Library includes

// Project includes
#include <Core/AST/PrintVisitor.h>
#include <Core/AST/TreeGenerator.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/Analyser.h>
#include <Core/Runtime/Script.h>
#include <Core/Version.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/VirtualMachine/VirtualMachine.h>
#include <Logger/StackTrace.h>
#include <Logger/StdOutLogger.h>
#include <Tools/Files.h>
#include <Tools/Printer.h>
#include <Tools/Strings.h>
#include <Utils.h>

// Extension includes
#include <Extensions.h>

// Namespace declarations
using namespace Slang;


namespace {

	std::string mFilename;
	StringSet mLibraryFolders;
	Utils::Common::StdOutLogger mLogger;
	ParameterList mParameters;
	bool mPrintUsage = false;
	bool mPrintVersion = false;

}


void printUsage()
{
	std::cout << "Usage: slang-format [options] [-f] <file> [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "-f | --file <file>         Format given file <file>" << std::endl;
	std::cout << "-l | --library <library>   Library root path" << std::endl;
	std::cout << "-n | --dry-run             If set, do not actually make the formatting changes" << std::endl;
	std::cout << "--dump-config              Dump configuration options to stdout and exit." << std::endl;
	std::cout << "-v | --verbose             Verbose output" << std::endl;
	std::cout << std::endl;
	std::cout << "Generic Options:" << std::endl;
	std::cout << std::endl;
	std::cout << "-h | --help                This help" << std::endl;
	std::cout << "--version                  Version information" << std::endl;
	std::cout << std::endl;
}

void printVersion()
{
	std::cout << PRODUCT_NAME << " Format " << PRODUCT_VERSION << " (cli)" << std::endl;
	std::cout << COPYRIGHT << std::endl;
	std::cout << std::endl;
}

void processParameters( int argc, const char* argv[] )
{
	StringList params;
	std::string paramStr;

	bool scriptParams = false;

	for ( int i = 1; i < argc; i++ ) {
		if ( !scriptParams ) {
			if ( Utils::Tools::StringCompare( argv[i], "-f" ) || Utils::Tools::StringCompare( argv[i], "--file" ) ) {
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;

					exit( -1 );
				}

				mFilename = argv[i];
				params.push_back( mFilename );
				paramStr += mFilename;

				// all parameters that follow are designated for our script
				scriptParams = true;
			}
			else if ( Utils::Tools::StringCompare( argv[i], "-h" ) || Utils::Tools::StringCompare( argv[i], "--help" ) ) {
				mPrintUsage = true;
			}
			else if ( Utils::Tools::StringCompare( argv[i], "-l" ) || Utils::Tools::StringCompare( argv[i], "--library" ) ) {
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;

					exit( -1 );
				}

				mLibraryFolders.insert( argv[i] );
			}
			else if ( Utils::Tools::StringCompare( argv[i], "-v" ) || Utils::Tools::StringCompare( argv[i], "--verbose" ) ) {
				mLogger.setLoudness( Utils::Common::ILogger::LoudnessInfo );

				Utils::Printer::Instance()->ActivatePrinter = true;
				Utils::Printer::Instance()->PrintFileAndLine = true;
			}
			else if ( Utils::Tools::StringCompare( argv[i], "--version" ) ) {
				mPrintVersion = true;
			}
			else if ( mFilename.empty() ){
				mFilename = argv[i];
				params.push_back( mFilename );
				paramStr += mFilename;

				// all parameters that follow are designated for our script
				scriptParams = true;
			}
		}
		else {
			params.emplace_back( argv[i] );
			paramStr += "\n";
			paramStr += argv[i];
		}
	}
}

std::string getFileContent( const std::string& filename )
{
    if ( filename.empty() ) {
		OSerror("invalid filename '" + filename + "' provided!");
		throw Common::Exceptions::Exception("invalid filename '" + filename + "' provided!");
	}
	if ( !Utils::Tools::Files::exists(filename) ) {
		OSerror("file '" + filename + "' not found!");
		throw Common::Exceptions::Exception("file '" + filename + "' not found!");
	}

	// open file
	std::ifstream in(filename.c_str(), std::ios_base::binary);

	// read file content
	auto content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());

	mLibraryFolders.insert( Utils::Tools::Files::ExtractPathname(Utils::Tools::Files::GetFullname(filename)) );

	return content;
}

int main( int argc, const char* argv[] )
{
	processParameters( argc, argv );

	VirtualMachine mVirtualMachine;

	// add extensions
#ifdef USE_SYSTEM_EXTENSION
	mVirtualMachine.addExtension( new Extensions::System::SystemExtension() );
	mVirtualMachine.addExtension( new Extensions::LIBC::Extension() );
#endif

	mVirtualMachine.init();

	for ( const auto& library : mLibraryFolders ) {
		mVirtualMachine.addLibraryFolder( library );
	}

	if ( mPrintVersion ) {
		printVersion();

		return 0;
	}
	else if ( mPrintUsage || mFilename.empty() ) {
		printUsage();

		return 0;
	}

	try {
	    /*
		Designtime::Analyser analyser( true, false );
		analyser.processString( getFileContent( mFilename ), mFilename );

		AST::TreeGenerator generator( Controller::Instance().repository(), true );
		generator.process( Controller::Instance().globalScope() );
		*/

		mVirtualMachine.createScriptFromFile( mFilename );

		AST::TreeLineBuffer output;
		AST::PrintVisitor printer;

		printer.generate( Controller::Instance().globalScope(), output );

		AST::TreeLineBuffer::Lines lines;
		output.getLines( lines );

		for ( auto it = lines.begin(); it != lines.end(); ++it ) {
			std::cout << it->first.toString() << ": " << it->second << std::endl;
		}

		return 0;
	}
	catch ( std::exception &e ) {	// catch every std::exception and all derived exception types
		OSerror( e.what() );
	}
	catch ( ... ) {	// catch everything
		std::cout << "uncaught exception detected!" << std::endl;
	}

	return -1;
}
