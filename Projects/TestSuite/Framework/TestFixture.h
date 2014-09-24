
#ifndef _Testing_TestFixture_h_
#define _Testing_TestFixture_h_


// Library includes
#include <list>
#include <typeinfo>

// Project includes
#include "GenericTest.h"
#include <Common/Logger.h>

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
	virtual ~TestFixture() { }

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

	void run() {
		std::cout << std::endl << "********* Starting: " << typeid(*this).name() << " *********" << std::endl;

		setup();

		for ( TestList::const_iterator it = mTests.begin(); it!= mTests.end(); it++ ) {
			(*it)->run();
		}

		teardown();
		cleanup();

		std::cout << "********* Finished: " << typeid(*this).name() << " *********" << std::endl;
	}

protected:

private:
	void cleanup() {
		for ( TestList::iterator it = mTests.begin(); it != mTests.end(); ++it ) {
			delete (*it);
		}
		mTests.clear();
	}

private:
	std::string	mName;
	TestList	mTests;
};


}


#endif _Testing_TestFixture_h_
