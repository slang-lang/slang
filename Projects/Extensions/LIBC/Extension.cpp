
// Header
#include "Extension.h"

// Library includes

// Project includes
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include "locale/setlocale.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {


Extension::Extension()
: AExtension( "LIBC", "0.2.0" )
{
}

void Extension::initialize( ExtensionNamespace* scope )
{
#ifdef _WIN32
    // Win32 only

    (void)scope;
#else
    // Unix/Linux only

    scope->define( "LC_ALL",      new Runtime::Int32Type( "LC_ALL", LC_ALL ) );
    scope->define( "LC_COLLATE",  new Runtime::Int32Type( "LC_COLLATE", LC_COLLATE ) );
    scope->define( "LC_CTYPE",    new Runtime::Int32Type( "LC_CTYPE", LC_CTYPE ) );
    scope->define( "LC_MONETARY", new Runtime::Int32Type( "LC_MONETARY", LC_MONETARY ) );
    scope->define( "LC_NUMERIC",  new Runtime::Int32Type( "LC_NUMERIC", LC_NUMERIC ) );
    scope->define( "LC_TIME",     new Runtime::Int32Type( "LC_TIME", LC_TIME ) );
#endif

#ifdef _WIN32
    // Win32 only
#else
    // Unix/Linux only

    // mCassert.initialize( scope );
    mCstring.initialize( scope );
    mFenv.initialize( scope );
    mMath.initialize( scope );
    mStdio.initialize( scope );
    mStdlib.initialize( scope );
#endif
}

void Extension::provideMethods( ExtensionMethods& methods )
{
    assert( methods.empty() );

    // locale
    methods.push_back( new locale::SETLOCALE() );

#ifdef _WIN32
    // Win32 only
#else
    // Unix/Linux only

    // mCassert.provideMethods( methods );
    mCstring.provideMethods( methods );
    mFenv.provideMethods( methods );
    mMath.provideMethods( methods );
    mStdio.provideMethods( methods );
    mStdlib.provideMethods( methods );
#endif
}


}
}
}
