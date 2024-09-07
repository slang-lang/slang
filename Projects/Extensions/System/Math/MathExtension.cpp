
// Header
#include "MathExtension.h"

// Library includes

// Project includes
#include "Abs.h"
#include "Ceil.h"
#include "Exp.h"
#include "Floor.h"
#include "Round.h"
#include "Sqrt.h"
#include "Trunc.h"

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
	methods.push_back( new CeilDouble() );
	methods.push_back( new CeilFloat() );
	methods.push_back( new ExpDouble() );
	methods.push_back( new ExpFloat() );
	methods.push_back( new FloorDouble() );
	methods.push_back( new FloorFloat() );
	methods.push_back( new RoundDouble() );
	methods.push_back( new RoundFloat() );
	methods.push_back( new SqrtDouble() );
	methods.push_back( new SqrtFloat() );
	methods.push_back( new TruncDouble() );
	methods.push_back( new TruncFloat() );

}


}
}
}
}
