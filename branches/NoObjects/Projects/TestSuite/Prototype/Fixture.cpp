
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "PrototypeTest.h"

// Namespace declarations


namespace Testing {
namespace Prototype {


Fixture::Fixture(const Utils::Common::Logger *p)
: TestFixture("PrototypeTestFixture"),
  Utils::Common::Logger(p, "PrototypeTestFixture")
{
}

void Fixture::setup()
{
	PrototypeTest* prototypeTest = new PrototypeTest(this);
	add(prototypeTest);
}

void Fixture::teardown()
{
}


}
}
