
// Header
#include "TimeExtension.h"

// Library includes

// Project includes
#include "StdTime.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Time {


SystemTimeExtension::SystemTimeExtension()
: AExtension( "Time", "0.0.1" )
{
}

void SystemTimeExtension::initialize( IScope* /*scope*/ )
{
#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
#endif
}

void SystemTimeExtension::provideMethods( ExtensionMethods& methods )
{
    methods.push_back( new StdTime() );
}


}
}
}
}
