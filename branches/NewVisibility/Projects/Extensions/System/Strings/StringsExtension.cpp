
// Header
#include "StringsExtension.h"

// Library includes

// Project includes
#include "StrFind.h"
#include "StrLen.h"
#include "StrLPad.h"
#include "StrLTrim.h"
#include "StrRPad.h"
#include "StrRTrim.h"
#include "StrTrim.h"
#include "SubStr.h"
#include "ToLower.h"
#include "ToUpper.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Strings {


SystemStringsExtension::SystemStringsExtension()
: AExtension("Strings")
{
}

SystemStringsExtension::~SystemStringsExtension()
{
}

void SystemStringsExtension::provideMethods(ExtensionMethods &methods)
{
	methods.push_back(new StrFind());
	methods.push_back(new StrLen());
	methods.push_back(new StrLPad());
	methods.push_back(new StrLTrim());
	methods.push_back(new StrRPad());
	methods.push_back(new StrRTrim());
	methods.push_back(new StrTrim());
	methods.push_back(new SubStr());
	methods.push_back(new ToLower());
	methods.push_back(new ToUpper());
}


}
}
}
}
