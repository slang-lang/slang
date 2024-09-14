
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "InterfacesTest.h"

// Namespace declarations


namespace Testing {
namespace Interfaces {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "Interfaces", std::move( libraries ) )
, Utils::Common::Logger( p, "Interfaces" )
{
}

void Fixture::setup()
{
    add( new InterfacesTest( this ) );
}

void Fixture::teardown()
{
}


}
}
