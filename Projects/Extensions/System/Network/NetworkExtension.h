
#ifndef Slang_Extensions_System_Network_NetworkExtension_h
#define Slang_Extensions_System_Network_NetworkExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Network {


class SystemNetworkExtension : public AExtension
{
public:
	SystemNetworkExtension();
	~SystemNetworkExtension();

public:
	void initialize(IScope* scope);
	void provideMethods(ExtensionMethods &methods);
};


}
}
}
}

#endif
