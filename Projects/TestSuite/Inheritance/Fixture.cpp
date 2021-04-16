
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "InheritanceTest.h"

// Namespace declarations


namespace Testing {
namespace Inheritance {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "Inheritance", std::move( libraries ) )
, Utils::Common::Logger( p, "Inheritance" )
{
}

void Fixture::setup()
{
    add( new InheritanceTest( this ) );
}

void Fixture::teardown()
{
}


}
}
