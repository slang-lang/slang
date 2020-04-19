
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "LanguageTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Extension includes
#ifdef USE_SYSTEM_EXTENSION
#	include <System/SystemExtension.h>
#endif

// Namespace declarations
using namespace Slang;


namespace Testing {
namespace Language {


LanguageTest::LanguageTest(const ::Utils::Common::ILogger *p)
: GenericTest("LanguageTest"),
  ::Utils::Common::FileLogger(p, "LanguageTest")
{
}

void LanguageTest::process()
{
	TEST(testAbstractObject);
	TEST(testAssert);
	TEST(testAssignment);
	TEST(testAttributes);
	TEST(testAtomicReference);
	TEST(testBooleanOperators);
	TEST(testComment);
	TEST(testConstCorrectness1);
	TEST(testConstCorrectness2);
	TEST(testConstCorrectness3);
	TEST(testConstCorrectness4);
	TEST(testCopy);
	TEST(testDefaultParameter);
	TEST(testEnum);
	TEST(testException);
	TEST(testFor);
	TEST(testForeach);
	TEST(GlobalVariableTest);
	TEST(testIf);
	TEST(testIncompleteBooleanEvaluation);
	TEST(testInfixOperator);
	TEST(testMethodOverloading);
	TEST(testNamespaces);
	TEST(testObjectEquality);
	TEST(testObjectReference);
	TEST(testParameters);
	TEST(testPostfixOperator);
	TEST(testPrint);
	TEST(testSanityChecker);
	TEST(testScope);
	TEST(testStaticMethod);
	TEST(testSwitch);
	TEST(testThis);
	TEST(testThrow);
	TEST(testTypeCast);
	TEST(testTypeInference);
	TEST(testWhile);
}

void LanguageTest::setup()
{
}

void LanguageTest::teardown()
{
}

void LanguageTest::GlobalVariableTest()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/GlobalVariableTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testAbstractObject()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Language/AbstractObjectTest.os"), Slang::Common::Exceptions::AbstractException);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testAssert()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Language/AssertTest.os"), Slang::Runtime::Exceptions::AssertionFailed);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testAssignment()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/Assignment.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testAttributes()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/AttributesTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testAtomicReference()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/AtomicReference.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testBooleanOperators()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/BooleanOperators.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testComment()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/CommentTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testConstCorrectness1()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Language/ConstCorrectness1.os"), Slang::Common::Exceptions::ConstCorrectnessViolated);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testConstCorrectness2()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Language/ConstCorrectness2.os"), Slang::Common::Exceptions::ConstCorrectnessViolated);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testConstCorrectness3()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Language/ConstCorrectness3.os"), Slang::Common::Exceptions::ConstCorrectnessViolated);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testConstCorrectness4()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Language/ConstCorrectness4.os"), Slang::Common::Exceptions::ConstCorrectnessViolated);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testCopy()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/CopyTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}
void LanguageTest::testDefaultParameter()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/DefaultParameter.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testEnum()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/EnumTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testException()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/ExceptionTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testFor()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/ForLoopTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testForeach()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Language/ForeachTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testIf()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/IfTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testIncompleteBooleanEvaluation()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/IncompleteBooleanEvaluationTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testInfixOperator()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/InfixOperator.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testMethodOverloading()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/MethodOverloadingTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testNamespaces()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/NamespaceTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testObjectEquality()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/ObjectEqualityTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testObjectReference()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/ObjectReference.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testParameters()
{
	try {
		VirtualMachine vm;

		ParameterList params;
		params.push_back(Parameter::CreateRuntime(Runtime::IntegerObject::TYPENAME, "2"));
		params.push_back(Parameter::CreateRuntime(Runtime::StringObject::TYPENAME, ""));

		TTHROWS(vm.runScriptFromFile("Tests/Language/ParameterTest.os", params), Common::Exceptions::ConstCorrectnessViolated);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testPostfixOperator()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/PostfixOperator.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}
void LanguageTest::testPrint()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/PrintTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testSanityChecker()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Language/SanityCheckerTest.os"), Slang::Designtime::Exceptions::SanityCheckError);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testScope()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/ScopeTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testStaticMethod()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Language/StaticMethodTest.os"), Common::Exceptions::StaticException);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testSwitch()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/SwitchTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testThis()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/ThisTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testThrow()
{
	try {
		VirtualMachine vm;
		TTHROWS(vm.runScriptFromFile("Tests/Language/ThrowTest.os"), Runtime::ControlFlow::E);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testTypeCast()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/TypeCastTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testTypeInference()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/TypeInferenceTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testWhile()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Language/WhileTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
