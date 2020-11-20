
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "InterfacesTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Namespace declarations
using namespace Slang;


namespace Testing {
namespace Interfaces {


InterfacesTest::InterfacesTest( const Utils::Common::ILogger* p )
: GenericTest( "InterfacesTest" ),
  Utils::Common::Logger( p, "InterfacesTest" )
{
}

void InterfacesTest::process()
{
    TEST(testBasicInterfaces);
    TEST(testFail_MethodImplemented);
    TEST(testInterfaceAsParameter);
    TEST(testInterfaceAsReturnValue);
    TEST(testInterfaceObject);
    TEST(testSlightlyMoreAdvancedTest);
}

void InterfacesTest::setup()
{
}

void InterfacesTest::teardown()
{
}

void InterfacesTest::testBasicInterfaces()
{
    try {
        VirtualMachine vm;
        vm.runScriptFromFile("Tests/Interfaces/BasicInterfacesTest.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InterfacesTest::testFail_MethodImplemented()
{
    try {
        VirtualMachine vm;
        TTHROWS(vm.runScriptFromFile("Tests/Interfaces/Fail_MethodImplemented.os"), Designtime::Exceptions::SyntaxError);

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InterfacesTest::testInterfaceObject()
{
TSKIP("inheriting from interfaces does not make an object abstract yet");

    try {
        VirtualMachine vm;
        TTHROWS(vm.runScriptFromFile("Tests/Interfaces/InterfaceObject.os"), Common::Exceptions::AbstractException);

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InterfacesTest::testInterfaceAsParameter()
{
    try {
        VirtualMachine vm;
        vm.runScriptFromFile("Tests/Interfaces/InterfaceAsParameter.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InterfacesTest::testInterfaceAsReturnValue()
{
    try {
        VirtualMachine vm;
        vm.runScriptFromFile("Tests/Interfaces/InterfaceAsReturnValue.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InterfacesTest::testSlightlyMoreAdvancedTest()
{
    try {
        VirtualMachine vm;
        vm.runScriptFromFile("Tests/Interfaces/SlightlyMoreAdvancedTest.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}



}
}
