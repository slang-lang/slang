
#ifndef Testing_AST_Fixture_h
#define Testing_AST_Fixture_h


// Library includes

// Project includes
#include <Logger/Logger.h>
#include <Framework/TestFixture.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace AST {


class Fixture : public TestFixture,
				private Utils::Common::Logger
{
public:
	Fixture( const Utils::Common::ILogger *p, StringSet libraries );
	~Fixture() = default;

public:
	void setup();
	void teardown();
};


}
}


#endif
