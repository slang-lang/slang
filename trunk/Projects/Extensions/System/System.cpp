
// Header
#include "System.h"

// Library includes

// Project includes
#include <System/IO/FileClose.h>
#include <System/IO/FileOpen.h>
#include <System/IO/FileRead.h>
#include <System/IO/FileSeek.h>
#include <System/IO/FileWrite.h>
#include "AssertMsg.h"
#include "Print.h"
#include "Write.h"
#include "WriteLn.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


void System::provideMethods(ExtensionMethods &methods)
{
	assert(methods.empty());

	methods.push_back(new AssertMsg());
	methods.push_back(new Printf());
	methods.push_back(new Write());
	methods.push_back(new WriteLn());

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
}


}
}
