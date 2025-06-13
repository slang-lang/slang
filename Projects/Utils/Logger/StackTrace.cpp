
// Header
#include "StackTrace.h"

// Library includes
#include <execinfo.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

// Project includes

// Namespace declarations


namespace Utils {
namespace Common {


void printStackTrace()
{
    const int MAX_FRAMES = 64;
    void* buffer[ MAX_FRAMES ];

    int nptrs = backtrace( buffer, MAX_FRAMES );
    char** symbols = backtrace_symbols( buffer, nptrs );
    if ( symbols == nullptr ) {
        perror( "backtrace_symbols" );
        exit( EXIT_FAILURE );
    }

    printf( "Stack trace:\n" );
    for ( int i = 0; i < nptrs; ++i ) {
        printf( "%s\n", symbols[i] );
    }

    free(symbols);
}


}
}
