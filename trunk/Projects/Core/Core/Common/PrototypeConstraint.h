
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

	bool hasRuntimeType() const;

public:
	std::string mConstraint;
	std::string mDesignType;
	unsigned int mIndex;
	std::string mRunType;
};


class PrototypeConstraints : public std::list<PrototypeConstraint>
{
public:
	std::string extractTypes(const std::list<PrototypeConstraint>& other) const;
	bool hasRuntimeTypes() const;
	const std::string& lookupType(const std::string& type) const;
};


}


#endif
