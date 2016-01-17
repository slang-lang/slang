
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
	TEST(testMethodOverloading);
	TEST(testObjectReference);
	TEST(testParameters);
	TEST(testPrint);
	//TEST(testSanityChecker);			// temporary disabled
	TEST(testScope);
	TEST(testStaticLocalVariable);
	//TEST(testSwitch);					// not yet implemented
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

		TTHROWS(vm.create("Tests/Language/AssertTest.os"), ObjectiveScript::Utils::Exceptions::AssertionFailed);

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

		vm.create("Tests/Language/BooleanOperators.os");

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

		vm.create("Tests/Language/CommentTest.os");

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

		TTHROWS(vm.create("Tests/Language/ConstCorrectness1.os"), ObjectiveScript::Utils::Exceptions::ConstCorrectnessViolated);

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

		TTHROWS(vm.create("Tests/Language/ConstCorrectness2.os"), ObjectiveScript::Utils::Exceptions::ConstCorrectnessViolated);

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

		TTHROWS(vm.create("Tests/Language/ConstCorrectness3.os"), ObjectiveScript::Utils::Exceptions::ConstCorrectnessViolated);

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

		vm.create("Tests/Language/DefaultParameter.os");

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

		vm.create("Tests/Language/ExceptionTest.os");

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

		TTHROWS(vm.create("Tests/Language/FinalTest.os"), ObjectiveScript::Utils::Exceptions::ConstCorrectnessViolated);

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

		vm.create("Tests/Language/ForLoopTest.os");

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

		vm.create("Tests/Language/IfTest.os");

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

		Script *s = vm.create("Tests/Language/InterfacesTest.os");

		ParameterList params;
		s->execute("GetBox", params);

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

		vm.create("Tests/Language/MethodOverloadingTest.os");

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

		vm.create("Tests/Language/NamespaceTest.os");

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

		vm.create("Tests/Language/ObjectReference.os");

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
		params.push_back(Parameter("argc", NumberObject::TYPENAME, "2"));
		params.push_back(Parameter("argv", StringObject::TYPENAME, ""));
		vm.create("Tests/Language/ParameterTest.os", params);

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

		vm.create("Tests/Language/PrintTest.os");

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

		TTHROWS(vm.create("Tests/Language/SanityChecker.os"), ObjectiveScript::Utils::Exceptions::SyntaxError);

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

		vm.create("Tests/Language/ScopeTest.os");

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

		vm.create("Tests/Language/StaticVariablesTest.os");

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

		TTHROWS(vm.create("Tests/Language/SwitchTest.os"), ObjectiveScript::Utils::Exceptions::NotImplemented);

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

		vm.create("Tests/Language/WhileTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// unexpected exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
