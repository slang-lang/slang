
// Header
#include "stdio.hpp"

// Library includes

// Project includes
#include "clearerr.h"
#include "getchar.h"
#include "fclose.h"
#include "feof.h"
#include "ferror.h"
#include "fflush.h"
#include "fgetc.h"
#include "fgets.h"
#include "fopen.h"
#include "fputc.h"
#include "fputs.h"
#include "fread.h"
#include "fseek.h"
#include "ftell.h"
#include "fwrite.h"
#include "perror.h"
#include "putchar.h"
#include "puts.h"
#include "remove.h"
#include "rename.h"
#include "rewind.h"
#include "tmpfile.h"
#include "tmpnam.h"
#include "ungetc.h"


// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionLIBC {
namespace stdio {


stdio_t::FileHandles_t stdio_t::FileHandles;

const int32_t STDIN  = 1;
const int32_t STDOUT = 2;
const int32_t STDERR = 3;

stdio_t::stdio_t()
: AExtension( "stdio", "0.2.0" )
{
}

void stdio_t::initialize( ExtensionNamespace* scope )
{
	// constants
	scope->define( "BUFSIZ",       new Runtime::IntegerObject( "BUFSIZ",       BUFSIZ ) );
	scope->define( "EOF",          new Runtime::IntegerObject( "EOF",          EOF ) );
	scope->define( "FILENAME_MAX", new Runtime::IntegerObject( "FILENAME_MAX", FILENAME_MAX ) );
	scope->define( "FOPEN_MAX",    new Runtime::IntegerObject( "FOPEN_MAX",    FOPEN_MAX ) );
	scope->define( "TMP_MAX",      new Runtime::IntegerObject( "TMP_MAX",      TMP_MAX ) );

	scope->define( "STDIN",  new Runtime::IntegerObject( "STDIN",  STDIN ) );
	scope->define( "STDOUT", new Runtime::IntegerObject( "STDOUT", STDOUT ) );
	scope->define( "STDERR", new Runtime::IntegerObject( "STDERR", STDERR ) );

	scope->define( "SEEK_SET", new Runtime::IntegerObject( "SEEK_SET", SEEK_SET ) );
	scope->define( "SEEK_CUR", new Runtime::IntegerObject( "SEEK_CUR", SEEK_CUR ) );
	scope->define( "SEEK_END", new Runtime::IntegerObject( "SEEK_END", SEEK_END ) );

	// nothing to do here
	FileHandles[ 0 ]      = nullptr;
	FileHandles[ STDIN ]  = stdin;
	FileHandles[ STDOUT ] = stdout;
	FileHandles[ STDERR ] = stderr;
}

void stdio_t::provideMethods( ExtensionMethods& methods )
{
    methods.push_back( new CLEARERR() );
    methods.push_back( new GETCHAR() );
	methods.push_back( new FERROR() );
	methods.push_back( new FFLUSH() );
	methods.push_back( new FGETC() );
	methods.push_back( new FGETS() );
	methods.push_back( new FCLOSE() );
	methods.push_back( new FEOF() );
	methods.push_back( new FOPEN() );
	methods.push_back( new FPUTC() );
	methods.push_back( new FPUTS() );
	methods.push_back( new FREADB() );
	methods.push_back( new FREADD() );
	methods.push_back( new FREADF() );
	methods.push_back( new FREADI() );
	methods.push_back( new FREADS() );
	methods.push_back( new FSEEK() );
	methods.push_back( new FTELL() );
	methods.push_back( new FWRITEB() );
	methods.push_back( new FWRITED() );
	methods.push_back( new FWRITEF() );
	methods.push_back( new FWRITEI() );
	methods.push_back( new FWRITES() );
	methods.push_back( new PERROR() );
	methods.push_back( new PUTCHAR() );
	methods.push_back( new PUTS() );
	methods.push_back( new REMOVE() );
	methods.push_back( new RENAME() );
	methods.push_back( new REWIND() );
	methods.push_back( new TMPFILE() );
	methods.push_back( new TMPNAM() );
	methods.push_back( new UNGETC() );
}


}
}
}
}
