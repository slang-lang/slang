
#ifndef Slang_Extensions_System_Reflection_ReflectionExtension_h
#define Slang_Extensions_System_Reflection_ReflectionExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Reflection {


class SystemReflectionExtension : public AExtension
{
public:
	SystemReflectionExtension();
	~SystemReflectionExtension() = default;

public:
	void initialize( ExtensionNamespace* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}
}

#endif
