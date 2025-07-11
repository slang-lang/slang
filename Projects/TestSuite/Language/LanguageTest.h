
#ifndef Testing_Language_LanguageTest_h
#define Testing_Language_LanguageTest_h


// Library includes

// Project includes
#include <Logger/Logger.h>
#include <Framework/UnitTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Language {


class LanguageTest : public UnitTest,
					 private Utils::Common::Logger
{
public:
	explicit LanguageTest( const Utils::Common::ILogger* p );
	~LanguageTest() = default;

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void GlobalVariableTest();

	void testAbstractObject();
	void testAssert();
	void testAssignment();
	void testAttributes();
	void testAtomicReference();
	void testBooleanOperators();
	void testComment();
	void testConstCorrectness1();
	void testConstCorrectness2();
	void testConstCorrectness3();
	void testConstCorrectness4();
	void testCopy();
	void testDefaultParameter();
	void testEnum();
	void testException();
	void testFor();
	void testForeach();
	void testIf();
	void testIncompleteBooleanEvaluation();
	void testInfixOperator();
	void testMethodOverloading();
	void testNamespaces();
	void testObjectEquality();
	void testObjectReference();
	void testParameters();
	void testPostfixOperator();
	void testPrint();
	void testSanityChecker();
	void testScope();
	void testStaticMethod();
	void testSwitch();
	void testThis();
	void testThrow();
	void testTypeCast();
	void testTypeInference();
	void testWhile();
};


}
}


#endif
