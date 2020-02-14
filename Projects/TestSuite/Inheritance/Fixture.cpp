
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "InheritanceTest.h"

// Namespace declarations


namespace Testing {
namespace Inheritance {


Fixture::Fixture(const Utils::Common::ILogger *p)
: TestFixture("Inheritance"),
  Utils::Common::FileLogger(p, "Inheritance")
{
}

Fixture::~Fixture()
{
}

void Fixture::setup()
{
    InheritanceTest* inheritanceTest = new InheritanceTest(this);
    add(inheritanceTest);
}

void Fixture::teardown()
{
}


}
}
