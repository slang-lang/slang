
#ifndef Testing_RealWorldUsage_RealWorldUsageTest_h
#define Testing_RealWorldUsage_RealWorldUsageTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace RealWorldUsage {


class RealWorldUsageTest : public GenericTest,
				 private Utils::Common::FileLogger
{
public:
	RealWorldUsageTest(const Utils::Common::ILogger *p);
	virtual ~RealWorldUsageTest() { }

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testAlternateMemberDeclaration();
	void testAutoBoxing();
	void testCWithNamespace();
	void testCreateScriptFromString();
	void testDeeperNamespaces();
};


}
}


#endif
