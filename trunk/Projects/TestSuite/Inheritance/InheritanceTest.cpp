
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "InheritanceTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Inheritance {


InheritanceTest::InheritanceTest(const ::Utils::Common::ILogger *p)
: GenericTest("InheritanceTest"),
  ::Utils::Common::Logger(p, "InheritanceTest")
{
}

InheritanceTest::~InheritanceTest()
{
}

void InheritanceTest::process()
{
    TEST(testBasicInheritanceTest);
	TEST(testDefaultConstructorTest);
	TEST(testExceptionDuringConstructorTest);
	TEST(testExceptionDuringDestructorTest);
    TEST(testFinalMethodTest);
	TEST(testHybridConstructorTest);
	TEST(testKeywordBase);
	TEST(testSpecializedConstructorTest);
}

void InheritanceTest::setup()
{
}

void InheritanceTest::teardown()
{
}

void InheritanceTest::testBasicInheritanceTest()
{
    try {
        VirtualMachine vm;
        vm.createScriptFromFile("Tests/Inheritance/BasicInheritanceTest.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InheritanceTest::testDefaultConstructorTest()
{
    try {
        VirtualMachine vm;
        vm.createScriptFromFile("Tests/Inheritance/DefaultConstructorTest.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InheritanceTest::testExceptionDuringConstructorTest()
{
    try {
        VirtualMachine vm;
        vm.createScriptFromFile("Tests/Inheritance/ExceptionDuringConstructor.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InheritanceTest::testExceptionDuringDestructorTest()
{
    try {
        VirtualMachine vm;
        vm.createScriptFromFile("Tests/Inheritance/ExceptionDuringDestructor.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InheritanceTest::testFinalMethodTest()
{
    try {
        VirtualMachine vm;
        vm.createScriptFromFile("Tests/Inheritance/FinalMethodTest.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InheritanceTest::testHybridConstructorTest()
{
    try {
        VirtualMachine vm;
        vm.createScriptFromFile("Tests/Inheritance/HybridConstructorTest.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InheritanceTest::testKeywordBase()
{
    try {
        VirtualMachine vm;
        vm.createScriptFromFile("Tests/Inheritance/KeywordTest_Base.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}

void InheritanceTest::testSpecializedConstructorTest()
{
    try {
        VirtualMachine vm;
        vm.createScriptFromFile("Tests/Inheritance/SpecializedConstructorTest.os");

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}


}
}