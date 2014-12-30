
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)

// Header
#include "AttributesTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Utils/Printer.h>

// Namespace declartations
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
		VirtualMachine vm;
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/AttributesTest.os");

		// automatic success
		delete s;
	}
	catch ( std::exception& ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception!");
	}
}


}
}
