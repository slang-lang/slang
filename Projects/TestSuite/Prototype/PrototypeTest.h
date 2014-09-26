
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


class PrototypeTest : private Utils::Common::Logger,
					  public GenericTest
{
public:
	PrototypeTest(const Utils::Common::Logger *p);

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
