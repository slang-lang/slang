
#ifndef Slang_Extensions_LIBC_stdlib_stdlib_hpp
#define Slang_Extensions_LIBC_stdlib_stdlib_hpp


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdlib {


class stdlib_t : public AExtension
{
public:
	stdlib_t();
	~stdlib_t() = default;

public:
	void initialize( ExtensionNamespace* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}
}


#endif
