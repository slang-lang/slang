
// Header
#include "Fixture.h"

// Library includes

// Project includes
#include "ASTTest.h"

// Namespace declarations


namespace Testing {
namespace AST {


Fixture::Fixture( const Utils::Common::ILogger *p, StringSet libraries )
: TestFixture( "AST", std::move( libraries ) )
, Utils::Common::Logger( p, "ASTFixture" )
{
}

void Fixture::setup()
{
	add( new ASTTest( this ) );
}

void Fixture::teardown()
{
}


}
}
