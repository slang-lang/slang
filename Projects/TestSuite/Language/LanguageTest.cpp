
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "LanguageTest.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Core/Utils/Exceptions.h>

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Language {


LanguageTest::LanguageTest(const ::Utils::Common::ILogger *p)
: ::Utils::Common::Logger(p, "Language")
{
}

void LanguageTest::process()
{
	TEST(testAssert);
	TEST(testBooleanOperators);
	TEST(testComment);
	TEST(testConstCorrectness1);
	TEST(testConstCorrectness2);
	TEST(testConstCorrectness3);
	TEST(testDefaultParameter);
	TEST(testException);
	TEST(testFinal);
	TEST(testFor);
	TEST(testIf);
	TEST(testInfixOperator);
	TEST(testLawOfDemeter);
	TEST(testMethodOverloading);
	TEST(testObjectEquality);
	TEST(testObjectReference);
	TEST(testParameters);
	TEST(testPostfixOperator);
	TEST(testPrint);
	//TEST(testSanityChecker);			// temporary disabled
	TEST(testScope);
	//TEST(testStaticLocalVariable);
	//TEST(testSwitch);					// not yet implemented
	TEST(testThis);
	TEST(testTypeCast);
	TEST(testWhile);

// not yet implemented
	//TEST(testInterfaces);
	//TEST(testNamespaces);
}

void LanguageTest::setup()
{
}

void LanguageTest::teardown()
{
}

void LanguageTest::testAssert()
{
	try {
		VirtualMachine vm;

		TTHROWS(vm.createScriptFromFile("Tests/Language/AssertTest.os"), ObjectiveScript::Utils::Exceptions::AssertionFailed);

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/ConstCorrectness1.os"), ObjectiveScript::Utils::Exceptions::ConstCorrectnessViolated);

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/ConstCorrectness2.os"), ObjectiveScript::Utils::Exceptions::ConstCorrectnessViolated);

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/ConstCorrectness3.os"), ObjectiveScript::Utils::Exceptions::ConstCorrectnessViolated);

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

void LanguageTest::testFinal()
{
	try {
		VirtualMachine vm;

		TTHROWS(vm.createScriptFromFile("Tests/Language/FinalTest.os"), ObjectiveScript::Utils::Exceptions::ConstCorrectnessViolated);

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

void LanguageTest::testInterfaces()
{
	try {
		VirtualMachine vm;

		Script *s = vm.createScriptFromFile("Tests/Language/InterfacesTest.os");

		ParameterList params;
		s->execute("GetBox", params);

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void LanguageTest::testLawOfDemeter()
{
	try {
		VirtualMachine vm;

		TTHROWS(vm.createScriptFromFile("Tests/Language/LawOfDemeterTest.os"), ObjectiveScript::Utils::Exceptions::LawOfDemeterViolated);

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
		params.push_back(Parameter("argc", Runtime::NumberObject::TYPENAME, "2"));
		params.push_back(Parameter("argv", Runtime::StringObject::TYPENAME, ""));
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

		TTHROWS(vm.createScriptFromFile("Tests/Language/SanityChecker.os"), ObjectiveScript::Utils::Exceptions::SyntaxError);

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

		TTHROWS(vm.createScriptFromFile("Tests/Language/SwitchTest.os"), ObjectiveScript::Utils::Exceptions::NotImplemented);

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
