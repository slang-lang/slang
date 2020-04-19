
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
	PrototypeConstraint();
	PrototypeConstraint(size_t index, std::string designType, std::string runType, std::string constraint);

public:
	bool operator==(const PrototypeConstraint& other) const;

	bool hasDesigntimeType() const;
	bool hasRuntimeType() const;

public:
	std::string mConstraint;
	std::string mDesignType;
	size_t mIndex;
	std::string mRunType;
};


class PrototypeConstraints : public std::list<PrototypeConstraint>
{
public:
	bool operator==(const PrototypeConstraints& other) const;

public:
	PrototypeConstraints buildRawConstraints(const PrototypeConstraints& other) const;
	PrototypeConstraints buildRuntimeConstraints(const PrototypeConstraints& other) const;
	std::string extractTypes(const PrototypeConstraints& other) const;
	bool hasDesigntimeTypes() const;
	bool hasRuntimeTypes() const;
	PrototypeConstraint lookupConstraint(const std::string &type) const;
	const std::string& lookupType(const std::string& type) const;
};


}


#endif
