
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "PrototypeTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Prototype {


PrototypeTest::PrototypeTest(const ::Utils::Common::ILogger *p)
: GenericTest("PrototypeTest"),
  ::Utils::Common::Logger(p, "PrototypeTest")
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

		vm.createScriptFromFile("Tests/Prototypes/PrototypeTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testPrototypeUsage()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Prototypes/PrototypeTest_Inheritance.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
