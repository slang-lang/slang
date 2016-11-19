
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "PrototypeTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>
#include <Core/Runtime/Exceptions.h>

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Prototype {


PrototypeTest::PrototypeTest(const ::Utils::Common::ILogger *p)
: GenericTest("PrototypeTest"),
  ::Utils::Common::Logger(p, "PrototypeTest")
{
}

void PrototypeTest::process()
{
	TEST(testAdvancedPrototypeTest);
	TEST(testBasicPrototypeTest);
	TEST(testBasicPrototypeWithInheritanceConstraint);
	TEST(testBasicPrototypeWithObjectTest);
	TEST(testFail_BasicPrototypeWithInheritanceConstraint);
	TEST(testFail_PrototypeAssignment);
	TEST(testInheritFromPrototypeTest);
	TEST(testPrototypeAsMember);
	TEST(testPrototypeAsParameter);
	TEST(testPrototypeAsPrototypedMember);
	TEST(testPrototypeAsReturnValue);
}

void PrototypeTest::setup()
{
}

void PrototypeTest::teardown()
{
}

void PrototypeTest::testAdvancedPrototypeTest()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Prototypes/AdvancedPrototypeTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testBasicPrototypeTest()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Prototypes/BasicPrototypeTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testBasicPrototypeWithInheritanceConstraint()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Prototypes/BasicPrototypeWithInheritanceConstraint.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testBasicPrototypeWithObjectTest()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Prototypes/BasicPrototypeWithObjectTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testFail_BasicPrototypeWithInheritanceConstraint()
{
	try {
		VirtualMachine vm;

		TTHROWS(vm.createScriptFromFile("Tests/Prototypes/Fail_BasicPrototypeWithInheritanceConstraint.os"), ObjectiveScript::Runtime::Exceptions::AssertionFailed);
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testFail_PrototypeAssignment()
{
	try {
		VirtualMachine vm;

		TTHROWS(vm.createScriptFromFile("Tests/Prototypes/Fail_PrototypeAssignment.os"), ObjectiveScript::Common::Exceptions::Exception);
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testInheritFromPrototypeTest()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Prototypes/InheritFromPrototypeTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testPrototypeAsMember()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Prototypes/PrototypeAsMember.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testPrototypeAsParameter()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Prototypes/PrototypeAsParameter.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testPrototypeAsPrototypedMember()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Prototypes/PrototypeAsPrototypedMember.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void PrototypeTest::testPrototypeAsReturnValue()
{
	try {
		VirtualMachine vm;

		vm.createScriptFromFile("Tests/Prototypes/PrototypeAsReturnValue.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
