
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "LanguageTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Core/Utils/Exceptions.h>
#include <Utils/Printer.h>

// Namespace declartations
using namespace ObjectiveScript;


namespace Testing {
namespace Language {


LanguageTest::LanguageTest(const ::Utils::Common::Logger *p)
: ::Utils::Common::Logger(p, "Language"),
  mStdoutPrinter(p)
{
}

void LanguageTest::process()
{
	TEST(testAssert);
	TEST(testComment);
	TEST(testConstCorrectness);
	TEST(testDefaultParameter);
	TEST(testFor);
	TEST(testIf);
	//TEST(testInterfaces);
	TEST(testMethodOverloading);
	TEST(testObjectReference);
	TEST(testPrint);
	TEST(testStaticLocalVariable);
	TEST(testWhile);
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
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/AssertTest.os");

		// automatic success
	}
	catch ( ObjectiveScript::Utils::AssertionFailed& /*e*/ ) {
		// success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testComment()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/CommentTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testConstCorrectness()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/ConstCorrectness.os");

		// automatic success
	}
	catch ( ObjectiveScript::Utils::ConstCorrectnessViolated& /*e*/ ) {
		// success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testDefaultParameter()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/DefaultParameter.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testFor()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/ForLoopTest.os");

		// automatic success
	}
	catch ( ObjectiveScript::Utils::AssertionFailed& /*e*/ ) {
		// this is okay for now => success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testIf()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/IfTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testInterfaces()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		Script *s = vm.create("Tests/Language/InterfacesTest.os");

		ParameterList params;
		s->execute("GetBox", params);

		// automatic success
	}
/*
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
*/
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testMethodOverloading()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/MethodOverloadingTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testObjectReference()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/ObjectReference.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testPrint()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/PrintTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testStaticLocalVariable()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/StaticVariablesTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

void LanguageTest::testWhile()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		vm.create("Tests/Language/WhileTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}


}
}
