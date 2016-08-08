
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "InterfacesTest.h"

// Library includes

// Project includes
#include <Core/Script.h>
#include <Core/VirtualMachine.h>
#include <Core/Utils/Exceptions.h>

// Namespace declarations
using namespace ObjectiveScript;


namespace Testing {
namespace Interfaces {


InterfacesTest::InterfacesTest(const ::Utils::Common::ILogger *p)
: GenericTest("InterfacesTest"),
  ::Utils::Common::Logger(p, "InterfacesTest")
{
}

InterfacesTest::~InterfacesTest()
{
}

void InterfacesTest::process()
{
    TEST(testBasicInterfaces);
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
        TTHROWS(vm.createScriptFromFile("Tests/Interfaces/BasicInterfacesTest.os"), ObjectiveScript::Utils::Exceptions::AbstractException);

        // automatic success
    }
    catch ( std::exception& e ) {
        // exception has been thrown: test failed!
        TFAIL(e.what());
    }
}


}
}
