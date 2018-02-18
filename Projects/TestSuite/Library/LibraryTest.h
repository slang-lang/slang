
#ifndef Testing_Library_LibraryTest_h
#define Testing_Library_LibraryTest_h


// Library includes

// Project includes
#include <Common/Logger.h>
#include <Framework/GenericTest.h>

// Forward declarations

// Namespace declarations


namespace Testing {
namespace Library {


class LibraryTest : public GenericTest,
				 	private Utils::Common::Logger
{
public:
	LibraryTest(const Utils::Common::ILogger *p);

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
