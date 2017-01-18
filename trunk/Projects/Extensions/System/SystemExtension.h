
#ifndef ObjectiveScript_Extensions_System_SystemExtension_h
#define ObjectiveScript_Extensions_System_SystemExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>
#include <System/Console/Console.h>
#include <System/IO/IO.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


class SystemExtension : public AExtension
{
public:
	SystemExtension();
	~SystemExtension();

public:
	void provideMethods(ExtensionMethods &methods);

private:
	Console::SystemConsoleExtension mConsoleExtension;
	IO::SystemIOExtension mIOExtension;
};


}
}
}


#endif
