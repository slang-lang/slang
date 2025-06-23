
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "OperatorTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Extension includes
#ifdef USE_SYSTEM_EXTENSION
#	include <LIBC/Extension.h>
#	include <System/SystemExtension.h>
#endif

// Namespace declarations
using namespace Slang;


namespace Testing {
namespace Operator {


OperatorTest::OperatorTest( const Utils::Common::ILogger* p )
: UnitTest( "OperatorTest" ),
  Utils::Common::Logger( p, "OperatorTest" )
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
	//FIXME: TEST(testEnumeration);
	//FIXME: TEST(testIndexOperator);
	TEST(testInverseOperator);
	TEST(testIsOperator);
	TEST(testMathOverloadsWithNumbers);
	TEST(testMathOverloadsWithObjects);
	TEST(testRangeOperator);
	TEST(testShiftOperator);
	TEST(testUnaryMinus);
	TEST(testUnaryPlus);
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

void OperatorTest::testEnumeration()
{
    try {
        VirtualMachine vm;
        vm.runScriptFromFile("Tests/Operator/Enumeration.os");

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
		vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
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

void OperatorTest::testRangeOperator()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/RangeOperatorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testShiftOperator()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Operator/ShiftOperator.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testUnaryMinus()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Operator/UnaryMinus.os"), Slang::Common::Exceptions::UnknownOperation);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testUnaryPlus()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Operator/UnaryPlus.os"), Slang::Common::Exceptions::UnknownOperation);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void OperatorTest::testUnaryValidate()
{
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
