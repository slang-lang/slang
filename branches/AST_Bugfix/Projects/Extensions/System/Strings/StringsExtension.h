
#ifndef ObjectiveScript_Extensions_System_Strings_StringsExtension_h
#define ObjectiveScript_Extensions_System_Strings_StringsExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Strings {


class SystemStringsExtension : public AExtension
{
public:
	SystemStringsExtension();
	~SystemStringsExtension();

public:
	void provideMethods(ExtensionMethods &methods);
};


}
}
}
}

#endif
