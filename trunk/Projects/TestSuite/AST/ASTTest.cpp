
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "ASTTest.h"

// Library includes

// Project includes
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace AST {


ASTTest::ASTTest(const ::Utils::Common::ILogger *p)
: GenericTest("ASTTest"),
  ::Utils::Common::Logger(p, "ASTTest")
{
}

ASTTest::~ASTTest()
{
}

void ASTTest::process()
{
	TEST(testAssert);
	TEST(testAssignment);
	TEST(testBreak);
	TEST(testContinue);
	TEST(testExit);
	TEST(testExpression);
	TEST(testFor);
	TEST(testForeach);
	TEST(testGenerator);
	TEST(testIf);
	TEST(testNew);
	TEST(testReturn);
	TEST(testSwitch);
	TEST(testThrow);
	TEST(testTry);
	TEST(testTypeDeclaration);
	TEST(testUnaryExpression);
	TEST(testWhile);
}

void ASTTest::setup()
{
}

void ASTTest::teardown()
{
}

void ASTTest::testAssert()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/AssertTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testAssignment()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/AssignmentTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testBreak()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/BreakTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testContinue()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/ContinueTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testExit()
{
TSKIP("skipping ExitTest.os");

	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/ExitTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testExpression()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/ExpressionTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testFor()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/ForTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testForeach()
{
TSKIP("foreach not yet supported");

	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/ForeachTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testGenerator()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/GeneratorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testIf()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/IfTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testNew()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/NewTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testReturn()
{
	try {
		VirtualMachine vm;

		Runtime::Object returnValue;
		vm.createScriptFromFile("Tests/AST/ReturnTest.os", ParameterList(), &returnValue);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testSwitch()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/SwitchTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testThrow()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.createScriptFromFile("Tests/AST/ThrowTest.os"), Common::Exceptions::Exception);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testTry()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/TryTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testTypeDeclaration()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/TypeDeclarationTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testUnaryExpression()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/UnaryExpressionTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testWhile()
{
	try {
		VirtualMachine vm;
		vm.createScriptFromFile("Tests/AST/WhileTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}