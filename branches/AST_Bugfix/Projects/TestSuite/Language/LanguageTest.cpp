
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "LanguageTest.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Language {


LanguageTest::LanguageTest(const ::Utils::Common::ILogger *p)
: GenericTest("LanguageTest"),
  ::Utils::Common::Logger(p, "LanguageTest")
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
	TEST(testDefaultParameter);
	TEST(testEnum);
	TEST(testException);
	TEST(testFor);
	TEST(testForeach);
	TEST(GlobalVariableTest);
	TEST(testIf);
	TEST(testIncompleteBooleanEvaluation);
	TEST(testInfixOperator);
	TEST(testLawOfDemeter);
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

// not implemented
	//TEST(testStaticLocalVariable);	// static variables are not supported
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

		vm.createScriptFromFile("Tests/Language/GlobalVariableTest.os");

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/AbstractObjectTest.os"), ObjectiveScript::Common::Exceptions::AbstractException);

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/AssertTest.os"), ObjectiveScript::Runtime::Exceptions::AssertionFailed);

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

		vm.createScriptFromFile("Tests/Language/Assignment.os");

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
		vm.createScriptFromFile("Tests/Language/AttributesTest.os");

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

		vm.createScriptFromFile("Tests/Language/AtomicReference.os");

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

		vm.createScriptFromFile("Tests/Language/BooleanOperators.os");

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

		vm.createScriptFromFile("Tests/Language/CommentTest.os");

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/ConstCorrectness1.os"), ObjectiveScript::Common::Exceptions::ConstCorrectnessViolated);

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/ConstCorrectness2.os"), ObjectiveScript::Common::Exceptions::ConstCorrectnessViolated);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testConstCorrectness3()
{
TSKIP("const references are not yet const");

	try {
		VirtualMachine vm;

		TTHROWS(vm.createScriptFromFile("Tests/Language/ConstCorrectness3.os"), ObjectiveScript::Common::Exceptions::ConstCorrectnessViolated);

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/ConstCorrectness4.os"), ObjectiveScript::Common::Exceptions::ConstCorrectnessViolated);

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

		vm.createScriptFromFile("Tests/Language/DefaultParameter.os");

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

		vm.createScriptFromFile("Tests/Language/EnumTest.os");

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

		vm.createScriptFromFile("Tests/Language/ExceptionTest.os");

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

		vm.createScriptFromFile("Tests/Language/ForLoopTest.os");

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

		vm.createScriptFromFile("Tests/Language/ForeachTest.os");

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

		vm.createScriptFromFile("Tests/Language/IfTest.os");

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

		vm.createScriptFromFile("Tests/Language/IncompleteBooleanEvaluationTest.os");

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

		vm.createScriptFromFile("Tests/Language/InfixOperator.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testLawOfDemeter()
{
	TSKIP("skipping Law of Demeter test");

	try {
		VirtualMachine vm;

		TTHROWS(vm.createScriptFromFile("Tests/Language/LawOfDemeterTest.os"), ObjectiveScript::Designtime::Exceptions::LawOfDemeterViolated);

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

		vm.createScriptFromFile("Tests/Language/MethodOverloadingTest.os");

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

		vm.createScriptFromFile("Tests/Language/NamespaceTest.os");

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

		vm.createScriptFromFile("Tests/Language/ObjectEqualityTest.os");

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

		vm.createScriptFromFile("Tests/Language/ObjectReference.os");

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
		vm.createScriptFromFile("Tests/Language/ParameterTest.os", params);

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

		vm.createScriptFromFile("Tests/Language/PostfixOperator.os");

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

		vm.createScriptFromFile("Tests/Language/PrintTest.os");

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/SanityCheckerTest.os"), ObjectiveScript::Common::Exceptions::SyntaxError);

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

		vm.createScriptFromFile("Tests/Language/ScopeTest.os");

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/StaticMethodTest.os"), Common::Exceptions::StaticException);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testStaticLocalVariable()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Language/StaticVariablesTest.os");

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

		vm.createScriptFromFile("Tests/Language/SwitchTest.os");

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

		vm.createScriptFromFile("Tests/Language/ThisTest.os");

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/ThrowTest.os"), Common::Exceptions::Exception);

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

		vm.createScriptFromFile("Tests/Language/TypeCastTest.os");

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

		vm.createScriptFromFile("Tests/Language/TypeInferenceTest.os");

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

		vm.createScriptFromFile("Tests/Language/WhileTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
