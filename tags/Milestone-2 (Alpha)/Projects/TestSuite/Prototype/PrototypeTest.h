
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
					  private Utils::Common::Logger
{
public:
	PrototypeTest(const Utils::Common::ILogger *p);
	virtual ~PrototypeTest() { }

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testPrototypeDeclaration();
	void testPrototypeUsage();
};


}
}


#endif