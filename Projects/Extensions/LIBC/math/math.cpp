
// Header
#include "math.hpp"

// Library includes

// Project includes
#include "abs.h"
#include "cbrt.h"
#include "exp.h"
#include "exp2.h"
#include "expm1.h"
#include "fdim.h"
#include "fma.h"
#include "fmax.h"
#include "fmin.h"
#include "fmod.h"
#include "hypot.h"
#include "log.h"
#include "log10.h"
#include "log1p.h"
#include "log2.h"
#include "nan.h"
#include "pow.h"
#include "remainder.h"
#include "sqrt.h"

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
    methods.push_back( new CBRT() );
    methods.push_back( new CBRTF() );
    methods.push_back( new EXP() );
    methods.push_back( new EXPF() );
    methods.push_back( new EXP2() );
    methods.push_back( new EXP2F() );
    methods.push_back( new EXPM1() );
    methods.push_back( new EXPM1F() );
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
    methods.push_back( new HYPOT() );
    methods.push_back( new HYPOTF() );
    methods.push_back( new LOG() );
    methods.push_back( new LOGF() );
    methods.push_back( new LOG10() );
    methods.push_back( new LOG10F() );
    methods.push_back( new LOG1P() );
    methods.push_back( new LOG1PF() );
    methods.push_back( new LOG2() );
    methods.push_back( new LOG2F() );
    methods.push_back( new MathNAN() );
    methods.push_back( new MathNANF() );
    methods.push_back( new POW() );
    methods.push_back( new POWF() );
    methods.push_back( new REMAINDER() );
    methods.push_back( new REMAINDERF() );
    methods.push_back( new SQRT() );
    methods.push_back( new SQRTF() );
}


}
}
}
}
