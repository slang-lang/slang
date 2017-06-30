
// Header
#include "TreeLineBuffer.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


TreeLineBuffer::TreeLineBuffer()
{
}

TreeLineBuffer::~TreeLineBuffer()
{
}

void TreeLineBuffer::append(const std::string& content)
{
	insert(mLastInsertPosition, content);
}

void TreeLineBuffer::clear()
{
	mTreeLines.clear();
}

void TreeLineBuffer::getLines(Lines& lines)
{
	lines = mTreeLines;
}

void TreeLineBuffer::insert(const Common::Position& position, const std::string& content)
{
	// store last insert position for append
	mLastInsertPosition = position;

	// find out if there is still some content at this given position
	Lines::iterator it = mTreeLines.find(position);
	if ( it != mTreeLines.end() ) {
		// append content at an existing position
		it->second += content;
		return;
	}

	// insert content at a new position
	mTreeLines.insert(std::make_pair(position, content));
}

void TreeLineBuffer::insert(const Lines& lines)
{
	for ( Lines::const_iterator it = lines.begin(); it != lines.end(); ++it ) {
		insert(it->first, it->second);
	}
}

void TreeLineBuffer::insert(const TreeLineBuffer& buffer)
{
	insert(buffer.mTreeLines);
}


}
}
