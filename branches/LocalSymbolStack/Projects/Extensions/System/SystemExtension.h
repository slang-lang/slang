
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
#include <System/Strings/StringsExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
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
	Strings::SystemStringsExtension mStringsExtension;
};


}
}
}


#endif