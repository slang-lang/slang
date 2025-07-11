
// Library includes
#include <list>

// Project includes
#include <Core/Defines.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/VirtualMachine/Controller.h>
#include <Logger/StdOutLogger.h>
#include <Tools/Printer.h>
#include <Tools/Strings.h>
#include <Utils.h>

// Fixtures
#include <AST/Fixture.h>
#include <Extensions/Fixture.h>
#include <Inheritance/Fixture.h>
#include <Interfaces/Fixture.h>
#include <Language/Fixture.h>
#include <Library/Fixture.h>
#include <Math/Fixture.h>
#include <Operator/Fixture.h>
#include <Prototype/Fixture.h>
#include <Utils/Fixture.h>

// Namespace declarations


#ifdef _WIN32
	// Memory leak check - Begin
	#define _CRTDBG_MAP_ALLOC
	#include <cstdlib>

	#include <iostream>
	#include <crtdbg.h>
	#ifdef _DEBUG
	#define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
	#define new DEBUG_NEW
	#endif
	// Memory leak check - End

	//#include <vld.h>
#endif


typedef std::list<MyUnit::TestFixture*> FixtureList;

namespace {

	StringSet mLibraryFolders;
	Utils::Common::ILogger* mLogger{ nullptr };
	Utils::Printer* mPrinter{ nullptr };

}


void cleanup()
{
	if ( mLogger ) {
		delete mLogger;
		mLogger = nullptr;
	}
}

void initialize()
{
	mLogger = new Utils::Common::StdOutLogger();
	mPrinter = Utils::Printer::Instance();
}

void printUsage()
{
	std::cout << "Usage: TestSuite [options] [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "-h | --help           This help" << std::endl;
    std::cout << "-l | --library <library>   Library root path" << std::endl;
	std::cout << "-q | --quiet          Quiet mode, chats as less as possible" << std::endl;
	std::cout << "--show                Print test suites information" << std::endl;
	std::cout << "--showtests           Print unit tests of given test suite" << std::endl;
	std::cout << "--test                Execute given test suite" << std::endl;
	std::cout << "-v | --verbose        Verbose output" << std::endl;
	std::cout << std::endl;
}

int main( int argc, const char* argv[] )
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	initialize();

	bool show = false;
	std::string toRun;

	if ( argc > 1 ) {
		for ( int i = 1; i < argc; i++ ) {
			if ( Utils::Tools::StringCompare( argv[i], "-h" ) || Utils::Tools::StringCompare( argv[i], "--help" ) ) {
				printUsage();
				cleanup();

				return 0;
			}
			else if ( Utils::Tools::StringCompare( argv[i], "-l" ) || Utils::Tools::StringCompare( argv[i], "--library" ) ) {
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;

					exit( -1 );
				}

				mLibraryFolders.insert( argv[i] );
			}
			else if ( Utils::Tools::StringCompare( argv[i], "-q" ) || Utils::Tools::StringCompare( argv[i], "--quiet" ) ) {
				mLogger->setLoudness( Utils::Common::ILogger::LoudnessMute );

				mPrinter->ActivatePrinter = false;
			}
			else if ( Utils::Tools::StringCompare( argv[i], "--show" ) ) {
				show = true;
			}
			else if ( Utils::Tools::StringCompare( argv[i], "--showtests" ) ) {
				show = true;
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;
					cleanup();
					return -1;
				}
				toRun = argv[i];
			}
			else if ( Utils::Tools::StringCompare( argv[i], "--test" ) ) {
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;
					return -1;
				}
				toRun = argv[i];
			}
			else if ( Utils::Tools::StringCompare( argv[i], "-v" ) || Utils::Tools::StringCompare( argv[i], "--verbose" ) ) {
				mLogger->setLoudness( Utils::Common::ILogger::LoudnessDebug );

				mPrinter->ActivatePrinter = true;
				mPrinter->AutomaticLineBreak = true;
				mPrinter->PrintFileAndLine = true;
			}
			else {
				toRun = argv[i];
			}
		}
	}

	try {
		FixtureList mFixtures;

		Testing::AST::Fixture ast( mLogger, mLibraryFolders );
		mFixtures.push_back( &ast );

		Testing::Extensions::Fixture extensions( mLogger, mLibraryFolders );
		mFixtures.push_back( &extensions );

		Testing::Inheritance::Fixture inheritance( mLogger, mLibraryFolders );
		mFixtures.push_back( &inheritance );

		Testing::Interfaces::Fixture interfaces( mLogger, mLibraryFolders );
		mFixtures.push_back( &interfaces );

		Testing::Language::Fixture language( mLogger, mLibraryFolders );
		mFixtures.push_back( &language );

		Testing::Library::Fixture library( mLogger, mLibraryFolders );
		mFixtures.push_back( &library );

		Testing::Math::Fixture math( mLogger, mLibraryFolders );
		mFixtures.push_back( &math );

		Testing::Operator::Fixture operator_overloading( mLogger, mLibraryFolders );
		mFixtures.push_back( &operator_overloading );

		Testing::Prototype::Fixture prototype( mLogger, mLibraryFolders );
		mFixtures.push_back( &prototype );

		Testing::UtilsTest::Fixture utils( mLogger, mLibraryFolders );
		mFixtures.push_back( &utils );

		MyUnit::TestResult result;

		bool executed = false;

		for ( auto& mFixture : mFixtures ) {
			if ( show ) {
				if ( toRun.empty() ) {
					std::cout << mFixture->getName() << std::endl;
					continue;
				}
				else if ( toRun == mFixture->getName() ) {
					mFixture->print();
				}
			}
			else if ( toRun.empty() || toRun == mFixture->getName() ) {
				executed = true;
				result = result + mFixture->run();
			}
		}

		std::cout << std::endl;
		std::cout << "Statistics: "
				  << ( result.Run - result.Failed - result.Skipped ) << " passed, "
				  << result.Skipped << " skipped, "
				  << result.Failed << " failed "
				  << std::endl;

		mFixtures.clear();

		cleanup();

		if ( !executed && !show ) {
			std::cout << "could not find fixture '" << toRun << "'!" << std::endl;
		}

		return 0;
	}
	catch ( Runtime::ControlFlow::E &e ) {
		if ( e != Runtime::ControlFlow::ExitProgram ) {
			OSerror( "abnormal program termination!" );
		}
	}
	catch ( std::exception& e ) {
		OSerror( e.what() );
	}
	catch ( ... ) {	// catch everything
		std::cout << "uncaught exception detected" << std::endl;
	}

	// if we get here something bad has happened
	Controller::Instance().threads()->print();

	return -1;
}
