
// Header
#include "Extension.h"

// Library includes
#include <cerrno>

// Project includes
#include "cassert/cassert.h"
#include "cstring/strcat.h"
#include "cstring/strchr.h"
#include "cstring/strcmp.h"
#include "cstring/strcoll.h"
#include "cstring/strcspn.h"
#include "cstring/strlen.h"
#include "cstring/strncat.h"
#include "cstring/strncmp.h"
#include "cstring/strpbrk.h"
#include "cstring/strspn.h"
#include "cstring/strrchr.h"
#include "cstring/strstr.h"
#include "locale/setlocale.h"
#include "stdio/stdio.hpp"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionsLIBC {


Extension::Extension()
: AExtension( "LIBC", "0.0.2" )
{
}

Extension::~Extension()
{
}

void Extension::initialize( ExtensionNamespace* scope )
{
#ifdef _WIN32
	// Win32 only

	(void)scope;
#else
	// Unix/Linux only

	scope->define( "LC_ALL",      new Runtime::IntegerObject( "LC_ALL", LC_ALL ) );
	scope->define( "LC_COLLATE",  new Runtime::IntegerObject( "LC_COLLATE", LC_COLLATE ) );
	scope->define( "LC_CTYPE",    new Runtime::IntegerObject( "LC_CTYPE", LC_CTYPE ) );
	scope->define( "LC_MONETARY", new Runtime::IntegerObject( "LC_MONETARY", LC_MONETARY ) );
	scope->define( "LC_NUMERIC",  new Runtime::IntegerObject( "LC_NUMERIC", LC_NUMERIC ) );
	scope->define( "LC_TIME",     new Runtime::IntegerObject( "LC_TIME", LC_TIME ) );
#endif

#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only

	mSTDIOExtension.initialize( scope );
#endif
}

void Extension::provideMethods( ExtensionMethods& methods )
{
	assert( methods.empty() );

	// cassert
	//methods.push_back( new CASSERT() );

	// cstring
	methods.push_back( new STRCAT() );
	methods.push_back( new STRCHR() );
	methods.push_back( new STRCMP() );
	methods.push_back( new STRCOLL() );
	methods.push_back( new STRCSPN() );
	methods.push_back( new STRLEN() );
	methods.push_back( new STRNCAT() );
	methods.push_back( new STRNCMP() );
	methods.push_back( new STRPBRK() );
	methods.push_back( new STRSPN() );
	methods.push_back( new STRRCHR() );
	methods.push_back( new STRSTR() );

	// locale
	methods.push_back( new SETLOCALE() );

#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only

	mSTDIOExtension.provideMethods( methods );
#endif
}


}
}
}
