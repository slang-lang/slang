
#ifndef Testing_Extensions_ExtensionsTest_h
#define Testing_Extensions_ExtensionsTest_h


// Library includes

// Project includes
#include <Logger/Logger.h>
#include <Framework/UnitTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Extensions {


class ExtensionsTest : public UnitTest,
				 	   private Utils::Common::Logger
{
public:
	explicit ExtensionsTest( const Utils::Common::ILogger* p );
	~ExtensionsTest() = default;

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
