
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "AttributesTest.h"

// Namespace declarations


namespace Testing {
namespace Attributes {


Fixture::Fixture(const Utils::Common::Logger *p)
: TestFixture("AttributesTestFixture"),
  Utils::Common::Logger(p, "AttributesTestFixture")
{
}

Fixture::~Fixture()
{
}

void Fixture::setup()
{
	AttributesTest* attributesTest = new AttributesTest(this);
	add(attributesTest);
}

void Fixture::teardown()
{
}


}
}
