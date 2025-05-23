
// Header
#include "BreakPoint.h"

// Library includes
#include <sstream>

// Project includes

// Namespace declarations


namespace Slang {
namespace Core {


BreakPoint::BreakPoint()
: mLine( static_cast<unsigned int>( -1 ) )
{
}

BreakPoint::BreakPoint(const Common::Position &position)
: mFilename(position.mFile),
  mLine(position.mLine)
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

std::string BreakPoint::toConfigString() const
{
	std::stringstream ss;
	ss << mFilename << " " << mLine;
	if ( mCondition.isValid() ) {
		ss << " " << mCondition.toString();
	}
	return ss.str();
}

std::string BreakPoint::toString() const
{
	std::stringstream ss;
	ss << mFilename << " " << mLine;
	if ( mCondition.isValid() ) {
		ss << " [" << mCondition.toString() << "]";
	}
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

bool BreakPoint::operator==(const Common::Position& other) const
{
	return (mFilename == other.mFile) && (mLine == other.mLine);
}


}
}
