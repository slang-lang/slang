
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "LibraryTest.h"

// Namespace declarations


namespace Testing {
namespace Library {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "Library", std::move( libraries ) )
, Utils::Common::Logger( p, "Library" )
{
}

void Fixture::setup()
{
	add( new LibraryTest( this ) );
}

void Fixture::teardown()
{
}


}
}
