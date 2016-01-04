
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
	void testFinal();
	void testFor();
	void testIf();
	void testInterfaces();
	void testMethodOverloading();
	void testNamespaces();
	void testObjectReference();
	void testParameters();
	void testPrint();
	void testScope();
	void testStaticLocalVariable();
	void testSwitch();
	void testWhile();
};


}
}


#endif
