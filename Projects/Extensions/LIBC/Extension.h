
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
namespace ExtensionsLIBC {


class Extension : public AExtension
{
public:
	Extension();
	~Extension() = default;

public:
	void initialize( ExtensionNamespace* scope );
	void provideMethods( ExtensionMethods& methods );

private:
    ExtensionLIBC::fenv::fenv_t     mFenv;
    ExtensionLIBC::math::math_t     mMath;
    ExtensionLIBC::stdio::stdio_t   mStdio;
    ExtensionLIBC::stdlib::stdlib_t mStdlib;
};


}
}
}


#endif
