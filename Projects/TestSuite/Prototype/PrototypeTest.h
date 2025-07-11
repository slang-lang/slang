
#ifndef _Testing_Prototype_PrototypeTest_h_
#define _Testing_Prototype_PrototypeTest_h_


// Library includes

// Project includes
#include <Logger/Logger.h>
#include <Framework/UnitTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Prototype {


class PrototypeTest : public UnitTest,
					  private Utils::Common::Logger
{
public:
	explicit PrototypeTest( const Utils::Common::ILogger* p );
	~PrototypeTest() = default;

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testAdvancedPrototypeTest();
	void testBasicPrototypeTest();
	void testBasicPrototypeWithInheritanceConstraint();
	void testBasicPrototypeWithObjectTest();
	void testFail_BasicPrototypeWithInheritanceConstraint();
	void testFail_PrototypeAssignment();
	void testInheritFromPrototypeTest();
	void testPrototypeAsMember();
	void testPrototypeAsParameter();
	void testPrototypeAsPrototypedMember();
	void testPrototypeAsReturnValue();
};


}
}


#endif
