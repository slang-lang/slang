
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "UtilsTest.h"

// Namespace declarations


namespace Testing {
namespace UtilsTest {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "Utils", std::move( libraries ) )
, Utils::Common::Logger( p, "Utils" )
{
}

void Fixture::setup()
{
	add( new UtilsTest( this ) );
}

void Fixture::teardown()
{
}


}
}
