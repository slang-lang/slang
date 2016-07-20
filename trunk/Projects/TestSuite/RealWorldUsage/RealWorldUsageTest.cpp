
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "RealWorldUsageTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Core/Utils/Exceptions.h>

// Namespace declartations
using namespace ObjectiveScript;


namespace Testing {
namespace RealWorldUsage {


RealWorldUsageTest::RealWorldUsageTest(const ::Utils::Common::ILogger *p)
: GenericTest("RealWorldUsageTest"),
  ::Utils::Common::Logger(p, "RealWorldUsageTest")
{
}

void RealWorldUsageTest::process()
{
	TEST(testAlternateMemberDeclaration);
}

void RealWorldUsageTest::setup()
{
}

void RealWorldUsageTest::teardown()
{
}

void RealWorldUsageTest::testAlternateMemberDeclaration()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/RealWorldUsage/AlternateMemberDeclaration.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
