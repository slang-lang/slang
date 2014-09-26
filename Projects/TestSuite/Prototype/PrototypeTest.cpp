
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)

// Header
#include "PrototypeTest.h"

// Library includes

// Project includes

// Namespace declartations


namespace Testing {
namespace Prototype {


PrototypeTest::PrototypeTest(const Utils::Common::Logger *p)
: Utils::Common::Logger(p, "PrototypeTest")
{
}

void PrototypeTest::process()
{
	TEST(testPrototypeDeclaration);
	TEST(testPrototypeUsage);
}

void PrototypeTest::setup()
{
}

void PrototypeTest::teardown()
{
}

void PrototypeTest::testPrototypeDeclaration()
{
}

void PrototypeTest::testPrototypeUsage()
{
}


}
}
