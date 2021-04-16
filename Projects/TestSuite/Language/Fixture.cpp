
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "LanguageTest.h"

// Namespace declarations


namespace Testing {
namespace Language {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "Language", std::move( libraries ) )
, Utils::Common::Logger( p, "Language" )
{
}

void Fixture::setup()
{
	add( new LanguageTest( this ) );
}

void Fixture::teardown()
{
}


}
}
