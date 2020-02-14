
#ifndef _Testing_TestFramework_TestFrameworkTest_h_
#define _Testing_TestFramework_TestFrameworkTest_h_


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Framework {


class TestFrameworkTest : public GenericTest,
						  private Utils::Common::FileLogger
{
public:
	TestFrameworkTest(const Utils::Common::ILogger *p);

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testCOMPARE();
	void testTCOMPARE();
	void testTFAIL();
	void testTSKIP();
	void testTTHROWS();
	void testTVERIFY();

private:
	void preventFail(bool t, bool f, bool &result);

	void dont_throw_std_ex();
	void throw_std_ex();
};


}
}


#endif
