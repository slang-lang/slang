
#ifndef ObjectiveScript_Designtime_Prototype_h
#define ObjectiveScript_Designtime_Prototype_h


// Library includes
#include <list>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class PrototypeConstraint
{
public:
	PrototypeConstraint(unsigned int index, const std::string& type, const std::string& constraint)
	: mConstraint(constraint),
	  mIndex(index),
	  mType(type)
	{ }

public:
	bool operator==(const PrototypeConstraint& other) const {
		return mConstraint == other.mConstraint && mIndex == other.mIndex && mType == mType;
	}

public:
	std::string mConstraint;
	unsigned int mIndex;
	std::string mType;
};

typedef std::list<PrototypeConstraint> PrototypeConstraints;


}
}


#endif
