
// Header
#include "BreakPoint.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Core {


BreakPoint::BreakPoint()
: mLine(-1)
{
}

BreakPoint::BreakPoint(const Utils::Position &position)
: mFilename(position.mFile),
  mLine(position.mLine)
{
}

BreakPoint::~BreakPoint()
{
}

const std::string& BreakPoint::getFilename() const
{
	return mFilename;
}

unsigned int BreakPoint::getLine() const
{
	return mLine;
}

bool BreakPoint::operator<(const BreakPoint& other) const
{
	if ( mFilename == other.mFilename ) {
		return mLine < other.mLine;
	}

	return mFilename < other.mFilename;
}

bool BreakPoint::operator==(const BreakPoint& other) const
{
	return (mFilename == other.mFilename) && (mLine == other.mLine);
}

bool BreakPoint::operator==(const Utils::Position& other) const
{
	return (mFilename == other.mFile) && (mLine == other.mLine);
}


}
}
