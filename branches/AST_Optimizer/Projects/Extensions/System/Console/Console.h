
#ifndef ObjectiveScript_Extensions_System_Console_Console_h
#define ObjectiveScript_Extensions_System_Console_Console_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Console {


class SystemConsoleExtension : public AExtension
{
public:
	SystemConsoleExtension();
	~SystemConsoleExtension();

public:
	void provideMethods(ExtensionMethods &methods);
};


}
}
}
}

#endif
