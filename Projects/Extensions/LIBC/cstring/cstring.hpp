
#ifndef Slang_Extensions_LIBC_cstring_cstring_hpp
#define Slang_Extensions_LIBC_cstring_cstring_hpp


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cstring {


class cstring_t : public AExtension
{
public:
    cstring_t();
    ~cstring_t() = default;

public:
    void initialize( ExtensionNamespace* scope );
    void provideMethods( ExtensionMethods& methods );
};


}
}
}
}


#endif
