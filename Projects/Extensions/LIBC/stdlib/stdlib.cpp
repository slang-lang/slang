
// Header
#include "stdlib.hpp"

// Library includes

// Project includes
#include "abs.h"
#include "rand.h"
#include "srand.h"


// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionLIBC {
namespace stdlib {


stdlib_t::stdlib_t()
: AExtension( "stdlib", "0.0.1" )
{
}

void stdlib_t::initialize( ExtensionNamespace* scope )
{
	// constants
	scope->define( "RAND_MAX", new Runtime::IntegerObject( "RAND_MAX", RAND_MAX ) );
}

void stdlib_t::provideMethods( ExtensionMethods& methods )
{
    methods.push_back( new ABS() );
    methods.push_back( new RAND() );
    methods.push_back( new SRAND() );
}


}
}
}
}
