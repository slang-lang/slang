
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "InheritanceTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Core/Utils/Exceptions.h>

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Inheritance {


InheritanceTest::InheritanceTest(const ::Utils::Common::ILogger *p)
: ::Utils::Common::Logger(p, "AttributesTest")
{
}

InheritanceTest::~InheritanceTest()
{
}

void InheritanceTest::process()
{
    TEST(testBasicInheritance);
}

void InheritanceTest::setup()
{
}

void InheritanceTest::teardown()
{
}

void InheritanceTest::testBasicInheritance()
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


}
}
