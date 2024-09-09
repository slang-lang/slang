
#ifndef Testing_Math_MathTest_h
#define Testing_Math_MathTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/UnitTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Math {


class MathTest : public UnitTest,
				 private Utils::Common::Logger
{
public:
	explicit MathTest( const Utils::Common::ILogger* p );
	~MathTest() = default;

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testBasicExpressionParsing();
	void testDataTypeBool();
	void testDataTypeDouble();
	void testDataTypeFloat();
	void testDataTypeInt();
	void testSimpleMath();
	void testUnaryMinus();
};


}
}


#endif
