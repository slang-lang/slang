
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

// Extension includes
#ifdef USE_SYSTEM_EXTENSION
#	include <System/SystemExtension.h>
#endif

// Namespace declarations
using namespace Slang;


namespace Testing {
namespace Prototype {


PrototypeTest::PrototypeTest(const ::Utils::Common::ILogger *p)
: GenericTest("PrototypeTest"),
  ::Utils::Common::FileLogger(p, "PrototypeTest")
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
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Prototypes/AdvancedPrototypeTest.os");

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
		vm.runScriptFromFile("Tests/Prototypes/BasicPrototypeTest.os");

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
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Prototypes/BasicPrototypeWithInheritanceConstraint.os");

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
		vm.runScriptFromFile("Tests/Prototypes/BasicPrototypeWithObjectTest.os");

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
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		TTHROWS(vm.runScriptFromFile("Tests/Prototypes/Fail_BasicPrototypeWithInheritanceConstraint.os"), Slang::Common::Exceptions::TypeMismatch);
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
		//TTHROWS(vm.runScriptFromFile("Tests/Prototypes/Fail_PrototypeAssignment.os"), Slang::Common::Exceptions::TypeMismatch);
		TTHROWS(vm.runScriptFromFile("Tests/Prototypes/Fail_PrototypeAssignment.os"), Slang::Common::Exceptions::TypeMismatch);
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
		//TTHROWS(vm.runScriptFromFile("Tests/Prototypes/InheritFromPrototypeTest.os"), Slang::Common::Exceptions::NotSupported);
		vm.runScriptFromFile("Tests/Prototypes/InheritFromPrototypeTest.os");
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
		vm.runScriptFromFile("Tests/Prototypes/PrototypeAsMember.os");

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
		vm.runScriptFromFile("Tests/Prototypes/PrototypeAsParameter.os");

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
		vm.runScriptFromFile("Tests/Prototypes/PrototypeAsPrototypedMember.os");

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
		vm.runScriptFromFile("Tests/Prototypes/PrototypeAsReturnValue.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
