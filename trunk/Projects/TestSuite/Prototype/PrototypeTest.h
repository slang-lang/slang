
#ifndef _Testing_Prototype_PrototypeTest_h_
#define _Testing_Prototype_PrototypeTest_h_


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Prototype {


class PrototypeTest : public GenericTest,
					  private Utils::Common::FileLogger
{
public:
	PrototypeTest(const Utils::Common::ILogger *p);
	virtual ~PrototypeTest() { }

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
