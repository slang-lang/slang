
#ifndef Testing_Utils_UtilsTest_h
#define Testing_Utils_UtilsTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/UnitTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace UtilsTest {


class UtilsTest : public UnitTest,
				  private Utils::Common::Logger
{
public:
	explicit UtilsTest( const Utils::Common::ILogger* p );
	~UtilsTest() = default;

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testSemVer();
	void testSplitBy();
};


}
}


#endif
