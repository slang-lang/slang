
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "ExtensionsTest.h"

// Namespace declarations


namespace Testing {
namespace Extensions {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "Extensions", std::move( libraries ) )
, Utils::Common::Logger( p, "Extensions" )
{
}

void Fixture::setup()
{
	add( new ExtensionsTest( this ) );
}

void Fixture::teardown()
{
}


}
}
