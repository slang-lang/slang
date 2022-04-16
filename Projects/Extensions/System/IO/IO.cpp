
// Header
#include "IO.h"

// Library includes

// Project includes
#include "FGETS.h"
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

const int32_t STDIN  = 1;
const int32_t STDOUT = 2;
const int32_t STDERR = 3;

SystemIOExtension::SystemIOExtension()
: AExtension( "IO", "0.1.0" )
{
}

void SystemIOExtension::initialize( Slang::IScope* scope )
{
    // IO constants
    scope->define( "STDIN", new Runtime::IntegerObject( "STDIN", STDIN ) );
    scope->define( "STDOUT", new Runtime::IntegerObject( "STDOUT", STDOUT ) );
    scope->define( "STDERR", new Runtime::IntegerObject( "STDERR", STDERR ) );

	// nothing to do here
    mFileHandles[ 0 ]      = nullptr;
    mFileHandles[ STDIN ]  = stdin;
    mFileHandles[ STDOUT ] = stdout;
    mFileHandles[ STDERR ] = stderr;
}

void SystemIOExtension::provideMethods( ExtensionMethods& methods )
{
    methods.push_back( new FGETS() );
	methods.push_back( new FileClose() );
	methods.push_back( new FileEOF() );
	methods.push_back( new FileOpen() );
	methods.push_back( new FileReadBool() );
	methods.push_back( new FileReadDouble() );
	methods.push_back( new FileReadFloat() );
	methods.push_back( new FileReadInt() );
	methods.push_back( new FileReadString() );
	methods.push_back( new FileSeek() );
	methods.push_back( new FileTell() );
	methods.push_back( new FileWriteBool() );
	methods.push_back( new FileWriteDouble() );
	methods.push_back( new FileWriteFloat() );
	methods.push_back( new FileWriteInt() );
	methods.push_back( new FileWriteString() );
}


}
}
}
}
