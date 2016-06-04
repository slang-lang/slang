
// Header
#include "Position.h"

// Library includes
#include <sstream>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Utils {


Position::Position(const std::string& file, unsigned int line, unsigned int column)
: mFile(file), mLine(line), mColumn(column)
{
}

bool Position::operator==(const Position& other) const
{
	return (this->mFile == other.mFile && this->mLine == other.mLine && this->mColumn == other.mColumn);
}

bool Position::operator<(const Position& other) const
{
	if ( this->mFile == other.mFile ) {
		if ( this->mLine == other.mLine ) {
			return (this->mColumn < other.mColumn);
		}

		return (this->mLine < other.mLine);
	}

	return (this->mFile < other.mFile);
}

std::string Position::toString() const
{
	std::stringstream ss;

	if ( !mFile.empty() ) {
		ss << "file " << mFile;
	}
	if ( mLine != 0 ) {
		ss << ", line " << mLine;

		if ( mColumn != 0 ) {
			ss << ", column " << mColumn;
		}
	}

	return ss.str();
}


}
}
