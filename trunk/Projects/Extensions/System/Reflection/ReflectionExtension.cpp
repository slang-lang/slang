
// Header
#include "ReflectionExtension.h"

// Library includes

// Project includes
#include "CreateInstance.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Reflection {


SystemReflectionExtension::SystemReflectionExtension()
: AExtension("Reflection")
{
}

SystemReflectionExtension::~SystemReflectionExtension()
{
}

void SystemReflectionExtension::initialize(IScope* scope)
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
}


}
}
}
}
