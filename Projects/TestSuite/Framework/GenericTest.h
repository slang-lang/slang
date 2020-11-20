
#ifndef _Framework_GenericTest_h_
#define _Framework_GenericTest_h_


// Library includes
#include <typeinfo>
#include <utility>

// Project includes
#include "TestFramework.h"
#include <Common/Logger.h>

// Forward declarations

// Namespace declarations


namespace Testing {


class TestResult
{
public:
	TestResult()
	: Failed(0),
	  Run(0),
	  Skipped(0)
	{ }
	TestResult( const TestResult& other )	= default;

	TestResult operator+( const TestResult& other ) {
		Failed += other.Failed;
		Run += other.Run;
		Skipped += other.Skipped;

		return *this;
	}

	int Failed;
	int Run;
	int Skipped;
};


class GenericTest
{
public:
	enum TestResult_e {
		Failed = 0,
		Passed,
		Skipped
	};

public:
	explicit GenericTest( std::string name )
	: mLastResult( Failed ),
	  mName( std::move( name ) )
	{ }
	virtual ~GenericTest() = default;

	virtual void process() = 0;
	virtual void setup() = 0;
	virtual void teardown() = 0;

public:
	const std::string& getName() const {
		return mName;
	}

	void print() const {
		std::cout << getName() << std::endl;
	}

	TestResult run() {
		setup();
		process();
		teardown();

		printResults();

		return mResult;
	}

protected:
	TestResult_e mLastResult;
	std::string mName;

	TestResult mResult;

private:
	void printResults() const {
		std::cout << "Statistics: " << getName() << " " << (mResult.Run - mResult.Failed - mResult.Skipped) << " passed, " << mResult.Skipped << " skipped, " << mResult.Failed << " failed" << std::endl;
	}
};

}

#endif
