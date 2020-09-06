
#ifndef Slang_Extensions_System_Console_Console_h
#define Slang_Extensions_System_Console_Console_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Console {


class SystemConsoleExtension : public AExtension
{
public:
	SystemConsoleExtension();
	~SystemConsoleExtension() = default;

public:
	void initialize( IScope* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}
}

#endif
