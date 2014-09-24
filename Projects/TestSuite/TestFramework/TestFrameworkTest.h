
#ifndef _Testing_TestFramework_TestFrameworkTest_h_
#define _Testing_TestFramework_TestFrameworkTest_h_


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {


class TestFrameworkTest : private Utils::Common::Logger,
						  public GenericTest
{
public:
	TestFrameworkTest(const Utils::Common::Logger *p);

public:
	void process();
	void setup();
	void teardown();

private:
	// Tests
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

#endif
