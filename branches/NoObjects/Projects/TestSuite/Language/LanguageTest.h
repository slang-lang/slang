
#ifndef Testing_Language_LanguageTest_h
#define Testing_Language_LanguageTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>
#include <Utils/Printer.h>

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
	void testComment();
	void testFor();
	void testIf();
	void testPrint();
	void testStaticLocalVariable();
	void testWhile();

	void testConstCorrectness();
	void testInterfaces();

private:
	::Utils::Printer mStdoutPrinter;
};


}
}


#endif
