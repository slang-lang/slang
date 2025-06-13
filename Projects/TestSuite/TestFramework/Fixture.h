
#ifndef _Testing_TestFramework_Fixture_h_
#define _Testing_TestFramework_Fixture_h_


// Library includes

// Project includes
#include <Core/Common/Types.h>
#include <Framework/TestFixture.h>
#include <Logger/Logger.h>

// Forward declarations

// Namespace declarations
using namespace Slang;
using namespace Testing;


namespace Testing {
namespace Framework {


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
