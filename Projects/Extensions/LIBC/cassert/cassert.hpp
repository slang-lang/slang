
#ifndef Slang_Extensions_LIBC_cassert_cassert_hpp
#define Slang_Extensions_LIBC_cassert_cassert_hpp


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cassert {


class cassert_t : public AExtension
{
public:
    cassert_t();
    ~cassert_t() = default;

public:
    void initialize( ExtensionNamespace* scope );
    void provideMethods( ExtensionMethods& methods );
};


}
}
}
}


#endif
