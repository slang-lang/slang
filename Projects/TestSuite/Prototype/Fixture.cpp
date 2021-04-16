
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "PrototypeTest.h"

// Namespace declarations


namespace Testing {
namespace Prototype {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "Prototype", std::move( libraries ) )
, Utils::Common::Logger( p, "Prototype" )
{
}

void Fixture::setup()
{
	add( new PrototypeTest( this ) );
}

void Fixture::teardown()
{
}


}
}
