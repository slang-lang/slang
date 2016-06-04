
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "MathTest.h"

// Namespace declarations


namespace Testing {
namespace Math {


Fixture::Fixture(const Utils::Common::ILogger *p)
: TestFixture("Math"),
  Utils::Common::Logger(p, "Math")
{
}

Fixture::~Fixture()
{
}

void Fixture::setup()
{
	MathTest* mathTest = new MathTest(this);
	add(mathTest);
}

void Fixture::teardown()
{
}


}
}
