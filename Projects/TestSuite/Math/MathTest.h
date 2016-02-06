
#ifndef Testing_Math_MathTest_h
#define Testing_Math_MathTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Math {


class MathTest : private Utils::Common::Logger,
				 public GenericTest
{
public:
	MathTest(const Utils::Common::ILogger *p);
	virtual ~MathTest() { }

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testBasicExpressionParsing();
	void testDataTypeBool();
	void testDataTypeFloat();
	void testDataTypeInt();
};


}
}


#endif
