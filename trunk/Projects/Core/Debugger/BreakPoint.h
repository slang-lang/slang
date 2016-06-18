
#ifndef Debugger_BreakPoint_h
#define Debugger_BreakPoint_h


// Library includes
#include <list>
#include <string>
#include <vector>

// Project includes
#include <Core/Utils/Position.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Core {


class BreakPoint
{
public:
	BreakPoint();
	BreakPoint(const Utils::Position& position);
	~BreakPoint();

public:
	const std::string& getFilename() const;
	unsigned int getLine() const;

	std::string toString() const;

public:
	bool operator<(const BreakPoint& other) const;
	bool operator==(const BreakPoint& other) const;
	bool operator==(const Utils::Position& other) const;

private:
	std::string mFilename;
	unsigned int mLine;
};


typedef std::list<BreakPoint> BreakPointList;


}
}


#endif
