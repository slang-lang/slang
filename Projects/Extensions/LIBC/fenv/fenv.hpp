
#ifndef Slang_Extensions_LIBC_fenv_fenv_hpp
#define Slang_Extensions_LIBC_fenv_fenv_hpp


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionLIBC {
namespace fenv {


class fenv_t : public AExtension
{
public:
	fenv_t();
	~fenv_t() = default;

public:
	void initialize( ExtensionNamespace* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}
}


#endif
