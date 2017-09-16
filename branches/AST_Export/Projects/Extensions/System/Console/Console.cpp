
// Header
#include "Console.h"

// Library includes

// Project includes
#include <System/Console/Cerr.h>
#include <System/Console/Cin.h>
#include <System/Console/Cout.h>
#include <System/Console/Endl.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Console {


SystemConsoleExtension::SystemConsoleExtension()
: AExtension("Console")
{
}

SystemConsoleExtension::~SystemConsoleExtension()
{
}

void SystemConsoleExtension::provideMethods(ExtensionMethods &methods)
{
	methods.push_back(new Cerr());
	methods.push_back(new Cin());
	methods.push_back(new Cout());
	methods.push_back(new Endl());
}


}
}
}
}
