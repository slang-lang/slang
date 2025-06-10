
// Header
#include "cassert.hpp"

// Library includes

// Project includes
#include "cassert.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cassert {


cassert_t::cassert_t()
: AExtension( "cassert", "0.0.1" )
{
}

void cassert_t::initialize( ExtensionNamespace* scope )
{
    (void)scope;
}

void cassert_t::provideMethods( ExtensionMethods& methods )
{
    methods.push_back( new CASSERT() );
}


}
}
}
}
