
// Header
#include "StringsExtension.h"

// Library includes

// Project includes
#include "StrFind.h"
#include "StrLen.h"
#include "StrLPad.h"
#include "StrLTrim.h"
#include "StrPos.h"
#include "StrRPad.h"
#include "StrRTrim.h"
#include "StrTrim.h"
#include "SubStr.h"
#include "ToLower.h"
#include "ToUpper.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


SystemStringsExtension::SystemStringsExtension()
: AExtension( "Strings", "0.0.1" )
{
}

void SystemStringsExtension::initialize( IScope* scope )
{
#ifdef _WIN32
	// Win32 only

	{	// LINEBREAK (system specific)
		std::ostringstream character;
		character << '\r' << '\n';

		scope->define( "LINEBREAK", new Runtime::StringObject( character.str() ) );
	}
#else
	// Unix/Linux only

	{	// LINEBREAK (system specific)
		std::ostringstream character;
		character << '\n';

		scope->define( "LINEBREAK", new Runtime::StringObject( character.str() ) );
	}
#endif

	{	// NUL
		std::ostringstream character;
		character << '\0';

		scope->define( "NUL", new Runtime::StringObject( character.str() ) );
	}
	{	// LINEBREAK_DOS (system specific)
		std::ostringstream character;
		character << '\r' << '\n';

		scope->define( "LINEBREAK_DOS", new Runtime::StringObject( character.str() ) );
	}
	{	// LINEBREAK_UNIX (system specific)
		std::ostringstream character;
		character << '\n';

		scope->define( "LINEBREAK_UNIX", new Runtime::StringObject( character.str() ) );
	}
	{	// TABULATOR
		std::ostringstream character;
		character << '\t';

		scope->define( "TABULATOR", new Runtime::StringObject( character.str() ) );
	}
}

void SystemStringsExtension::provideMethods( ExtensionMethods& methods )
{
	methods.push_back( new StrFind() );
	methods.push_back( new StrLen() );
	methods.push_back( new StrLPad() );
	methods.push_back( new StrLTrim() );
	methods.push_back( new StrPos() );
	methods.push_back( new StrRPad() );
	methods.push_back( new StrRTrim() );
	methods.push_back( new StrTrim() );
	methods.push_back( new SubStr() );
	methods.push_back( new ToLower() );
	methods.push_back( new ToUpper() );
}


}
}
}
}
