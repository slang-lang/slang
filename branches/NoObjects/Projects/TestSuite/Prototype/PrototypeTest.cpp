
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "PrototypeTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Core/Utils/Exceptions.h>
#include <Utils/Printer.h>

// Namespace declartations
using namespace ObjectiveScript;


namespace Testing {
namespace Prototype {


PrototypeTest::PrototypeTest(const ::Utils::Common::Logger *p)
: ::Utils::Common::Logger(p, "PrototypeTest"),
  mStdoutPrinter(p)
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
		vm.setPrinter(&mStdoutPrinter);

		vm.create("Tests/Prototypes/PrototypeTest.os");

		// automatic success
	}
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void PrototypeTest::testPrototypeUsage()
{
	try {
		VirtualMachine vm;
		vm.setPrinter(&mStdoutPrinter);

		vm.create("Tests/Prototypes/PrototypeTest_Inheritance.os");

		// automatic success
	}
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}


}
}
