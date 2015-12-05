
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "MathTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Core/Utils/Exceptions.h>

// Namespace declartations
using namespace ObjectiveScript;


namespace Testing {
namespace Math {


MathTest::MathTest(const ::Utils::Common::Logger *p)
: ::Utils::Common::Logger(p, "Math"),
  mStdoutPrinter(p)
{
}

void MathTest::process()
{
	TEST(testBasicExpressionParsing);
}

void MathTest::setup()
{
}

void MathTest::teardown()
{
}

void MathTest::testBasicExpressionParsing()
{
	try {
		VirtualMachine vm;
		vm.setPrinter(&mStdoutPrinter);

		vm.create("Tests/Math/BasicTest.os");

		// automatic success
	}
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
