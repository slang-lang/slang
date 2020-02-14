
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "InterfacesTest.h"

// Namespace declarations


namespace Testing {
namespace Interfaces {


Fixture::Fixture(const Utils::Common::ILogger *p)
: TestFixture("Interfaces"),
  Utils::Common::FileLogger(p, "Interfaces")
{
}

Fixture::~Fixture()
{
}

void Fixture::setup()
{
    InterfacesTest* interfacesTest = new InterfacesTest(this);
    add(interfacesTest);
}

void Fixture::teardown()
{
}


}
}
