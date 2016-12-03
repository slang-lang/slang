
#ifndef _Framework_TestFixture_h_
#define _Framework_TestFixture_h_


// Library includes
#include <list>
#include <typeinfo>

// Project includes
#include <Common/Logger.h>
#include "GenericTest.h"

// Forward declarations

// Namespace declarations


namespace Testing {


class TestFixture
{
public:
	typedef std::list<GenericTest*> TestList;

public:
	TestFixture(const std::string& name)
	: mName(name)
	{ }
	virtual ~TestFixture() {
		cleanup();
	}

public:
	virtual void setup() = 0;
	virtual void teardown() = 0;

public:
	void add(GenericTest *t) {
		mTests.push_back(t);
	}

	const std::string& getName() const {
		return mName;
	}

	void print() {
		std::cout << "TestSuite: " << getName() << std::endl;

		for ( TestList::const_iterator it = mTests.begin(); it!= mTests.end(); it++ ) {
			(*it)->print();
		}
	}

	TestResult run() {
		TestResult result;

		std::cout << std::endl << "********* Starting: " << getName() << " *********" << std::endl;

		setup();

		for ( TestList::const_iterator it = mTests.begin(); it!= mTests.end(); it++ ) {
			result = result + (*it)->run();
		}

		teardown();
		cleanup();

		std::cout << "********* Finished: " << getName() << " *********" << std::endl;

		return result;
	}

protected:

private:
	void cleanup() {
		for ( TestList::iterator it = mTests.begin(); it != mTests.end(); ++it ) {
			delete (*it);
			(*it) = 0;
		}
		mTests.clear();
	}

private:
	std::string mName;
	TestList mTests;
};


}


#endif
