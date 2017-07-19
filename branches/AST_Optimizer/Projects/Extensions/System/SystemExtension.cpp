
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
	scope->define("EAFNOSUPPORT", new Runtime::IntegerObject(EAFNOSUPPORT));
	scope->define("EINVAL", new Runtime::IntegerObject(EINVAL));
	scope->define("EMFILE", new Runtime::IntegerObject(EMFILE));
	scope->define("ENFILE", new Runtime::IntegerObject(ENFILE));
	scope->define("ENOBUFS", new Runtime::IntegerObject(ENOBUFS));
	scope->define("ENOMEM", new Runtime::IntegerObject(ENOMEM));
	scope->define("EPROTONOSUPPORT", new Runtime::IntegerObject(EPROTONOSUPPORT));

	// Console
	mConsoleExtension.initialize(scope);
	// IO
	mIOExtension.initialize(scope);
	// Math
	mMathExtension.initialize(scope);
	// Network
	mNetworkExtension.initialize(scope);
	// Strings
	mStringsExtension.initialize(scope);

#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
#endif
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

	// Console
	mConsoleExtension.provideMethods(methods);

	// IO
	mIOExtension.provideMethods(methods);

	// Math
	mMathExtension.provideMethods(methods);

	// Network
	mNetworkExtension.provideMethods(methods);

	// Strings
	mStringsExtension.provideMethods(methods);

	
#ifdef _WIN32
	// Win32 only methods
#else
	// Unix/Linux only methods
	methods.push_back(new SetKeyboardBlockingMode());
#endif
}


}
}
}
