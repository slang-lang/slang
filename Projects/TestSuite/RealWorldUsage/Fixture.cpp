
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "RealWorldUsageTest.h"

// Namespace declarations


namespace Testing {
namespace RealWorldUsage {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "RealWorldUsage", std::move( libraries ) )
, Utils::Common::Logger( p, "RealWorldUsage" )
{
}

void Fixture::setup()
{
	add( new RealWorldUsageTest( this ) );
}

void Fixture::teardown()
{
}


}
}
