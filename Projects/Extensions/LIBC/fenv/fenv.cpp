
// Header
#include "fenv.hpp"

// Library includes
#include <fenv.h>

// Project includes
#include <Core/Runtime/BuildInTypes/Int32Type.h>
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
    scope->define( "FE_DIVBYZERO", new Runtime::Int32Type( "FE_DIVBYZERO", FE_DIVBYZERO ) );
    scope->define( "FE_INEXACT", new Runtime::Int32Type( "FE_INEXACT", FE_INEXACT ) );
    scope->define( "FE_INVALID", new Runtime::Int32Type( "FE_INVALID", FE_INVALID ) );
    scope->define( "FE_OVERFLOW", new Runtime::Int32Type( "FE_OVERFLOW", FE_OVERFLOW ) );
    scope->define( "FE_UNDERFLOW", new Runtime::Int32Type( "FE_UNDERFLOW", FE_UNDERFLOW ) );
    scope->define( "FE_ALL_EXCEPT", new Runtime::Int32Type( "FE_ALL_EXCEPT", FE_ALL_EXCEPT ) );

    scope->define( "FE_DOWNWARD",   new Runtime::Int32Type( "FE_DOWNWARD",   FE_DOWNWARD ) );
    scope->define( "FE_TONEAREST",  new Runtime::Int32Type( "FE_TONEAREST",  FE_TONEAREST ) );
    scope->define( "FE_TOWARDZERO", new Runtime::Int32Type( "FE_TOWARDZERO", FE_TOWARDZERO ) );
    scope->define( "FE_UPWARD",     new Runtime::Int32Type( "FE_UPWARD",     FE_UPWARD ) );
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
