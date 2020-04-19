
#ifndef ObjectiveScript_Extensions_System_Reflection_ReflectionExtension_h
#define ObjectiveScript_Extensions_System_Reflection_ReflectionExtension_h


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
	~SystemReflectionExtension();

public:
	void initialize(IScope* scope);
	void provideMethods(ExtensionMethods &methods);
};


}
}
}
}

#endif
