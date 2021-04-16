
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "MathTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Namespace declartations
using namespace Slang;


namespace Testing {
namespace Math {


MathTest::MathTest( const Utils::Common::ILogger* p )
: UnitTest( "MathTest" ),
  Utils::Common::Logger( p, "MathTest" )
{
}

void MathTest::process()
{
	TEST(testBasicExpressionParsing);
	TEST(testDataTypeBool);
	TEST(testDataTypeDouble);
	TEST(testDataTypeFloat);
	TEST(testDataTypeInt);
	TEST(testSimpleMath);
	TEST(testUnaryMinus);
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
		vm.runScriptFromFile("Tests/Math/BasicTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void MathTest::testDataTypeBool()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Math/DataTypeBool.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void MathTest::testDataTypeDouble()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Math/DataTypeDouble.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void MathTest::testDataTypeFloat()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Math/DataTypeFloat.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void MathTest::testDataTypeInt()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Math/DataTypeInt.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void MathTest::testSimpleMath()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Math/SimpleMath.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void MathTest::testUnaryMinus()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Math/UnaryMinus.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}


}
}
