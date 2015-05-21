
#ifndef Testing_Math_Fixture_h
#define Testing_Math_Fixture_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/TestFixture.h>

// Forward declarations

// Namespace declarations
using namespace Testing;


namespace Testing {
namespace Math {


class Fixture : public TestFixture,
				private Utils::Common::Logger
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
