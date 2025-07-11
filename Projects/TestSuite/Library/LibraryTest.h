
#ifndef Testing_Library_LibraryTest_h
#define Testing_Library_LibraryTest_h


// Library includes

// Project includes
#include <Logger/Logger.h>
#include <Framework/UnitTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Library {


class LibraryTest : public UnitTest,
				 	private Utils::Common::Logger
{
public:
	explicit LibraryTest( const Utils::Common::ILogger* p );
	~LibraryTest() = default;

public:
	void process();
	void setup();
	void teardown();

private:	// Tests
	void testSystemBoolean();
	void testSystemCharacter();
	void testSystemCharacterIterator();
	void testSystemCollectionsDoubleLinkedList();
	void testSystemCollectionsIterator();
	void testSystemCollectionsList();
	void testSystemCollectionsMap();
	void testSystemCollectionsPair();
	void testSystemCollectionsQueue();
	void testSystemCollectionsSet();
	void testSystemCollectionsStack();
	void testSystemCollectionsVector();
	void testSystemDouble();
	void testSystemFloat();
	void testSystemInteger();
	void testSystemIOFile();
	void testSystemIOLogger();
	void testSystemString();
	void testSystemStringIterator();
};


}
}


#endif
