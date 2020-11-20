
#ifndef _Testing_Prototype_Fixture_h_
#define _Testing_Prototype_Fixture_h_


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/TestFixture.h>

// Forward declarations

// Namespace declarations
using namespace Testing;


namespace Testing {
namespace Prototype {


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
