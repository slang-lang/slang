
#ifndef _Framework_TestFixture_h_
#define _Framework_TestFixture_h_


// Library includes

// Project includes
#include <Core/Common/Types.h>
#include <MyUnit/TestFixture.h>

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Testing {


class TestFixture : public MyUnit::TestFixture
{
public:
    TestFixture( std::string name, StringSet libraries )
    : MyUnit::TestFixture( std::move( name ) )
    , mLibraryFolders( std::move( libraries ) )
    { }

protected:
    StringSet mLibraryFolders;
};


}


#endif
