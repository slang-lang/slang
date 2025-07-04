
#ifndef _Framework_UnitTest_h_
#define _Framework_UnitTest_h_


// Library includes

// Project includes
#include <MyUnit/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {

class UnitTest : public MyUnit::GenericTest
{
public:
    explicit UnitTest( std::string name )
    : GenericTest( std::move( name ) )
    { }
};

}


#endif