
#ifndef Slang_Extensions_System_IO_IO_h
#define Slang_Extensions_System_IO_IO_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace IO {


class SystemIOExtension : public AExtension
{
public:
	SystemIOExtension();
	~SystemIOExtension() = default;

public:
	void initialize( ExtensionNamespace* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}
}


#endif
