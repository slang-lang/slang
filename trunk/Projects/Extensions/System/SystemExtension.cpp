
// Header
#include "SystemExtension.h"

// Library includes

// Project includes
#include <System/Console/Cerr.h>
#include <System/Console/Cin.h>
#include <System/Console/Cout.h>
#include <System/Console/Endl.h>
#include <System/Math/Abs.h>
#include <System/Math/Ceil.h>
#include <System/Math/Floor.h>
#include <System/Math/Rand.h>
#include <System/Math/Round.h>
#include <System/Math/Sqrt.h>
#include <System/Math/Srand.h>
#include <System/Math/Trunc.h>
#include <System/IO/FileClose.h>
#include <System/IO/FileOpen.h>
#include <System/IO/FileRead.h>
#include <System/IO/FileSeek.h>
#include <System/IO/FileWrite.h>
#include <System/Strings/StrFind.h>
#include <System/Strings/StrLen.h>
#include <System/Strings/StrLTrim.h>
#include <System/Strings/StrRTrim.h>
#include <System/Strings/StrTrim.h>
#include <System/Strings/SubStr.h>
#include <System/Strings/ToLower.h>
#include <System/Strings/ToUpper.h>
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
#else
	// store keyboard blocking mode
	storeKeyboardBlockingMode();
#endif
}

SystemExtension::~SystemExtension()
{
#ifdef _WIN32
#else
	// not restoring the keyboard settings causes the input from the terminal to not work right
	restoreKeyboardBlockingMode();
#endif
}

void SystemExtension::provideMethods(ExtensionMethods &methods)
{
	assert(methods.empty());

	// Generic methods
	methods.push_back(new AssertMsg());
	methods.push_back(new GetChar());
	methods.push_back(new GetEnv());
	methods.push_back(new Sleep());
	methods.push_back(new StdTime());
	methods.push_back(new Write());
	methods.push_back(new WriteLn());

	methods.push_back(new Console::Cerr());
	methods.push_back(new Console::Cin());
	methods.push_back(new Console::Cout());
	methods.push_back(new Console::Endl());

	methods.push_back(new Math::AbsDouble());
	methods.push_back(new Math::AbsFloat());
	methods.push_back(new Math::CeilDouble());
	methods.push_back(new Math::CeilFloat());
	methods.push_back(new Math::FloorDouble());
	methods.push_back(new Math::FloorFloat());
	methods.push_back(new Math::Rand());
	methods.push_back(new Math::RoundDouble());
	methods.push_back(new Math::RoundFloat());
	methods.push_back(new Math::SqrtDouble());
	methods.push_back(new Math::SqrtFloat());
	methods.push_back(new Math::Srand());
	methods.push_back(new Math::TruncDouble());
	methods.push_back(new Math::TruncFloat());

	methods.push_back(new IO::FileClose());
	methods.push_back(new IO::FileOpen());
	methods.push_back(new IO::FileReadBool());
	methods.push_back(new IO::FileReadDouble());
	methods.push_back(new IO::FileReadFloat());
	methods.push_back(new IO::FileReadInt());
	methods.push_back(new IO::FileReadString());
	methods.push_back(new IO::FileSeek());
	methods.push_back(new IO::FileWriteBool());
	methods.push_back(new IO::FileWriteDouble());
	methods.push_back(new IO::FileWriteFloat());
	methods.push_back(new IO::FileWriteInt());
	methods.push_back(new IO::FileWriteString());

	methods.push_back(new Strings::StrFind());
	methods.push_back(new Strings::StrLen());
	methods.push_back(new Strings::StrLTrim());
	methods.push_back(new Strings::StrRTrim());
	methods.push_back(new Strings::StrTrim());
	methods.push_back(new Strings::SubStr());
	methods.push_back(new Strings::ToLower());
	methods.push_back(new Strings::ToUpper());

	
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
