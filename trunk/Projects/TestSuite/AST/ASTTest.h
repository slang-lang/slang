
#ifndef Testing_AST_ASTTest_h
#define Testing_AST_ASTTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace AST {


class ASTTest : public GenericTest,
				private Utils::Common::Logger
{
public:
	ASTTest(const Utils::Common::ILogger *p);
	~ASTTest();

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testAssert();
	void testAssignment();
	void testBreak();
	void testContinue();
	void testExit();
	void testExpression();
	void testFor();
	void testForeach();
	void testGenerator();
	void testIf();
	void testNamespace();
	void testNew();
	void testReturn();
	void testSwitch();
	void testThrow();
	void testTry();
	void testTypeDeclaration();
	void testTypeSystem();
	void testUnaryExpression();
	void testWhile();
};


}
}


#endif