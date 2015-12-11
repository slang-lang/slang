
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "OperatorTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Core/Utils/Exceptions.h>

// Namespace declartations
using namespace ObjectiveScript;


namespace Testing {
namespace Operator {


OperatorTest::OperatorTest(const ::Utils::Common::Logger *p)
: ::Utils::Common::Logger(p, "Operator"),
  mStdoutPrinter(p)
{
}

void OperatorTest::process()
{
	TEST(testMathOverloadsWithNumbers);
	TEST(testMathOverloadsWithObjects);
}

void OperatorTest::setup()
{
}

void OperatorTest::teardown()
{
}

void OperatorTest::testMathOverloadsWithNumbers()
{
	try {
		VirtualMachine vm;
		vm.setPrinter(&mStdoutPrinter);

		vm.create("Tests/Operator/MathOverloadsWithNumbers.os");

		// automatic success
	}
	catch ( ObjectiveScript::Utils::AssertionFailed& /*e*/ ) {
		// success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testMathOverloadsWithObjects()
{
	try {
		VirtualMachine vm;
		vm.setPrinter(&mStdoutPrinter);

		vm.create("Tests/Operator/MathOverloadsWithObjects.os");

		// automatic success
	}
	catch ( ObjectiveScript::Utils::AssertionFailed& /*e*/ ) {
		// success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
