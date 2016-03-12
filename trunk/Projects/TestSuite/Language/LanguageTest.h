
#ifndef Testing_Language_LanguageTest_h
#define Testing_Language_LanguageTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Language {


class LanguageTest : private Utils::Common::Logger,
					 public GenericTest
{
public:
	LanguageTest(const Utils::Common::ILogger *p);
	virtual ~LanguageTest() { }

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testAssert();
	void testBooleanOperators();
	void testComment();
	void testConstCorrectness1();
	void testConstCorrectness2();
	void testConstCorrectness3();
	void testDefaultParameter();
	void testException();
	void testFinal();
	void testFor();
	void testIf();
	void testInfixOperator();
	void testLawOfDemeter();
	void testMethodOverloading();
	void testNamespaces();
	void testObjectEquality();
	void testObjectReference();
	void testParameters();
	void testPostfixOperator();
	void testPrint();
	void testSanityChecker();
	void testScope();
	void testStaticLocalVariable();
	void testSwitch();
	void testThis();
	void testTypeCast();
	void testWhile();
};


}
}


#endif
