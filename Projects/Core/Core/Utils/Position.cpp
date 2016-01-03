
// Header
#include "Position.h"

// Library includes
#include <sstream>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Utils {


Position::Position(unsigned int l, unsigned int c)
: line(l), column(c)
{
}

bool Position::operator==(const Position& other) const
{
	return (this->line == other.line && this->column == other.column);
}

bool Position::operator<(const Position& other) const
{
	if ( this->line == other.line ) {
		return (this->column < other.column);
	}

	return (this->line < other.line);
}

std::string Position::toString() const
{
	std::stringstream ss;
	if ( line != 0 ) {
		ss << "Line " << line;

		if ( column != 0 ) {
			ss << ", Column " << column;
		}
	}
	return ss.str();
}


}
}
