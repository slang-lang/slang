
#ifndef Slang_Core_Core_AST_TreeLineBuffer_h
#define Slang_Core_Core_AST_TreeLineBuffer_h


// Library includes
#include <map>
#include <string>

// Project includes
#include <Core/Common/Position.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace AST {


class TreeLineBuffer
{
public:
	typedef std::map<Common::Position, std::string> Lines;

public:
	TreeLineBuffer() = default;
	~TreeLineBuffer() = default;

public:
	void getLines(Lines& lines) const;

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
