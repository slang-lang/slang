
// Header
#include "math.hpp"

// Library includes
#include <math.h>

// Project includes
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>
#include "abs.h"
#include "acos.h"
#include "acosh.h"
#include "asin.h"
#include "asinh.h"
#include "atan.h"
#include "atanh.h"
#include "atan2.h"
#include "cbrt.h"
#include "ceil.h"
#include "copysign.h"
#include "cos.h"
#include "cosh.h"
#include "erf.h"
#include "erfc.h"
#include "exp.h"
#include "exp2.h"
#include "expm1.h"
#include "fdim.h"
#include "floor.h"
#include "fma.h"
#include "fmax.h"
#include "fmin.h"
#include "fmod.h"
#include "hypot.h"
#include "ilogb.h"
#include "ldexp.h"
#include "lgamma.h"
#include "log.h"
#include "log10.h"
#include "log1p.h"
#include "log2.h"
#include "logb.h"
#include "nan.h"
#include "nearbyint.h"
#include "nextafter.h"
#include "nexttoward.h"
#include "pow.h"
#include "remainder.h"
#include "rint.h"
#include "round.h"
#include "scalbn.h"
#include "sin.h"
#include "sinh.h"
#include "sqrt.h"
#include "tan.h"
#include "tanh.h"
#include "tgamma.h"
#include "trunc.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


math_t::math_t()
: AExtension( "math", "0.1.0" )
{
}

void math_t::initialize( ExtensionNamespace* scope )
{
    // constants
    scope->define( "FP_NORMAL",    new Runtime::FloatType(  "FP_NORMAL",    FP_NORMAL ) );
    scope->define( "FP_SUBNORMAL", new Runtime::FloatType(  "FP_SUBNORMAL", FP_SUBNORMAL ) );
    scope->define( "FP_ZERO",      new Runtime::FloatType(  "FP_ZERO",      FP_ZERO ) );
    scope->define( "FP_INFINITE",  new Runtime::FloatType(  "FP_INFINITE",  FP_INFINITE ) );
    scope->define( "FP_NAN",       new Runtime::FloatType(  "FP_NAN",       FP_NAN ) );

    //scope->define( "FP_FAST_FMA",  new Runtime::DoubleType( "FP_FAST_FMA",  FP_FAST_FMA ) );
    //scope->define( "FP_FAST_FMAF", new Runtime::FloatType(  "FP_FAST_FMAF", FP_FAST_FMAF ) );

    scope->define( "HUGE_VAL",     new Runtime::DoubleType( "HUGE_VAL",     HUGE_VAL ) );
    scope->define( "HUGE_VALF",    new Runtime::FloatType(  "HUGE_VALF",    HUGE_VALF ) );
    //scope->define( "HUGE_VALL",    new Runtime::Int64Type(  "HUGE_VALL",    HUGE_VALL ) );

    scope->define( "INFINITY",     new Runtime::DoubleType( "INFINITY",     INFINITY ) );
    scope->define( "NAN",          new Runtime::DoubleType( "NAN",          NAN ) );
}

void math_t::provideMethods( ExtensionMethods& methods )
{
    methods.push_back( new ABS() );
    methods.push_back( new ACOS() );
    methods.push_back( new ACOSF() );
    methods.push_back( new ACOSH() );
    methods.push_back( new ACOSHF() );
    methods.push_back( new ASIN() );
    methods.push_back( new ASINF() );
    methods.push_back( new ASINH() );
    methods.push_back( new ASINHF() );
    methods.push_back( new ATAN() );
    methods.push_back( new ATANF() );
    methods.push_back( new ATANH() );
    methods.push_back( new ATANHF() );
    methods.push_back( new ATAN2() );
    methods.push_back( new ATAN2F() );
    methods.push_back( new CBRT() );
    methods.push_back( new CBRTF() );
    methods.push_back( new CEIL() );
    methods.push_back( new CEILF() );
    methods.push_back( new COPYSIGN() );
    methods.push_back( new COPYSIGNF() );
    methods.push_back( new COS() );
    methods.push_back( new COSF() );
    methods.push_back( new COSH() );
    methods.push_back( new COSHF() );
    methods.push_back( new ERF() );
    methods.push_back( new ERFF() );
    methods.push_back( new ERFC() );
    methods.push_back( new ERFCF() );
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
    methods.push_back( new FLOOR() );
    methods.push_back( new FLOORF() );
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
    methods.push_back( new ILOGB() );
    methods.push_back( new ILOGBF() );
    methods.push_back( new LABS() );
    methods.push_back( new LDEXP() );
    methods.push_back( new LDEXPF() );
    methods.push_back( new LGAMMA() );
    methods.push_back( new LGAMMAF() );
    methods.push_back( new LOG() );
    methods.push_back( new LOGF() );
    methods.push_back( new LOG10() );
    methods.push_back( new LOG10F() );
    methods.push_back( new LOG1P() );
    methods.push_back( new LOG1PF() );
    methods.push_back( new LOG2() );
    methods.push_back( new LOG2F() );
    methods.push_back( new LOGB() );
    methods.push_back( new LOGBF() );
    methods.push_back( new MathNAN() );
    methods.push_back( new MathNANF() );
    methods.push_back( new NEARBYINT() );
    methods.push_back( new NEARBYINTF() );
    methods.push_back( new NEXTAFTER() );
    methods.push_back( new NEXTAFTERF() );
    methods.push_back( new NEXTTOWARD() );
    methods.push_back( new NEXTTOWARDF() );
    methods.push_back( new POW() );
    methods.push_back( new POWF() );
    methods.push_back( new POWL() );
    methods.push_back( new REMAINDERF() );
    methods.push_back( new RINT() );
    methods.push_back( new RINTF() );
    methods.push_back( new ROUND() );
    methods.push_back( new ROUNDF() );
    methods.push_back( new SCALBN() );
    methods.push_back( new SCALBNF() );
    methods.push_back( new SIN() );
    methods.push_back( new SINF() );
    methods.push_back( new SINH() );
    methods.push_back( new SINHF() );
    methods.push_back( new SQRTDouble() );
    methods.push_back( new SQRTF() );
    methods.push_back( new SQRTFloat() );
    methods.push_back( new TAN() );
    methods.push_back( new TANF() );
    methods.push_back( new TANH() );
    methods.push_back( new TANHF() );
    methods.push_back( new TGAMMA() );
    methods.push_back( new TGAMMAF() );
    methods.push_back( new TRUNC() );
    methods.push_back( new TRUNCF() );
}


}
}
}
}

