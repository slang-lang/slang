
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "OperatorTest.h"

// Namespace declarations


namespace Testing {
namespace Operator {


Fixture::Fixture(const Utils::Common::ILogger *p)
: TestFixture("Operator"),
  Utils::Common::FileLogger(p, "Operator")
{
}

Fixture::~Fixture()
{
}

void Fixture::setup()
{
	OperatorTest* operatorTest = new OperatorTest(this);
	add(operatorTest);
}

void Fixture::teardown()
{
}


}
}
