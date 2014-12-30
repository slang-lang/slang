
#ifndef _Testing_GenericTest_h_
#define _Testing_GenericTest_h_


// Library includes
#include <typeinfo>

// Project includes
#include "TestFramework.h"
#include <Common/Logger.h>

// Forward declarations

// Namespace declarations


#define NO_TYPEID


namespace Testing {


class GenericTest
{
public:
	typedef enum TestResult_e {
		Failed = 0,
		Passed,
		Skipped
	};

public:
	GenericTest()
	: mFailed(0),
	  mLastResult(Failed),
	  mRun(0),
	  mSkipped(0)
	{ }
	virtual ~GenericTest() { }

	virtual void process() = 0;
	virtual void setup() = 0;
	virtual void teardown() = 0;

public:
	void run() {
		setup();
		process();
		teardown();

		printResults();
	}

protected:
	TestResult_e mLastResult;

	int mFailed;
	int mRun;
	int	mSkipped;

private:
	void printResults() {
#ifndef NO_TYPEID
		std::cout << typeid(*this).name() << " Statistics: " << (mRun - mFailed - mSkipped) << " passed, " << mFailed << " failed, " << mSkipped << " skipped" << std::endl;
#else
		std::cout << " Statistics: " << (mRun - mFailed - mSkipped) << " passed, " << mFailed << " failed, " << mSkipped << " skipped" << std::endl;
#endif
	}
};

}

#endif _Testing_GenericTest_h_
