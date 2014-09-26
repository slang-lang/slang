
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)

// Header
#include "PrototypeTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Utils/Printer.h>

// Namespace declartations
using namespace ObjectiveScript;


namespace Testing {
namespace Prototype {


Utils::Printer stdoutPrinter;


PrototypeTest::PrototypeTest(const Utils::Common::Logger *p)
: Utils::Common::Logger(p, "PrototypeTest")
{
}

void PrototypeTest::process()
{
	TEST(testPrototypeDeclaration);
	TEST(testPrototypeUsage);
}

void PrototypeTest::setup()
{
}

void PrototypeTest::teardown()
{
}

void PrototypeTest::testPrototypeDeclaration()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&stdoutPrinter);

		vm.create("Tests/PrototypeTest.os");

		// automatic succes
	}
	catch ( std::exception& ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception!");
	}
}

void PrototypeTest::testPrototypeUsage()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/PrototypeTest.os");

		VariablesList params;
		s->execute("test", params);

		// automatic succes
	}
	catch ( std::exception& ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception!");
	}
}


}
}
