
// Header
#include "Position.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Utils {


Position::Position(unsigned int l, unsigned int c)
: line(l), column(c)
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
}
