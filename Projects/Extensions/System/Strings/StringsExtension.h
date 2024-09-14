
#ifndef Slang_Extensions_System_Strings_StringsExtension_h
#define Slang_Extensions_System_Strings_StringsExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class SystemStringsExtension : public AExtension
{
public:
	SystemStringsExtension();
	~SystemStringsExtension() = default;

public:
	void initialize( ExtensionNamespace* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}
}

#endif
