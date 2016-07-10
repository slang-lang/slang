
// Header
#include "BreakPoint.h"

// Library includes
#include <sstream>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Core {


BreakPoint::BreakPoint()
: mLine((unsigned int)-1)
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

const Condition& BreakPoint::getCondition() const
{
	return mCondition;
}

const std::string& BreakPoint::getFilename() const
{
	return mFilename;
}

unsigned int BreakPoint::getLine() const
{
	return mLine;
}

void BreakPoint::setCondition(const Condition& condition)
{
	mCondition = condition;
}

std::string BreakPoint::toString() const
{
	std::stringstream ss;
	ss << mFilename << " " << mLine << " [" << mCondition.toString() << "]";
	return ss.str();
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
