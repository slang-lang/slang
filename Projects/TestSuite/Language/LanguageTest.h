
#ifndef Testing_Language_LanguageTest_h
#define Testing_Language_LanguageTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>
#include <Tools/Printer.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Language {


class LanguageTest : private Utils::Common::Logger,
					 public GenericTest
{
public:
	LanguageTest(const Utils::Common::Logger *p);
	virtual ~LanguageTest() { }

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testAssert();
	void testBooleanOperators();
	void testComment();
	void testConstCorrectness();
	void testConstCorrectness2();
	void testDefaultParameter();
	void testFinal();
	void testForLoop();
	void testIf();
	void testInterfaces();
	void testMethodOverloading();
	void testNamespaces();
	void testObjectReference();
	void testParameters();
	void testPrint();
	void testStaticLocalVariable();
	void testWhile();

private:
	Utils::Printer mStdoutPrinter;
};


}
}


#endif
