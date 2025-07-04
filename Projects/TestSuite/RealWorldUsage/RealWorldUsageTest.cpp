
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "RealWorldUsageTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Namespace declartations
using namespace Slang;


namespace Testing {
namespace RealWorldUsage {


RealWorldUsageTest::RealWorldUsageTest( const Utils::Common::ILogger* p )
: UnitTest( "RealWorldUsageTest" ),
  Utils::Common::Logger( p, "RealWorldUsageTest" )
{
}

void RealWorldUsageTest::process()
{
	TEST(testAlternateMemberDeclaration);
	TEST(testAutoBoxing);
	TEST(testCWithNamespace);
	TEST(testCreateScriptFromString);
	TEST(testDeeperNamespaces);
}

void RealWorldUsageTest::setup()
{
}

void RealWorldUsageTest::teardown()
{
}

void RealWorldUsageTest::testAlternateMemberDeclaration()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/RealWorldUsage/Namespaces/AlternateMemberDeclaration.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void RealWorldUsageTest::testAutoBoxing()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/RealWorldUsage/AutoBoxing.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void RealWorldUsageTest::testCWithNamespace()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/RealWorldUsage/Namespaces/C-WithNamespaces.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void RealWorldUsageTest::testCreateScriptFromString()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromString(
			"public object Main {\
				public void Main(int argc = 0, string args = \"\") {\
					var one = 1;\
					print(\"one = \" + one);\
				}\
			}"
		);

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}

void RealWorldUsageTest::testDeeperNamespaces()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/RealWorldUsage/Namespaces/DeeperNamespaces.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed!
		TFAIL(e.what());
	}
}


}
}
