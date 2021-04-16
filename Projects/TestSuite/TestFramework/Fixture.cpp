
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "TestFrameworkTest.h"

// Namespace declarations


namespace Testing {
namespace Framework {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "Testing", std::move( libraries ) )
, Utils::Common::Logger( p, "TestFramework" )
{
}

void Fixture::setup()
{
	add( new TestFrameworkTest( this ) );
}

void Fixture::teardown()
{
}


}
}
