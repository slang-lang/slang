
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "TestFrameworkTest.h"

// Library includes
#include <exception>

// Project includes

// Namespace declarations


namespace Testing {
namespace Framework {


TestFrameworkTest::TestFrameworkTest( const Utils::Common::ILogger* p )
: GenericTest( "TestFrameworkTest" ),
  Utils::Common::Logger( p, "TestFrameworkTest" )
{
}

void TestFrameworkTest::dont_throw_std_ex()
{
	// do nothing
	// or anything
	// but don't throw a std::exception
}

void TestFrameworkTest::preventFail(bool t, bool f, bool &result)
{
	TestResult mResult;

	// reset result to false
	result = false;

	// if the compare result is NOT ok:
	// return with result as false
	// this also sets mFailed (this is some sort of hack, but hey, it works)
	TCOMPARE(t, f);

	if ( mResult.Failed > 0 ) {
		result = false;
		return;
	}

	// if the compare result is ok:
	// return with result as true
	result = true;
}

void TestFrameworkTest::process()
{
	TEST(testCOMPARE);
	TEST(testTCOMPARE);
	TEST(testTFAIL);
	TEST(testTSKIP);
	TEST(testTTHROWS);
	TEST(testTVERIFY);
}

void TestFrameworkTest::setup()
{
}

void TestFrameworkTest::teardown()
{
}

void TestFrameworkTest::testCOMPARE()
{
	// declare (and initialize)
	bool f = false;
	bool t = false;


	// test 1
	if ( COMPARE(true, false) ) {
		assert(!"true == false");
	}

	// test 2
	t = true;
	f = false;

	if ( COMPARE(t, f) ) {
		assert(!"true == false");
	}

	// test 3
	t = true;
	f = true;

	if ( !COMPARE(t, f) ) {
		assert(!"true != true");
	}

	// test 4
	t = false;
	f = false;

	if ( !COMPARE(t, f) ) {
		assert(!"false != false");
	}
}

void TestFrameworkTest::testTCOMPARE()
{
	// declare (and initialize)
	bool f = false;
	bool result = false;
	bool t = false;


	// test 1
	t = true;
	f = false;

	//preventFail(t, f, result);
	assert(!result);

	// test 2
	t = true;
	f = true;

	preventFail(t, f, result);
	assert(result);

	// test 3
	t = false;
	f = false;

	preventFail(t, f, result);
	assert(result);
}

void TestFrameworkTest::testTFAIL()
{
// skipping fail-test
TSKIP("");

	--mResult.Failed;
	//std::cout << "PASSED: ";
	TFAIL("this should fail");
}

void TestFrameworkTest::testTSKIP()
{
// skipping skip-test
TSKIP("");

	--mResult.Skipped;
	std::cout << "PASSED: ";
	TSKIP("skipping test");

	// should not be executed:
	TFAIL("failing test");
}

void TestFrameworkTest::testTTHROWS()
{
	TTHROWS(throw_std_ex(), std::exception);

	//TTHROWS(dont_throw_std_ex(), std::exception);
}

void TestFrameworkTest::testTVERIFY()
{
	// declare (and initialize)
	bool f = false;
	bool t = false;


	// test 1
	t = true;
	f = true;

	TVERIFY( (t == f) );


	// test 2
	t = false;
	f = false;

	TVERIFY( (t == f) );
}

void TestFrameworkTest::throw_std_ex()
{
	// do nothing
	// but throw a std::exception
	throw std::exception(/*"std::exception"*/);
}


}
}
