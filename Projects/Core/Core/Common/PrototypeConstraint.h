
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
	PrototypeConstraint(unsigned int index, const std::string& designType, const std::string& runType, const std::string& constraint);

public:
	bool operator==(const PrototypeConstraint& other) const;

	bool typeHasBeenResolved() const;

public:
	std::string mConstraint;
	std::string mDesignType;
	unsigned int mIndex;
	std::string mRunType;
};

typedef std::list<PrototypeConstraint> PrototypeConstraints;


}


#endif
