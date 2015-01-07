
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "AttributesTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Core/Utils/Exceptions.h>
#include <Utils/Printer.h>

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Attributes {


::Utils::Printer stdoutPrinter;


AttributesTest::AttributesTest(const ::Utils::Common::Logger *p)
: ::Utils::Common::Logger(p, "AttributesTest")
{
}

AttributesTest::~AttributesTest()
{
}

void AttributesTest::process()
{
	TEST(testBasicLanguageFeatures);
}

void AttributesTest::setup()
{
}

void AttributesTest::teardown()
{
}

void AttributesTest::testBasicLanguageFeatures()
{
	try {
		//info("testBasicLanguageFeatures");

		VirtualMachine vm;
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/AttributesTest.os");

		// automatic success
		delete s;
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}


}
}
