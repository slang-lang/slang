
#ifndef Slang_Extensions_LIBC_math_math_hpp
#define Slang_Extensions_LIBC_math_math_hpp


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


class math_t : public AExtension
{
public:
	math_t();
	~math_t() = default;

public:
	void initialize( ExtensionNamespace* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}
}


#endif
