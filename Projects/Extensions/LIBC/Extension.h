
#ifndef Slang_Extensions_LIBC_Extension_h
#define Slang_Extensions_LIBC_Extension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionsLIBC {


class Extension : public AExtension
{
public:
	Extension();
	~Extension();

public:
	void initialize( ExtensionNamespace* scope );
	void provideMethods( ExtensionMethods& methods );

private:
//	ExtensionLIBC::CASSERT mCASSERTExtension;
//	ExtensionLIBC::CERRNO mCERRNOExtension;
};


}
}
}


#endif
