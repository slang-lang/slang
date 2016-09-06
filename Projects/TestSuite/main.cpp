
// Library includes
#include <list>
#include <map>

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/StackTrace.h>
#include <Tools/Printer.h>
#include <Tools/Strings.h>
#include <Tools/Tools.h>
#include <Utils.h>

// Fixtures
#include <Attributes/Fixture.h>
#include <Inheritance/Fixture.h>
#include <Interfaces/Fixture.h>
#include <Language/Fixture.h>
#include <Library/Fixture.h>
#include <Math/Fixture.h>
#include <Operator/Fixture.h>
#include <Prototype/Fixture.h>
#include <TestFramework/Fixture.h>

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


typedef std::list<TestFixture*> FixtureList;


void printUsage()
{
	std::cout << "Usage: TestSuite [options] [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "-h | --help           This help" << std::endl;
	std::cout << "-q | --quiet          Quiet mode, chats as less as possible" << std::endl;
	std::cout << "--show                Print test suites information" << std::endl;
	std::cout << "--showtests           Print unit tests of given test suite" << std::endl;
	std::cout << "--test                Execute given test suite" << std::endl;
	std::cout << "-v | --verbose        Verbose output" << std::endl;
	std::cout << std::endl;
}

int main(int argc, const char* argv[])
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	Utils::Common::ILogger *mLogger = new Utils::Common::StdOutLogger();
	Utils::Printer *mPrinter = Utils::PrinterDriver::getInstance();

	bool executed = false;
	bool show = false;
	std::string toRun = "";

	if ( argc > 1 ) {
		for (int i = 1; i < argc; i++) {
			if ( Utils::Tools::StringCompare(argv[i], "--help") ) {
				printUsage();

				return 0;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-q") || Utils::Tools::StringCompare(argv[i], "--quiet") ) {
				mLogger->setLoudness(Utils::Common::ILogger::LoudnessMute);

				mPrinter->ActivatePrinter = false;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--show") ) {
				show = true;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--showtests") ) {
				show = true;
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;
					return -1;
				}
				toRun = argv[i];
			}
			else if ( Utils::Tools::StringCompare(argv[i], "--test") ) {
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;
					return -1;
				}
				toRun = argv[i];
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-v") || Utils::Tools::StringCompare(argv[i], "--verbose") ) {
				mLogger->setLoudness(Utils::Common::ILogger::LoudnessDebug);

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
/*
		Testing::Framework::Fixture testing(logger);
		mFixtures.push_back(&testing);
*/
		Testing::Attributes::Fixture attributes(mLogger);
		mFixtures.push_back(&attributes);

		Testing::Inheritance::Fixture inheritance(mLogger);
		mFixtures.push_back(&inheritance);

		Testing::Interfaces::Fixture interfaces(mLogger);
		mFixtures.push_back(&interfaces);

		Testing::Language::Fixture language(mLogger);
		mFixtures.push_back(&language);

		Testing::Library::Fixture library(mLogger);
		mFixtures.push_back(&library);

		Testing::Math::Fixture math(mLogger);
		mFixtures.push_back(&math);

		Testing::Operator::Fixture operator_overloading(mLogger);
		mFixtures.push_back(&operator_overloading);
/*
		Testing::Prototype::Fixture prototype(logger);
		mFixtures.push_back(&prototype);
*/
		for ( FixtureList::iterator it = mFixtures.begin(); it != mFixtures.end(); ++it ) {
			if ( show ) {
				if ( toRun.empty() ) {
					std::cout << (*it)->getName() << std::endl;
					continue;
				}
				else if ( toRun == (*it)->getName() ) {
					(*it)->print();
				}
			}
			else if ( toRun.empty() || toRun == (*it)->getName() ) {
				executed = true;
				(*it)->run();
			}
		}

		mFixtures.clear();
	}
	catch ( std::exception& e ) {	// catch every std::exception and all derived exception types
		OSerror(e.what());

		ObjectiveScript::StackTrace::GetInstance().print();
	}
	catch ( ... ) {	// catch everything
		std::cout << "uncaught exception detected" << std::endl;
	}

	if ( !executed && !show ) {
		std::cout << "could not find fixture '" << toRun << "'!" << std::endl;
	}

	SafeDelete( mLogger );

	return 0;
}
