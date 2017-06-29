
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
	Lines::iterator it = mTreeLines.find(position);
	if ( it != mTreeLines.end() ) {
		it->second += content;
		return;
	}

	mTreeLines.insert(std::make_pair(position, content));
}

void TreeLineBuffer::insert(const Lines& lines)
{
	for ( Lines::const_iterator it = lines.begin(); it != lines.end(); ++it ) {
		insert(it->first, it->second);
	}
}


}
}
