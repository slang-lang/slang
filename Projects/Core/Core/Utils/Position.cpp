
// Header
#include "Position.h"

// Library includes
#include <sstream>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Utils {


Position::Position(const std::string& f, unsigned int l, unsigned int c)
: file(f), line(l), column(c)
{
}

bool Position::operator==(const Position& other) const
{
	return (this->file == other.file && this->line == other.line && this->column == other.column);
}

bool Position::operator<(const Position& other) const
{
	if ( this->file == other.file ) {
		if ( this->line == other.line ) {
			return (this->column < other.column);
		}

		return (this->line < other.line);
	}

	return (this->file < other.file);
}

std::string Position::toString() const
{
	std::stringstream ss;
	if ( !file.empty() ) {
		ss << "File " << file << ": ";
	}
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
