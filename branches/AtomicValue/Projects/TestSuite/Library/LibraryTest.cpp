
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "LibraryTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Core/Utils/Exceptions.h>

// Extension includes
#ifdef USE_SYSTEM_EXTENSION
#	include <System/SystemExtension.h>
#endif

// Namespace declartations
using namespace ObjectiveScript;


namespace Testing {
namespace Library {


LibraryTest::LibraryTest(const ::Utils::Common::ILogger *p)
: GenericTest("LibraryTest"),
  ::Utils::Common::Logger(p, "LibraryTest")
{
}

void LibraryTest::process()
{
	TEST(testBoolean);
	TEST(testDouble);
	TEST(testFloat);
	TEST(testInteger);
	TEST(testString);
}

void LibraryTest::setup()
{
}

void LibraryTest::teardown()
{
}

void LibraryTest::testBoolean()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/Library/BooleanTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testDouble()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/Library/DoubleTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testFloat()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/Library/FloatTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}


void LibraryTest::testInteger()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/Library/IntegerTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}


void LibraryTest::testString()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new ObjectiveScript::Extensions::System::SystemExtension());
#endif
		vm.createScriptFromFile("Tests/Library/StringTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}


}
}
