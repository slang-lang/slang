
#ifndef Testing_Interfaces_InterfacesTest_h
#define Testing_Interfaces_InterfacesTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Interfaces {


class InterfacesTest : private Utils::Common::Logger,
                       public GenericTest
{
public:
    InterfacesTest(const Utils::Common::ILogger *p);
    ~InterfacesTest();

public:
    void process();
    void setup();
    void teardown();

private:	// Tests
    void testBasicInterfaces();
};


}
}


#endif
