
// Header
#include "math.hpp"

// Library includes

// Project includes
#include "abs.h"
#include "fdim.h"
#include "fma.h"
#include "fmax.h"
#include "fmin.h"
#include "fmod.h"
#include "nan.h"
#include "remainder.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionLIBC {
namespace math {


math_t::math_t()
: AExtension( "math", "0.0.1" )
{
}

void math_t::initialize( ExtensionNamespace* scope )
{
    (void)scope;

	// constants
	//scope->define( "RAND_MAX", new Runtime::IntegerObject( "RAND_MAX", RAND_MAX ) );
}

void math_t::provideMethods( ExtensionMethods& methods )
{
    methods.push_back( new FABS() );
    methods.push_back( new FABSF() );
    methods.push_back( new FDIM() );
    methods.push_back( new FDIMF() );
    methods.push_back( new FMA() );
    methods.push_back( new FMAF() );
    methods.push_back( new FMAX() );
    methods.push_back( new FMAXF() );
    methods.push_back( new FMIN() );
    methods.push_back( new FMINF() );
    methods.push_back( new FMOD() );
    methods.push_back( new FMODF() );
    methods.push_back( new MathNAN() );
    methods.push_back( new MathNANF() );
    methods.push_back( new REMAINDER() );
    methods.push_back( new REMAINDERF() );
}


}
}
}
}
