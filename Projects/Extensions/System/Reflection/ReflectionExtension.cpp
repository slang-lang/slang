
// Header
#include "ReflectionExtension.h"

// Library includes

// Project includes
#include "CreateInstance.h"
#include "IsKnownType.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Reflection {


SystemReflectionExtension::SystemReflectionExtension()
: AExtension("Reflection")
{
}

void SystemReflectionExtension::initialize(IScope* /*scope*/)
{
#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
#endif
}

void SystemReflectionExtension::provideMethods(ExtensionMethods &methods)
{
	methods.push_back(new CreateInstance());
	methods.push_back(new IsKnownType());
}


}
}
}
}
