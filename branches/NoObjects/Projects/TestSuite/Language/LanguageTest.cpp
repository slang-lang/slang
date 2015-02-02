
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


::Utils::Printer stdoutPrinter;


LanguageTest::LanguageTest(const ::Utils::Common::Logger *p)
: ::Utils::Common::Logger(p, "Language")
{
}

void LanguageTest::process()
{
	TEST(testAssert);
	TEST(testComment);
	TEST(testFor);
	TEST(testIf);
	TEST(testPrint);
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
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		s->execute("test_assert", ParameterList());

		// automatic success
		delete s;
	}
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
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
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		s->execute("test_comment", ParameterList());

		// automatic success
		delete s;
	}
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
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
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		s->execute("test_for", ParameterList());

		// automatic success
		delete s;
	}
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
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
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		s->execute("test_if", ParameterList());

		// automatic success
		delete s;
	}
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
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
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		s->execute("test_print", ParameterList());

		// automatic success
		delete s;
	}
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
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
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		s->execute("test_while", ParameterList());

		// automatic success
		delete s;
	}
	catch ( ObjectiveScript::Utils::Exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception: " << e.what());
	}
}

}
}
