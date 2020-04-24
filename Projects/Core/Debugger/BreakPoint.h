
#ifndef Core_Debugger_BreakPoint_h
#define Core_Debugger_BreakPoint_h


// Library includes
#include <set>
#include <string>

// Project includes
#include <Core/Common/Position.h>
#include "Condition.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Core {


class BreakPoint
{
public:
	BreakPoint();
	explicit BreakPoint(const Common::Position& position);
	~BreakPoint() = default;

public:
	const Condition& getCondition() const;
	void setCondition(const Condition& condition);

	const std::string& getFilename() const;
	unsigned int getLine() const;

	std::string toConfigString() const;
	std::string toString() const;

public:
	bool operator<(const BreakPoint& other) const;
	bool operator==(const BreakPoint& other) const;
	bool operator==(const Common::Position& other) const;

private:
	Condition mCondition;
	std::string mFilename;
	unsigned int mLine;
};


typedef std::set<BreakPoint> BreakPointCollection;


}
}


#endif
