
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "OperatorTest.h"

// Namespace declarations


namespace Testing {
namespace Operator {


Fixture::Fixture( const Utils::Common::ILogger* p, StringSet libraries )
: TestFixture( "Operator", std::move( libraries ) )
, Utils::Common::Logger( p, "Operator" )
{
}

void Fixture::setup()
{
	add( new OperatorTest( this ) );
}

void Fixture::teardown()
{
}


}
}
