
// Header
#include "SystemExtension.h"

// Library includes
#include <cerrno>

// Project includes
#include "AssertMsg.h"
#include "GetChar.h"
#include "GetEnv.h"
#include "SetKeyboardBlockingMode.h"
#include "Sleep.h"
#include "StdTime.h"
#include "System.h"
#include "Write.h"
#include "WriteLn.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


SystemExtension::SystemExtension()
: AExtension("System")
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

void SystemExtension::initialize(IScope* scope)
{
	// error constants
	scope->define("EACCES", new Runtime::IntegerObject(EACCES));
	scope->define("EINVAL", new Runtime::IntegerObject(EINVAL));
	scope->define("EMFILE", new Runtime::IntegerObject(EMFILE));
	scope->define("ENFILE", new Runtime::IntegerObject(ENFILE));
	scope->define("ENOMEM", new Runtime::IntegerObject(ENOMEM));

#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
	scope->define("EAFNOSUPPORT", new Runtime::IntegerObject(EAFNOSUPPORT));
	scope->define("ENOBUFS", new Runtime::IntegerObject(ENOBUFS));
	scope->define("EPROTONOSUPPORT", new Runtime::IntegerObject(EPROTONOSUPPORT));
#endif

	// Console
	mConsoleExtension.initialize(scope);

	// IO
	mIOExtension.initialize(scope);

	// Math
	mMathExtension.initialize(scope);

	// Network
#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
	mNetworkExtension.initialize(scope);
#endif

	// Strings
	mStringsExtension.initialize(scope);
}

void SystemExtension::provideMethods(ExtensionMethods &methods)
{
	assert(methods.empty());

	// Generic methods
	methods.push_back(new Assert());
	methods.push_back(new GetChar());
	methods.push_back(new GetEnv());
	methods.push_back(new Sleep());
	methods.push_back(new StdTime());
	methods.push_back(new Write());
	methods.push_back(new WriteLn());

#ifdef _WIN32
	// Win32 only methods
#else
	// Unix/Linux only methods
	methods.push_back(new SetKeyboardBlockingMode());
#endif

	// Console
	mConsoleExtension.provideMethods(methods);

	// IO
	mIOExtension.provideMethods(methods);

	// Math
	mMathExtension.provideMethods(methods);

	// Network
#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
	mNetworkExtension.provideMethods(methods);
#endif

	// Strings
	mStringsExtension.provideMethods(methods);
}


}
}
}
