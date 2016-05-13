
#ifndef ObjectiveScript_Extensions_System_SystemExtension_h
#define ObjectiveScript_Extensions_System_SystemExtension_h


// Library includes

// Project includes
#include <Core/Interfaces/IExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


class SystemExtension : public IExtension
{
public:
	std::string getName() const {
		return "System";
	}

	void provideMethods(ExtensionMethods &methods);
};


}
}
}


#endif
