
#ifndef Testing_Library_LibraryTest_h
#define Testing_Library_LibraryTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Library {


class LibraryTest : public GenericTest,
				 	private Utils::Common::Logger
{
public:
	LibraryTest(const Utils::Common::ILogger *p);

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testBoolean();
	void testDouble();
	void testFloat();
	void testInteger();
	void testString();
};


}
}


#endif
