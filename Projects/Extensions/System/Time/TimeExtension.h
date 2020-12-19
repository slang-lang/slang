
#ifndef Slang_Extensions_System_Time_TimeExtension_h
#define Slang_Extensions_System_Time_TimeExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Time {


class SystemTimeExtension : public AExtension
{
public:
    SystemTimeExtension();
	~SystemTimeExtension() = default;

public:
	void initialize( IScope* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}
}

#endif
