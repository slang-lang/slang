
#ifndef Testing_Operator_OperatorTest_h
#define Testing_Operator_OperatorTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>
#include <Tools/Printer.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Operator {


class OperatorTest : private Utils::Common::Logger,
					 public GenericTest
{
public:
	OperatorTest(const Utils::Common::Logger *p);
	virtual ~OperatorTest() { }

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testBooleanOverloads_Assign();
	void testBooleanOverloads_BitAnd();
	void testBooleanOverloads_BitOr();
	void testBooleanOverloads_Equal();
	void testBooleanOverloads_Greater();
	void testBooleanOverloads_Greater_Equal();
	void testBooleanOverloads_Less();
	void testBooleanOverloads_Less_Equal();
	void testBooleanOverloads_Unequal();
	void testMathOverloadsWithNumbers();
	void testMathOverloadsWithObjects();

private:
	Utils::Printer mStdoutPrinter;
};


}
}


#endif
