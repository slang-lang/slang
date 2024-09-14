
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "MathTest.h"

// Namespace declarations


namespace Testing {
namespace Math {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "Math", std::move( libraries ) )
, Utils::Common::Logger( p, "Math" )
{
}

void Fixture::setup()
{
	add( new MathTest( this ) );
}

void Fixture::teardown()
{
}


}
}
