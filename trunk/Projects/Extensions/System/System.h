
#ifndef ObjectiveScript_Extensions_System_System_h
#define ObjectiveScript_Extensions_System_System_h


// Library includes

// Project includes
#include <Core/Interfaces/IExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class System : public IExtension
{
public:
	std::string getName() const {
		return "System";
	}

	void provideMethods(ExtensionMethods &methods);
};


}
}

#endif
