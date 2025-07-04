
#ifndef Testing_Inheritance_InheritanceTest_h
#define Testing_Inheritance_InheritanceTest_h


// Library includes

// Project includes
#include <Logger/Logger.h>
#include <Framework/UnitTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Inheritance {


class InheritanceTest : public UnitTest,
						private Utils::Common::Logger
{
public:
    explicit InheritanceTest( const Utils::Common::ILogger* p );
    ~InheritanceTest() = default;

public:
    void process();
    void setup();
    void teardown();

private:	// Tests
    void testBasicInheritanceTest();
	void testDefaultConstructorTest();
	void testExceptionDuringConstructorTest();
	void testExceptionDuringDestructorTest();
	void testFinalMethodTest();
	void testHybridConstructorTest();
	void testKeywordBase();
	void testSpecializedConstructorTest();
};


}
}


#endif
