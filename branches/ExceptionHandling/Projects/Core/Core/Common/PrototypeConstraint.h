
#ifndef ObjectiveScript_Common_PrototypeConstraint_h
#define ObjectiveScript_Common_PrototypeConstraint_h


// Library includes
#include <list>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class PrototypeConstraint
{
public:
	PrototypeConstraint(unsigned int index, const std::string& type, const std::string& constraint);

public:
	bool operator==(const PrototypeConstraint& other) const;

public:
	std::string mConstraint;
	unsigned int mIndex;
	std::string mType;
};

typedef std::list<PrototypeConstraint> PrototypeConstraints;


}


#endif
