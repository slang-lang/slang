
// Header
#include "Position.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Position::Position(size_t l = 0, size_t c = 0)
: column(c), line(l)
{
}

bool Position::operator==(const Position& other)
{
	return (this->line == other.line && this->column == other.column);
}

bool Position::operator<(const Position& other)
{
	if ( this->line == other.line ) {
		return (this->column < other.column);
	}
	return (this->line < other.line);
}


}
