
#ifndef Testing_Extensions_Fixture_h
#define Testing_Extensions_Fixture_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/TestFixture.h>

// Forward declarations

// Namespace declarations
using namespace Testing;


namespace Testing {
namespace Extensions {


class Fixture : public TestFixture,
				private Utils::Common::Logger
{
public:
	explicit Fixture( const Utils::Common::ILogger* p );
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
