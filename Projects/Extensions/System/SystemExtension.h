
#ifndef ObjectiveScript_Extensions_System_SystemExtension_h
#define ObjectiveScript_Extensions_System_SystemExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>
#include <System/Console/Console.h>
#include <System/IO/IO.h>
#include <System/Math/MathExtension.h>
#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
#	include <System/Network/NetworkExtension.h>
#endif
#include <System/Reflection/ReflectionExtension.h>
#include <System/Strings/StringsExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class SystemExtension : public AExtension
{
public:
	SystemExtension();
	~SystemExtension();

public:
	void initialize(IScope* scope);
	void provideMethods(ExtensionMethods &methods);

private:
	Console::SystemConsoleExtension mConsoleExtension;
	IO::SystemIOExtension mIOExtension;
	Math::SystemMathExtension mMathExtension;
#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
	Network::SystemNetworkExtension mNetworkExtension;
#endif
	Reflection::SystemReflectionExtension mReflectionExtension;
	Strings::SystemStringsExtension mStringsExtension;
};


}
}
}


#endif
