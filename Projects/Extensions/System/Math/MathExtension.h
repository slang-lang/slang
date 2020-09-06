
#ifndef Slang_Extensions_System_Math_MathExtension_h
#define Slang_Extensions_System_Math_MathExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Math {


class SystemMathExtension : public AExtension
{
public:
	SystemMathExtension();
	~SystemMathExtension() = default;

public:
	void initialize( IScope* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}
}

#endif
