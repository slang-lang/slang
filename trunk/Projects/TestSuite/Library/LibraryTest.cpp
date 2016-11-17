
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "LibraryTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

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
	TEST(testSystemBoolean);
	TEST(testSystemDouble);
	TEST(testSystemFloat);
	TEST(testSystemInteger);
	TEST(testSystemIOFile);
	TEST(testSystemIOLogger);
	TEST(testSystemString);
	TEST(testSystemStringIterator);
}

void LibraryTest::setup()
{
}

void LibraryTest::teardown()
{
}

void LibraryTest::testSystemBoolean()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/Library/System/BooleanTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemDouble()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/Library/System/DoubleTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemFloat()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/Library/System/FloatTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}


void LibraryTest::testSystemInteger()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/Library/System/IntegerTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemIOFile()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new ObjectiveScript::Extensions::System::SystemExtension());
#endif
		vm.createScriptFromFile("Tests/Library/System/IO/FileTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemIOLogger()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new ObjectiveScript::Extensions::System::SystemExtension());
#endif
		vm.createScriptFromFile("Tests/Library/System/IO/LoggerTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemString()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new ObjectiveScript::Extensions::System::SystemExtension());
#endif
		vm.createScriptFromFile("Tests/Library/System/StringTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemStringIterator()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new ObjectiveScript::Extensions::System::SystemExtension());
#endif
		vm.createScriptFromFile("Tests/Library/System/StringIteratorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}


}
}
