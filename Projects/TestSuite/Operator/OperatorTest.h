
#ifndef Testing_Operator_OperatorTest_h
#define Testing_Operator_OperatorTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/UnitTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Operator {


class OperatorTest : public UnitTest,
					 private Utils::Common::Logger
{
public:
	explicit OperatorTest( const Utils::Common::ILogger* p );
	~OperatorTest() = default;

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testBooleanOperator();
	void testBooleanOverloads_Assign();
	void testBooleanOverloads_BitAnd();
	void testBooleanOverloads_BitOr();
	void testBooleanOverloads_Equal();
	void testBooleanOverloads_Greater();
	void testBooleanOverloads_Greater_Equal();
	void testBooleanOverloads_Less();
	void testBooleanOverloads_Less_Equal();
	void testBooleanOverloads_Unequal();
	void testEnumeration();
	void testIndexOperator();
	void testInverseOperator();
	void testIsOperator();
	void testMathOverloadsWithNumbers();
	void testMathOverloadsWithObjects();
	void testRangeOperator();
	void testShiftOperator();
	void testUnaryMinus();
	void testUnaryPlus();
	void testUnaryValidate();
};


}
}


#endif
