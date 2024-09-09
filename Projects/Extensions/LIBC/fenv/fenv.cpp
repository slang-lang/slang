
// Header
#include "fenv.hpp"

// Library includes
#include <fenv.h>

// Project includes
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include "feclearexcept.h"
#include "fegetround.h"
#include "feraiseexcept.h"
#include "fesetround.h"
#include "fetestexcept.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace fenv {


fenv_t::fenv_t()
: AExtension( "fenv", "0.0.1" )
{
}

void fenv_t::initialize( ExtensionNamespace* scope )
{
    // constants
    scope->define( "FE_DIVBYZERO", new Runtime::IntegerObject( "FE_DIVBYZERO", FE_DIVBYZERO ) );
    scope->define( "FE_INEXACT", new Runtime::IntegerObject( "FE_INEXACT", FE_INEXACT ) );
    scope->define( "FE_INVALID", new Runtime::IntegerObject( "FE_INVALID", FE_INVALID ) );
    scope->define( "FE_OVERFLOW", new Runtime::IntegerObject( "FE_OVERFLOW", FE_OVERFLOW ) );
    scope->define( "FE_UNDERFLOW", new Runtime::IntegerObject( "FE_UNDERFLOW", FE_UNDERFLOW ) );
    scope->define( "FE_ALL_EXCEPT", new Runtime::IntegerObject( "FE_ALL_EXCEPT", FE_ALL_EXCEPT ) );

    scope->define( "FE_DOWNWARD",   new Runtime::IntegerObject( "FE_DOWNWARD",   FE_DOWNWARD ) );
    scope->define( "FE_TONEAREST",  new Runtime::IntegerObject( "FE_TONEAREST",  FE_TONEAREST ) );
    scope->define( "FE_TOWARDZERO", new Runtime::IntegerObject( "FE_TOWARDZERO", FE_TOWARDZERO ) );
    scope->define( "FE_UPWARD",     new Runtime::IntegerObject( "FE_UPWARD",     FE_UPWARD ) );
}

void fenv_t::provideMethods( ExtensionMethods& methods )
{
    methods.push_back( new FECLEAREXCEPT() );
    methods.push_back( new FEGETROUND() );
    methods.push_back( new FERAISEEXCEPT() );
    methods.push_back( new FESETROUND() );
    methods.push_back( new FETESTEXCEPT() );
}


}
}
}
}
