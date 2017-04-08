
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "LanguageTest.h"

// Namespace declarations


namespace Testing {
namespace Language {


Fixture::Fixture(const Utils::Common::ILogger *p)
: TestFixture("Language"),
  Utils::Common::Logger(p, "Language")
{
}

Fixture::~Fixture()
{
}

void Fixture::setup()
{
	LanguageTest* languageTest = new LanguageTest(this);
	add(languageTest);
}

void Fixture::teardown()
{
}


}
}
