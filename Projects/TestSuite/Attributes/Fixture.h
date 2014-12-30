
#ifndef Testing_Attributes_Fixture_h
#define Testing_Attributes_Fixture_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/TestFixture.h>

// Forward declarations

// Namespace declarations
using namespace Testing;


namespace Testing {
namespace Attributes {


class Fixture : public TestFixture,
				private Utils::Common::Logger
{
public:
	Fixture(const Utils::Common::Logger *p);
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
