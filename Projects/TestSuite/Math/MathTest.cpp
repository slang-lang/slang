
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


MathTest::MathTest(const ::Utils::Common::ILogger *p)
: ::Utils::Common::Logger(p, "Math")
{
}

void MathTest::process()
{
	TEST(testBasicExpressionParsing);
	TEST(testDataTypeBool);
	TEST(testDataTypeFloat);
	TEST(testDataTypeInt);
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
		vm.createScriptFromFile("Tests/Math/BasicTest.os");

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
		vm.createScriptFromString(
			"public object Main {\
				public void Main() {\
					number one = 1;\
					print(\"one = \" + one);\
				}\
			}"
		);

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
		vm.createScriptFromFile("Tests/Math/DataTypeFloat.os");

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
		vm.createScriptFromFile("Tests/Math/DataTypeInt.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
