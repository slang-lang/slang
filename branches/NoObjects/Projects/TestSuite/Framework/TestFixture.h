
#ifndef _Framework_TestFixture_h_
#define _Framework_TestFixture_h_


// Library includes
#include <list>
#include <typeinfo>

// Project includes
#include "GenericTest.h"
#include <Common/Logger.h>

// Forward declarations

// Namespace declarations


//#define NO_TYPEID


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

	void run() {
#ifdef NO_TYPEID
		std::cout << std::endl << "********* Starting:  *********" << std::endl;
#else
		std::cout << std::endl << "********* Starting: " << typeid(*this).name() << " *********" << std::endl;
#endif

		setup();

		for ( TestList::const_iterator it = mTests.begin(); it!= mTests.end(); it++ ) {
			(*it)->run();
		}

		teardown();
		cleanup();

#ifndef NO_TYPEID
		std::cout << "********* Finished:  *********" << std::endl;
#else
		std::cout << "********* Finished: " << typeid(*this).name() << " *********" << std::endl;
#endif
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
	std::string	mName;
	TestList	mTests;
};


}


#endif
