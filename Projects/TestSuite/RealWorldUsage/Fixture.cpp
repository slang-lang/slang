
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "RealWorldUsageTest.h"

// Namespace declarations


namespace Testing {
namespace RealWorldUsage {


Fixture::Fixture( const Utils::Common::ILogger* p )
: TestFixture( "RealWorldUsage" ),
  Utils::Common::Logger( p, "RealWorldUsage" )
{
}

void Fixture::setup()
{
	RealWorldUsageTest* mathTest = new RealWorldUsageTest(this);
	add(mathTest);
}

void Fixture::teardown()
{
}


}
}
