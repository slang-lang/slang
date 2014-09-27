
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)

// Header
#include "PrototypeTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Utils/Printer.h>

// Namespace declartations
using namespace ObjectiveScript;


namespace Testing {
namespace Prototype {


Utils::Printer stdoutPrinter;


PrototypeTest::PrototypeTest(const Utils::Common::Logger *p)
: Utils::Common::Logger(p, "PrototypeTest")
{
}

void PrototypeTest::process()
{
	TEST(testBasicLanguage);
	TEST(testPrototypeDeclaration);
	TEST(testPrototypeUsage);
}

void PrototypeTest::setup()
{
}

void PrototypeTest::teardown()
{
}

void PrototypeTest::testBasicLanguage()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/BasicLanguageTest.os");

		//s->execute("test_assert", VariablesList());
		s->execute("test_comments", VariablesList());
		s->execute("test_executeMethod", VariablesList());
		//s->execute("test_for", VariablesList());

		{
			VariablesList params;
			params.push_back(Variable("param1", "Number", "1"));
			s->execute("test_if", params);
		}
		s->execute("test_localVar", VariablesList());
		{
			VariablesList params;
			params.push_back(Variable("param1", "String", "1"));
			s->execute("test_print", params);
		}
		s->execute("test_staticLocalVar", VariablesList());
		{
			VariablesList params;
			params.push_back(Variable("maxCount", "Number", "5"));
			s->execute("test_while", params);
		}

		// automatic succes
		delete s;
	}
	catch ( std::exception& ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception!");
	}
}

void PrototypeTest::testPrototypeDeclaration()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/PrototypeTest.os");

		// automatic succes
		delete s;
	}
	catch ( std::exception& ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception!");
	}
}

void PrototypeTest::testPrototypeUsage()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/PrototypeTest.os");

		VariablesList params;
		s->execute("test", params);

		// automatic succes
		delete s;
	}
	catch ( std::exception& ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception!");
	}
}


}
}
