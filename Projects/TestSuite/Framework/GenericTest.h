
#ifndef _Testing_GenericTest_h_
#define _Testing_GenericTest_h_


// Library includes
//#include <boost/shared_ptr.hpp>
#include <typeinfo>

// Project includes
#include "TestFramework.h"
#include <Common/Logger.h>

// Forward declarations

// Namespace declarations


namespace Testing {


class GenericTest
{
public:
	//typedef boost::shared_ptr<GenericTest> Ptr;

public:
	typedef enum TestResult_e {
		Failed = 0,
		Passed,
		Skipped
	};

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

	void run() {
		setup();
			process();
		teardown();

		printResults();
	}

protected:
	TestResult_e	mLastResult;

	int mFailed;
	int mRun;
	int	mSkipped;

private:
	void printResults() {
		std::cout << typeid(*this).name() << " Statistics: " << (mRun - mFailed - mSkipped) << " passed, " << mFailed << " failed, " << mSkipped << " skipped" << std::endl;
	}
};

}

#endif _Testing_GenericTest_h_
