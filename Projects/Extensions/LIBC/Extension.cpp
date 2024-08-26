
// Header
#include "Extension.h"

// Library includes
#include <cerrno>

// Project includes
#include <Defines.h>
#include "cassert/cassert.h"
#include "cstring/strcat.h"
#include "cstring/strlen.h"
#include "cstring/strncat.h"
#include "cstring/strncmp.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionsLIBC {


Extension::Extension()
: AExtension( "LIBC", "0.0.1" )
{
}

Extension::~Extension()
{
}

void Extension::initialize( ExtensionNamespace* /*scope*/ )
{
/*
	// error constants
	scope->define( "EACCES", new Runtime::IntegerObject( "EACCES", EACCES ) );
	scope->define( "EINVAL", new Runtime::IntegerObject( "EINVAL", EINVAL ) );
	scope->define( "EMFILE", new Runtime::IntegerObject( "EMFILE", EMFILE ) );
	scope->define( "ENFILE", new Runtime::IntegerObject( "ENFILE", ENFILE ) );
	scope->define( "ENOMEM", new Runtime::IntegerObject( "ENOMEM", ENOMEM ) );

#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only

	scope->define( "WNOHANG", new Runtime::IntegerObject( "WNOHANG", WNOHANG ) );
	scope->define( "WUNTRACED", new Runtime::IntegerObject( "WUNTRACED", WUNTRACED ) );
#endif
*/
}

void Extension::provideMethods( ExtensionMethods& methods )
{
	assert( methods.empty() );

	// cassert
	methods.push_back( new CASSERT() );

	// cstring
	methods.push_back( new STRCAT() );
	methods.push_back( new STRLEN() );
	methods.push_back( new STRNCAT() );
	methods.push_back( new STRNCMP() );
}


}
}
}
