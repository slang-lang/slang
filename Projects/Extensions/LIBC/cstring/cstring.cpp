
// Header
#include "cstring.hpp"

// Library includes
#include <cstring>

// Project includes
#include "strcat.h"
#include "strchr.h"
#include "strcmp.h"
#include "strcoll.h"
#include "strcspn.h"
#include "strlen.h"
#include "strncat.h"
#include "strncmp.h"
#include "strpbrk.h"
#include "strspn.h"
#include "strrchr.h"
#include "strstr.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cstring {


cstring_t::cstring_t()
: AExtension( "cstring", "0.0.1" )
{
}

void cstring_t::initialize( ExtensionNamespace* scope )
{
    (void)scope;
}

void cstring_t::provideMethods( ExtensionMethods& methods )
{
    methods.push_back( new cstring::STRCAT() );
    methods.push_back( new cstring::STRCHR() );
    methods.push_back( new cstring::STRCMP() );
    methods.push_back( new cstring::STRCOLL() );
    methods.push_back( new cstring::STRCSPN() );
    methods.push_back( new cstring::STRLEN() );
    methods.push_back( new cstring::STRNCAT() );
    methods.push_back( new cstring::STRNCMP() );
    methods.push_back( new cstring::STRPBRK() );
    methods.push_back( new cstring::STRSPN() );
    methods.push_back( new cstring::STRRCHR() );
    methods.push_back( new cstring::STRSTR() );

}


}
}
}
}
