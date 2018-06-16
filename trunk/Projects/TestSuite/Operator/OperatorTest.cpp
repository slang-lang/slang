
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "OperatorTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Extension includes
#ifdef USE_SYSTEM_EXTENSION
#	include <System/SystemExtension.h>
#endif

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Operator {


OperatorTest::OperatorTest(const ::Utils::Common::Logger *p)
: GenericTest("OperatorTest"),
  ::Utils::Common::Logger(p, "OperatorTest")
{
}

void OperatorTest::process()
{
	TEST(testBooleanOperator);
	TEST(testBooleanOverloads_Assign);
	TEST(testBooleanOverloads_BitAnd);
	TEST(testBooleanOverloads_BitOr);
	TEST(testBooleanOverloads_Equal);
	TEST(testBooleanOverloads_Greater);
	TEST(testBooleanOverloads_Greater_Equal);
	TEST(testBooleanOverloads_Less);
	TEST(testBooleanOverloads_Less_Equal);
	TEST(testBooleanOverloads_Unequal);
	TEST(testIndexOperator);
	TEST(testInverseOperator);
	TEST(testIsOperator);
	TEST(testMathOverloadsWithNumbers);
	TEST(testMathOverloadsWithObjects);
	TEST(testUnaryValidate);
}

void OperatorTest::setup()
{
}

void OperatorTest::teardown()
{
}

void OperatorTest::testBooleanOperator()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOperatorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testBooleanOverloads_Assign()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOverloads_Assign.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testBooleanOverloads_BitAnd()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOverloads_BitAnd.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testBooleanOverloads_BitOr()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOverloads_BitOr.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testBooleanOverloads_Equal()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOverloads_Equal.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testBooleanOverloads_Greater()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOverloads_Greater.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testBooleanOverloads_Greater_Equal()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOverloads_Greater_Equal.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testBooleanOverloads_Less()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOverloads_Less.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testBooleanOverloads_Less_Equal()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOverloads_Less_Equal.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testBooleanOverloads_Unequal()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOverloads_Unequal.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testIndexOperator()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new ObjectiveScript::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Operator/IndexOperatorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testInverseOperator()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/InverseOperatorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testIsOperator()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/BooleanOverloads_Unequal.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testMathOverloadsWithNumbers()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/IsOperatorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testMathOverloadsWithObjects()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/MathOverloadsWithObjects.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testUnaryValidate()
{
TSKIP("unary validate is not yet implemented");

	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/UnaryValidate.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
