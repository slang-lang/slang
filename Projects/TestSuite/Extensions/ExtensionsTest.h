
#ifndef Testing_Extensions_ExtensionsTest_h
#define Testing_Extensions_ExtensionsTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Extensions {


class ExtensionsTest : public GenericTest,
				 private Utils::Common::FileLogger
{
public:
	ExtensionsTest(const Utils::Common::ILogger *p);
	virtual ~ExtensionsTest() { }

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
/*
	void testBasicExpressionParsing();
	void testDataTypeBool();
	void testDataTypeDouble();
	void testDataTypeFloat();
	void testDataTypeInt();
	void testSimpleExtensions();
	void testUnaryMinus();
*/
};


}
}


#endif