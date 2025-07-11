
#ifndef Testing_Interfaces_Fixture_h
#define Testing_Interfaces_Fixture_h


// Library includes

// Project includes
#include <Logger/Logger.h>
#include <Framework/TestFixture.h>

// Forward declarations

// Namespace declarations
using namespace Testing;


namespace Testing {
namespace Interfaces {


class Fixture : public TestFixture,
                private Utils::Common::Logger
{
public:
    explicit Fixture( const Utils::Common::ILogger* p, StringSet libraries );
    ~Fixture() = default;

public:
    void setup();
    void teardown();

protected:

private:

};


}
}


#endif
