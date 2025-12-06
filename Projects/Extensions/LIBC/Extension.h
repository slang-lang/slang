
#ifndef Slang_Extensions_LIBC_Extension_h
#define Slang_Extensions_LIBC_Extension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>
//#include "cassert/cassert.hpp"
#include "cstring/cstring.hpp"
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
    ~Extension() override = default;

public:
    void initialize( ExtensionNamespace* scope ) override;
    void provideMethods( ExtensionMethods& methods ) override;

private:
    //cassert::cassert_t mCassert;
    cstring::cstring_t mCstring;
    fenv::fenv_t       mFenv;
    math::math_t       mMath;
    stdio::stdio_t     mStdio;
    stdlib::stdlib_t   mStdlib;
};


}
}
}


#endif
