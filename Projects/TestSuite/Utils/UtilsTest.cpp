
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "UtilsTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <SemVer/Version.h>
#include <Tools/Strings.h>

// Namespace declartations
using namespace Slang;


namespace Testing {
namespace UtilsTest {


UtilsTest::UtilsTest( const Utils::Common::ILogger* p )
: UnitTest( "UtilsTest" )
, Utils::Common::Logger( p, "UtilsTest" )
{
}

void UtilsTest::process()
{
	TEST(testSemVer);
	TEST(testSplitBy);
}

void UtilsTest::setup()
{
}

void UtilsTest::teardown()
{
}

void UtilsTest::testSemVer()
{
	try {
		SemanticVersionNumber version100( "1.0.0" );
		SemanticVersionNumber version100WithBuildMetadata( "1.0.0+001" );
		SemanticVersionNumber version100WithLabel( "1.0.0-label" );
		SemanticVersionNumber version100WithLabelAndBuildMetadata( "1.0.0-alpha+001" );
		SemanticVersionNumber version101( "1.0.1" );
		SemanticVersionNumber version101WithBuildMetadata( "1.0.1+001" );
		SemanticVersionNumber version101WithLabel( "1.0.1-label" );
		SemanticVersionNumber version101WithLabelAndBuildMetadata( "1.0.1-alpha+001" );

		std::cout << "1.0.0+001 vs " << version100WithBuildMetadata.toString() << std::endl;

		assert( (version100 < version101) );
		TVERIFY( (version100WithLabel < version100) );
		TVERIFY( (version100WithLabelAndBuildMetadata < version100WithLabel) );

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void UtilsTest::testSplitBy()
{
    try {
        std::string version( "1.2.3-alpha+001" );

		std::string bugfix;
		std::string buildMetadata;
		std::string label;
		std::string major;
		std::string minor;

		// 1 . 2.3-alpha+001
		Utils::Tools::splitBy( version, '.', major, version );
		// 2 . 3-alpha+001
		Utils::Tools::splitBy( version, '.', minor, version );
		// 3-alpha + 001
		Utils::Tools::splitBy( version, '+', label, buildMetadata );
		// 3 - alpha
		Utils::Tools::splitBy( label, '-', bugfix, label );

		std::cout << major << " . " << minor << " . " << bugfix << " - " << label << " + " << buildMetadata << std::endl;

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
