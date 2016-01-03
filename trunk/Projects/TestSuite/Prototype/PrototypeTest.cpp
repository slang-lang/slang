
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

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Prototype {


PrototypeTest::PrototypeTest(const ::Utils::Common::ILogger *p)
: ::Utils::Common::Logger(p, "PrototypeTest")
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

		vm.create("Tests/Prototypes/PrototypeTest.os");

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

		vm.create("Tests/Prototypes/PrototypeTest_Inheritance.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
