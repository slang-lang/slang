
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
  mStdoutPrinter(this)
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

	TEST(testConstCorrectness);
	TEST(testInterfaces);
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
		vm.connectPrinter(&mStdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		s->execute("test_comments", ParameterList());

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
		vm.connectPrinter(&mStdoutPrinter);

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
		vm.connectPrinter(&mStdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		ParameterList params;
		params.push_back(Parameter("param1", "Number", "1", false, Parameter::AccessMode::ByReference));
		s->execute("test_if", params);

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
		vm.connectPrinter(&mStdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		ParameterList params;
		params.push_back(Parameter("param1", "String", "parameter", false, Parameter::AccessMode::ByReference));
		s->execute("test_print", params);

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

void LanguageTest::testStaticLocalVariable()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		s->execute("test_static_local_variable", ParameterList());

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
		vm.connectPrinter(&mStdoutPrinter);

		Script *s = vm.create("Tests/Language/BasicLanguageTest.os");

		ParameterList params;
		params.push_back(Parameter("maxCount", "Number", "5", false, Parameter::AccessMode::ByValue));
		s->execute("test_while", params);

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

void LanguageTest::testConstCorrectness()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		Script *s = vm.create("Tests/Language/ConstCorrectness.os");

		ParameterList params;
		params.push_back(Parameter("two", "Number", "2", true, Parameter::AccessMode::ByReference));
		s->execute("ModifyConstParameter", params);

		s->execute("ModifyMemberInConstMethod", ParameterList());

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

void LanguageTest::testInterfaces()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&mStdoutPrinter);

		Script *s = vm.create("Tests/Language/InterfacesTest.os");

		ParameterList params;
		s->execute("GetBox", params);

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
