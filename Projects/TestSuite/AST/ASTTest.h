
#ifndef Testing_AST_ASTTest_h
#define Testing_AST_ASTTest_h


// Library includes

// Project includes
#include <Logger/Logger.h>
#include <Framework/UnitTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace AST {


class ASTTest : public UnitTest,
				private Utils::Common::Logger
{
public:
	explicit ASTTest( const Utils::Common::ILogger* p );
	~ASTTest() = default;

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testAssert();
	void testAssignment();
	void testBase();
	void testBreak();
	void testContinue();
	void testConstCorrectness1();
	void testConstCorrectness2();
	void testConstCorrectness3();
	void testConstCorrectness4();
	void testConstCorrectness5();
	void testExit();
	void testExpression();
	void testFor();
	void testForeach();
	void testGenerator();
	void testIf();
	void testNamespace();
	void testNew();
	void testReturn();
	void testScopeOperator();
	void testSwitch();
	void testTernaryOperator();
	void testTernaryOperatorFail();
	void testThis();
	void testThrow();
	void testTry();
	void testTypecast();
	void testTypecastExpression();
	void testTypeDeclaration();
	void testTypeInference();
	void testTypeSystem();
	void testUnaryExpression();
	void testWhile();
};


}
}


#endif
