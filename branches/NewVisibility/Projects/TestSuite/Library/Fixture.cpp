
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "LibraryTest.h"

// Namespace declarations


namespace Testing {
namespace Library {


Fixture::Fixture(const Utils::Common::ILogger *p)
: TestFixture("Library"),
  Utils::Common::Logger(p, "Library")
{
}

Fixture::~Fixture()
{
}

void Fixture::setup()
{
	LibraryTest* libraryTest = new LibraryTest(this);
	add(libraryTest);
}

void Fixture::teardown()
{
}


}
}
