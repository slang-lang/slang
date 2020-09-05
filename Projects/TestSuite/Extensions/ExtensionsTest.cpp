
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "ExtensionsTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Namespace declartations
using namespace Slang;


namespace Testing {
namespace Extensions {


ExtensionsTest::ExtensionsTest(const ::Utils::Common::ILogger *p)
: GenericTest("ExtensionsTest"),
  ::Utils::Common::FileLogger(p, "ExtensionsTest")
{
}

void ExtensionsTest::process()
{
/*
	TEST(testBasicExpressionParsing);
	TEST(testDataTypeBool);
	TEST(testDataTypeDouble);
	TEST(testDataTypeFloat);
	TEST(testDataTypeInt);
	TEST(testSimpleExtensions);
	TEST(testUnaryMinus);
*/
}

void ExtensionsTest::setup()
{
}

void ExtensionsTest::teardown()
{
}

/*
void ExtensionsTest::testBasicExpressionParsing()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Extensions/BasicTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ExtensionsTest::testDataTypeBool()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Extensions/DataTypeBool.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ExtensionsTest::testDataTypeDouble()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Extensions/DataTypeDouble.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ExtensionsTest::testDataTypeFloat()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Extensions/DataTypeFloat.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ExtensionsTest::testDataTypeInt()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Extensions/DataTypeInt.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ExtensionsTest::testSimpleExtensions()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Extensions/SimpleExtensions.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void ExtensionsTest::testUnaryMinus()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Extensions/UnaryMinus.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}
*/


}
}
