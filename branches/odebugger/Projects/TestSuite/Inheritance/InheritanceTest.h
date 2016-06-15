
#ifndef Testing_Inheritance_InheritanceTest_h
#define Testing_Inheritance_InheritanceTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Inheritance {


class InheritanceTest : public GenericTest,
						private Utils::Common::Logger
{
public:
    InheritanceTest(const Utils::Common::ILogger *p);
    ~InheritanceTest();

public:
    void process();
    void setup();
    void teardown();

private:	// Tests
    void testBasicInheritanceTest();
	void testDefaultConstructorTest();
	void testExceptionDuringConstructorTest();
	void testExceptionDuringDestructorTest();
	void testHybridConstructorTest();
	void testKeywordBase();
	void testSpecializedConstructorTest();
};


}
}


#endif
