
#ifndef Testing_RealWorldUsage_RealWorldUsageTest_h
#define Testing_RealWorldUsage_RealWorldUsageTest_h


// Library includes

// Project includes
#include <Logger/Logger.h>
#include <Framework/UnitTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace RealWorldUsage {


class RealWorldUsageTest : public UnitTest,
				 		   private Utils::Common::Logger
{
public:
	explicit RealWorldUsageTest( const Utils::Common::ILogger* p );
	~RealWorldUsageTest() = default;

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
