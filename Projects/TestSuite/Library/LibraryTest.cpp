
#ifdef _WIN32
#pragma warning(disable : 4127)
#pragma warning(disable : 4702)
#endif

// Header
#include "LibraryTest.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Script.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Extension includes
#ifdef USE_SYSTEM_EXTENSION
#   include <LIBC/Extension.h>
#	include <System/SystemExtension.h>
#endif

// Namespace declarations
using namespace Slang;


namespace Testing {
namespace Library {


LibraryTest::LibraryTest( const Utils::Common::ILogger* p )
: UnitTest( "LibraryTest" ),
  Utils::Common::Logger( p, "LibraryTest" )
{
}

void LibraryTest::process()
{
	TEST(testSystemBoolean);
	TEST(testSystemCharacter);
	TEST(testSystemCharacterIterator);
	TEST(testSystemCollectionsDoubleLinkedList);
	//FIXME: TEST(testSystemCollectionsIterator);
	//FIXME: TEST(testSystemCollectionsList);
	//FIXME: TEST(testSystemCollectionsMap);
	TEST(testSystemCollectionsPair);
	//FIXME: TEST(testSystemCollectionsQueue);
	TEST(testSystemCollectionsSet);
	TEST(testSystemCollectionsStack);
	TEST(testSystemCollectionsVector);
	TEST(testSystemDouble);
	TEST(testSystemFloat);
	TEST(testSystemInteger);
	TEST(testSystemIOFile);
	TEST(testSystemIOLogger);
	TEST(testSystemString);
	TEST(testSystemStringIterator);
}

void LibraryTest::setup()
{
}

void LibraryTest::teardown()
{
}

void LibraryTest::testSystemBoolean()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Library/System/BooleanTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCharacter()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/CharacterTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCharacterIterator()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
		vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/CharacterIteratorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCollectionsDoubleLinkedList()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
        vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/Collections/DoubleLinkedListTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCollectionsIterator()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
        vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/Collections/IteratorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCollectionsList()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Library/System/Collections/ListTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCollectionsMap()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Library/System/Collections/MapTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCollectionsPair()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Library/System/Collections/PairTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCollectionsQueue()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
        vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/Collections/QueueTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCollectionsSet()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
        vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/Collections/SetTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCollectionsStack()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
        vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/Collections/StackTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemCollectionsVector()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
        vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/Collections/VectorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemDouble()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Library/System/DoubleTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemFloat()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Library/System/FloatTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}


void LibraryTest::testSystemInteger()
{
	try {
		VirtualMachine vm;
		vm.runScriptFromFile("Tests/Library/System/IntegerTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemIOFile()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
        vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/IO/FileTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemIOLogger()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
        vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/IO/LoggerTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemString()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
        vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/StringTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}

void LibraryTest::testSystemStringIterator()
{
	try {
		VirtualMachine vm;
#ifdef USE_SYSTEM_EXTENSION
        vm.addExtension(new Slang::Extensions::LIBC::Extension());
		vm.addExtension(new Slang::Extensions::System::SystemExtension());
#endif
		vm.runScriptFromFile("Tests/Library/System/StringIteratorTest.os");

		// automatic success
	}
	catch ( std::exception& e ) {
		// exception has been thrown: test failed
		TFAIL(e.what());
	}
}


}
}
