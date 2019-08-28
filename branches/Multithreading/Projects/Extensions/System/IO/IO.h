
#ifndef ObjectiveScript_Extensions_System_IO_IO_h
#define ObjectiveScript_Extensions_System_IO_IO_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace IO {


class SystemIOExtension : public AExtension
{
public:
	SystemIOExtension();
	~SystemIOExtension();

public:
	void initialize(IScope* scope);
	void provideMethods(ExtensionMethods &methods);
};


}
}
}
}


#endif
