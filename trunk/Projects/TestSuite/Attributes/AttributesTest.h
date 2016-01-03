
#ifndef Testing_Attributes_AttributesTest_h
#define Testing_Attributes_AttributesTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Attributes {


class AttributesTest : private Utils::Common::Logger,
					   public GenericTest
{
public:
	AttributesTest(const Utils::Common::ILogger *p);
	~AttributesTest();

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testBasicLanguageFeatures();
};


}
}


#endif
