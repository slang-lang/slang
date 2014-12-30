
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

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


::Utils::Printer stdoutPrinter;


PrototypeTest::PrototypeTest(const ::Utils::Common::Logger *p)
: ::Utils::Common::Logger(p, "PrototypeTest")
{
}

void PrototypeTest::process()
{
//	TEST(testBasicObject);
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

		//s->execute("test_assert", ParameterList());
		s->execute("test_comments", ParameterList());
		s->execute("test_executeMethod", ParameterList());
		//s->execute("test_for", ParameterList());

		{
			ParameterList params;
			params.push_back(Parameter("param1", "Number", "1"));
			s->execute("test_if", params);
		}
		s->execute("test_localVar", ParameterList());
		{
			ParameterList params;
			params.push_back(Parameter("param1", "String", "1"));
			s->execute("test_print", params);
		}
		s->execute("test_staticLocalVar", ParameterList());
		{
			ParameterList params;
			params.push_back(Parameter("maxCount", "Number", "5"));
			s->execute("test_while", params);
		}

		// automatic success
		delete s;
	}
	catch ( std::exception& ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception!");
	}
}

void PrototypeTest::testBasicObject()
{
	try {
		VirtualMachine vm;
		vm.connectPrinter(&stdoutPrinter);

		Script *s = vm.create("Tests/BasicObjectTest.os");

		// automatic success
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

		// automatic success
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

		ParameterList params;
		s->execute("test", params);

		// automatic success
		delete s;
	}
	catch ( std::exception& ) {
		// exception has been thrown: test failed!
		TFAIL("caught exception!");
	}
}


}
}
