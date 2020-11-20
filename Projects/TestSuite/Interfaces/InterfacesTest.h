
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


class InterfacesTest : public GenericTest,
					   private Utils::Common::Logger
{
public:
    explicit InterfacesTest( const Utils::Common::ILogger* p );
    ~InterfacesTest() = default;

public:
    void process();
    void setup();
    void teardown();

private:	// Tests
    void testBasicInterfaces();
	void testFail_MethodImplemented();
	void testInterfaceObject();
	void testInterfaceAsParameter();
	void testInterfaceAsReturnValue();
	void testSlightlyMoreAdvancedTest();
};


}
}


#endif
