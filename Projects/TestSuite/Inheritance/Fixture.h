
#ifndef Testing_Inheritance_Fixture_h
#define Testing_Inheritance_Fixture_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/TestFixture.h>

// Forward declarations

// Namespace declarations
using namespace Testing;


namespace Testing {
namespace Inheritance {


class Fixture : public TestFixture,
                private Utils::Common::FileLogger
{
public:
    Fixture(const Utils::Common::ILogger *p);
    ~Fixture();

public:
    void setup();
    void teardown();

protected:

private:

};


}
}


#endif
