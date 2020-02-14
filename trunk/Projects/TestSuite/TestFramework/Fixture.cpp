
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "TestFrameworkTest.h"

// Namespace declarations


namespace Testing {
namespace Framework {


Fixture::Fixture(const Utils::Common::ILogger *p)
: TestFixture("Testing"),
  Utils::Common::FileLogger(p, "TestFramework")
{
}

Fixture::~Fixture()
{
}

void Fixture::setup()
{
	TestFrameworkTest* frameworkTest = new TestFrameworkTest(this);
	add(frameworkTest);
}

void Fixture::teardown()
{
}


}
}
