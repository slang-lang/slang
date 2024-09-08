
// Header
#include "SystemExtension.h"

// Library includes
#include <cerrno>

// Project includes
#include <Defines.h>
#include "Ascii.h"
#include "Fork.h"
#include "GetEnv.h"
#include "PutEnv.h"
#include "SetEnv.h"
#include "SetKeyboardBlockingMode.h"
#include "Sleep.h"
#include "System.h"
#include "Wait.h"
#include "WaitPID.h"
#include "Write.h"
#include "WriteLn.h"

#ifdef _WIN32
	// Win32 only methods
#else
	// Unix/Linux only
#	include "Fork.h"
#endif

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


SystemExtension::SystemExtension()
: AExtension( "Slang System", "0.1.3" )
{
#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
	// store keyboard blocking mode
	storeKeyboardBlockingMode();
#endif
}

SystemExtension::~SystemExtension()
{
#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
	// not restoring the keyboard settings causes the input from the terminal to not work right
	restoreKeyboardBlockingMode();
#endif
}

void SystemExtension::initialize( ExtensionNamespace* scope )
{
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

	// Console
	mConsoleExtension.initialize( scope );

	// Network
#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
	mNetworkExtension.initialize( scope );
#endif

	// Strings
	mStringsExtension.initialize( scope );

	// Time
	mTimeExtension.initialize( scope );
}

void SystemExtension::provideMethods( ExtensionMethods& methods )
{
	assert( methods.empty() );

	// Generic methods
	methods.push_back( new Ascii() );
	methods.push_back( new GetEnv() );
	methods.push_back( new PutEnv() );
	methods.push_back( new SetEnv() );
	methods.push_back( new Sleep() );
	methods.push_back( new SystemExecute() );
	methods.push_back( new Write() );
	methods.push_back( new WriteLn() );

#ifdef _WIN32
	// Win32 only methods
#else
	// Unix/Linux only methods
	methods.push_back( new Fork() );
	methods.push_back( new SetKeyboardBlockingMode() );
	methods.push_back( new Wait() );
	methods.push_back( new WaitPID() );
#endif

	// Console
	mConsoleExtension.provideMethods( methods );

	// Network
#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
	mNetworkExtension.provideMethods( methods );
#endif

	// Reflection
	mReflectionExtension.provideMethods( methods );

	// Strings
	mStringsExtension.provideMethods( methods );

	// Time
	mTimeExtension.provideMethods( methods );
}


}
}
}
