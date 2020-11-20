
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "ASTTest.h"

// Namespace declarations


namespace Testing {
namespace AST {


Fixture::Fixture(const Utils::Common::ILogger *p)
: TestFixture("AST"),
  Utils::Common::Logger(p, "ASTFixture")
{
}

Fixture::~Fixture()
{
}

void Fixture::setup()
{
	ASTTest* astTest = new ASTTest(this);
	add(astTest);
}

void Fixture::teardown()
{
}


}
}
