
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "ExtensionsTest.h"

// Namespace declarations


namespace Testing {
namespace Extensions {


Fixture::Fixture( const Utils::Common::ILogger* p )
: TestFixture( "Extensions" ),
  Utils::Common::Logger( p, "Extensions" )
{
}

void Fixture::setup()
{
	ExtensionsTest* mathTest = new ExtensionsTest(this);
	add(mathTest);
}

void Fixture::teardown()
{
}


}
}
