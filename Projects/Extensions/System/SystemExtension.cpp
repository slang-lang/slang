
// Header
#include "SystemExtension.h"

// Library includes

// Project includes
#include <System/Console/Cerr.h>
#include <System/Console/Cin.h>
#include <System/Console/Cout.h>
#include <System/Console/Endl.h>
#include <System/IO/FileClose.h>
#include <System/IO/FileOpen.h>
#include <System/IO/FileRead.h>
#include <System/IO/FileSeek.h>
#include <System/IO/FileWrite.h>
#include <System/Strings/StrFind.h>
#include <System/Strings/StrLen.h>
#include <System/Strings/SubStr.h>
#include <System/Strings/ToLower.h>
#include <System/Strings/ToUpper.h>
#include "AssertMsg.h"
#include "GetEnv.h"
//#include "Print.h"
#include "Sleep.h"
#include "Write.h"
#include "WriteLn.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


void SystemExtension::provideMethods(ExtensionMethods &methods)
{
	assert(methods.empty());

	methods.push_back(new AssertMsg());
	methods.push_back(new GetEnv());
	//methods.push_back(new Printf());
	methods.push_back(new Sleep());
	methods.push_back(new Write());
	methods.push_back(new WriteLn());

	methods.push_back(new Console::Cerr());
	methods.push_back(new Console::Cin());
	methods.push_back(new Console::Cout());
	methods.push_back(new Console::Endl());

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
	methods.push_back(new Strings::SubStr());
	methods.push_back(new Strings::ToLower());
	methods.push_back(new Strings::ToUpper());
}


}
}
}
