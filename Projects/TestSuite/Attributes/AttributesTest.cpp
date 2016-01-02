
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

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Attributes {


AttributesTest::AttributesTest(const ::Utils::Common::ILogger *p)
: ::Utils::Common::Logger(p, "AttributesTest"),
  mPrinter(p)
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
		vm.setPrinter(&mPrinter);

		vm.create("Tests/Language/AttributesTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
