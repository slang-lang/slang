
#ifndef _Framework_TestFramework_h_
#define _Framework_TestFramework_h_


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


#define COMPARE( exp, act ) \
	(  exp == act ) ? true : false

#define SKIP( ) \
	return; \


// Compares to values, is not equal, test fails.
#define TCOMPARE( exp, act ) \
	if (  exp != act ) { \
		mFailed++; \
		mLastResult = GenericTest::Failed; \
		std::cout << __FILE__ << ":" << __LINE__ << " excepted: " << exp << ", actual: " << act << std::endl; \
		return; \
	}

// If used, the active test automatically fails.
#define TFAIL( expr ) \
	mFailed++; \
	mLastResult = GenericTest::Failed; \
	std::cout << __FILE__ << ":" << __LINE__ << ": " << expr << std::endl; \
	return; \

// Print an expression.
#define TPRINT( expr ) \
	std::cout << expr << std::endl;

// Skips the active test.
#define TSKIP( expr ) \
	mSkipped++; \
	mLastResult = GenericTest::Skipped; \
	if ( expr && strlen(expr) > 0 ) { \
		std::cout << expr << std::endl; \
	} \
	return;

// Verifys that the expression is true.
#define TVERIFY( expr ) \
	if ( !expr ) { \
		mFailed++; \
		mLastResult = GenericTest::Failed; \
		std::cout << __FILE__ << ":" << __LINE__ << ": " << expr << std::endl; \
		return; \
	}

// Expects and catches exeptions.
#define TTHROWS( func, ex ) \
	{ \
		bool __was__ex__thrown = false; \
		try { \
			(func); \
		} \
		catch ( ex& ) { \
			__was__ex__thrown = true; \
		} \
		TVERIFY( __was__ex__thrown ) \
	}

// Runs the given test.
#define TEST( exp ) \
	{ \
		mRun++; \
		mLastResult = GenericTest::Passed; \
		exp(); \
		switch ( mLastResult ) { \
			case GenericTest::Failed:  std::cout << "!!!FAILED:  " << __FUNCTION__ << ": " << std::endl; break; \
			case GenericTest::Passed:  std::cout << "PASSED:  " << __FUNCTION__ << ": " << std::endl; break; \
			case GenericTest::Skipped: std::cout << "SKIPPED: " << __FUNCTION__ << ": " << std::endl; break; \
		} \
	}


namespace Testing {




}


#endif _Framework_TestFramework_h_
