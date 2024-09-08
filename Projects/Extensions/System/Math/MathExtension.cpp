
// Header
#include "MathExtension.h"

// Library includes

// Project includes
#include "Abs.h"
#include "Sqrt.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Math {


SystemMathExtension::SystemMathExtension()
: AExtension( "Math", "0.0.2" )
{
}

void SystemMathExtension::initialize( ExtensionNamespace* /*scope*/ )
{
	// nothing to do here
}

void SystemMathExtension::provideMethods( ExtensionMethods& methods )
{
	methods.push_back( new AbsDouble() );
	methods.push_back( new AbsFloat() );
	methods.push_back( new SqrtDouble() );
	methods.push_back( new SqrtFloat() );

}


}
}
}
}
