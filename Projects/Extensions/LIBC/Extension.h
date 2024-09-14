
#ifndef Slang_Extensions_LIBC_Extension_h
#define Slang_Extensions_LIBC_Extension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>
#include "fenv/fenv.hpp"
#include "math/math.hpp"
#include "stdio/stdio.hpp"
#include "stdlib/stdlib.hpp"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {


class Extension : public AExtension
{
public:
    Extension();
    ~Extension() = default;

public:
    void initialize( ExtensionNamespace* scope );
    void provideMethods( ExtensionMethods& methods );

private:
    LIBC::fenv::fenv_t     mFenv;
    LIBC::math::math_t     mMath;
    LIBC::stdio::stdio_t   mStdio;
    LIBC::stdlib::stdlib_t mStdlib;
};


}
}
}


#endif
