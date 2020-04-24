
// Header
#include "IO.h"

// Library includes

// Project includes
#include "FileClose.h"
#include "FileEOF.h"
#include "FileOpen.h"
#include "FileRead.h"
#include "FileSeek.h"
#include "FileTell.h"
#include "FileWrite.h"


// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace IO {


SystemIOExtension::SystemIOExtension()
: AExtension("IO")
{
}

void SystemIOExtension::initialize(Slang::IScope* /*scope*/)
{
	// nothing to do here
}

void SystemIOExtension::provideMethods(ExtensionMethods &methods)
{
	methods.push_back(new FileClose());
	methods.push_back(new FileEOF());
	methods.push_back(new FileOpen());
	methods.push_back(new FileReadBool());
	methods.push_back(new FileReadDouble());
	methods.push_back(new FileReadFloat());
	methods.push_back(new FileReadInt());
	methods.push_back(new FileReadString());
	methods.push_back(new FileSeek());
	methods.push_back(new FileTell());
	methods.push_back(new FileWriteBool());
	methods.push_back(new FileWriteDouble());
	methods.push_back(new FileWriteFloat());
	methods.push_back(new FileWriteInt());
	methods.push_back(new FileWriteString());
}


}
}
}
}
