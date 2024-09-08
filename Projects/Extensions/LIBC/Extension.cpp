
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

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {


Extension::Extension()
: AExtension( "LIBC", "0.0.2" )
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

	mFenv.initialize( scope );
	mMath.initialize( scope );
	mStdio.initialize( scope );
	mStdlib.initialize( scope );
#endif
}

void Extension::provideMethods( ExtensionMethods& methods )
{
	assert( methods.empty() );

	// cassert
	//methods.push_back( new CASSERT() );

	// cstring
	methods.push_back( new cstring::STRCAT() );
	methods.push_back( new cstring::STRCHR() );
	methods.push_back( new cstring::STRCMP() );
	methods.push_back( new cstring::STRCOLL() );
	methods.push_back( new cstring::STRCSPN() );
	methods.push_back( new cstring::STRLEN() );
	methods.push_back( new cstring::STRNCAT() );
	methods.push_back( new cstring::STRNCMP() );
	methods.push_back( new cstring::STRPBRK() );
	methods.push_back( new cstring::STRSPN() );
	methods.push_back( new cstring::STRRCHR() );
	methods.push_back( new cstring::STRSTR() );

	// locale
	methods.push_back( new locale::SETLOCALE() );

#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only

	mFenv.provideMethods( methods );
	mMath.provideMethods( methods );
	mStdio.provideMethods( methods );
	mStdlib.provideMethods( methods );
#endif
}


}
}
}
