
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "ASTTest.h"

// Library includes

// Project includes
#include <Core/Designtime/Exceptions.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Extension includes
#ifdef USE_SYSTEM_EXTENSION
#	include <System/SystemExtension.h>
#endif

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
	TEST(testBase);
	TEST(testBreak);
	TEST(testContinue);
	TEST(testConstCorrectness1);
	TEST(testConstCorrectness2);
	TEST(testConstCorrectness3);
	TEST(testConstCorrectness4);
	TEST(testExit);
	TEST(testExpression);
	TEST(testFor);
	TEST(testForeach);
	TEST(testGenerator);
	TEST(testIf);
	TEST(testNamespace);
	TEST(testNew);
	TEST(testReturn);
	TEST(testScopeOperator);
	TEST(testSwitch);
	TEST(testTernaryOperator);
	TEST(testTernaryOperatorFail);
	TEST(testThis);
	TEST(testThrow);
	TEST(testTry);
	TEST(testTypecast);
	TEST(testTypeDeclaration);
	TEST(testTypeInference);
	TEST(testTypeSystem);
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
		vm.runScriptFromFile("Tests/AST/AssertTest.os");

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
		vm.runScriptFromFile("Tests/AST/AssignmentTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testBase()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/AST/BaseTest.os");

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
		vm.runScriptFromFile("Tests/AST/BreakTest.os");

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
		vm.runScriptFromFile("Tests/AST/ContinueTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testConstCorrectness1()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/AST/ConstCorrectnessTest1.os"), Common::Exceptions::ConstCorrectnessViolated);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testConstCorrectness2()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/AST/ConstCorrectnessTest2.os"), Common::Exceptions::ConstCorrectnessViolated);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testConstCorrectness3()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/AST/ConstCorrectnessTest3.os"), Common::Exceptions::ConstCorrectnessViolated);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testConstCorrectness4()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/AST/ConstCorrectnessTest4.os"), Common::Exceptions::StaticException);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testExit()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/AST/ExitTest.os"), Runtime::ControlFlow::E);

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
		vm.runScriptFromFile("Tests/AST/ExpressionTest.os");

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
		vm.runScriptFromFile("Tests/AST/ForTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testForeach()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new ObjectiveScript::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/AST/ForeachTest.os");

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
		vm.runScriptFromFile("Tests/AST/GeneratorTest.os");

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
		vm.runScriptFromFile("Tests/AST/IfTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testNamespace()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/AST/NamespaceTest.os");

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
		vm.runScriptFromFile("Tests/AST/NewTest.os");

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
		vm.runScriptFromFile("Tests/AST/ReturnTest.os", ParameterList(), &returnValue);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testScopeOperator()
{
	try {
		VirtualMachine vm;

		Runtime::Object returnValue;
		vm.runScriptFromFile("Tests/AST/ScopeOperatorTest.os", ParameterList(), &returnValue);

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
		vm.runScriptFromFile("Tests/AST/SwitchTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testTernaryOperator()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/AST/TernaryOperatorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testTernaryOperatorFail()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/AST/Fail_TernaryOperatorTest.os"), Designtime::Exceptions::SyntaxError);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testThis()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/AST/ThisTest.os");

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
		TTHROWS(vm.runScriptFromFile("Tests/AST/ThrowTest.os"), Runtime::ControlFlow::E);

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
		vm.runScriptFromFile("Tests/AST/TryTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testTypecast()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/AST/TypecastTest.os");

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
		vm.runScriptFromFile("Tests/AST/TypeDeclarationTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testTypeInference()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/AST/TypeInferenceTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void ASTTest::testTypeSystem()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/AST/TypeSystemTest.os");

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
		vm.runScriptFromFile("Tests/AST/UnaryExpressionTest.os");

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
		vm.runScriptFromFile("Tests/AST/WhileTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
