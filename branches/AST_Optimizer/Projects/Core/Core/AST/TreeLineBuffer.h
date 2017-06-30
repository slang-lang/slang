
#ifndef ObjectiveScript_Core_AST_TreeLineBuffer_h
#define ObjectiveScript_Core_AST_TreeLineBuffer_h

#include <Core/Defines.h>

// Library includes
#ifdef USE_ORDERED_COLLECTION
#	include <map>
#else
#	include <unordered_map>
#endif
#include <string>

// Project includes
#include <Core/Common/Position.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


class TreeLineBuffer
{
public:
#ifdef USE_ORDERED_COLLECTION
		typedef std::map<Common::Position, std::string> Lines;
#else
		typedef std::unordered_map<Common::Position, std::string> Lines;
#endif

public:
	TreeLineBuffer();
	~TreeLineBuffer();

public:
	void getLines(Lines& lines);

	void append(const std::string& content);
	void clear();
	void insert(const Common::Position& position, const std::string& content);
	void insert(const Lines& lines);
	void insert(const TreeLineBuffer& buffer);

private:
	Common::Position mLastInsertPosition;
	Lines mTreeLines;
};


}
}


#endif
