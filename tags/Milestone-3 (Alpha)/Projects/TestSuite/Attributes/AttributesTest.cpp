
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "AttributesTest.h"

// Library includes

// Project includes
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Attributes {


AttributesTest::AttributesTest(const ::Utils::Common::ILogger *p)
: GenericTest("AttributesTest"),
  ::Utils::Common::Logger(p, "AttributesTest")
{
}

AttributesTest::~AttributesTest()
{
}

void AttributesTest::process()
{
	TEST(testAttributesTest);
}

void AttributesTest::setup()
{
}

void AttributesTest::teardown()
{
}

void AttributesTest::testAttributesTest()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/Language/AttributesTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}