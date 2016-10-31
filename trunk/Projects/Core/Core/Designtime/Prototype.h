
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
	PrototypeConstraint(const std::string& type, const std::string& constraint)
	: mConstraint(constraint),
	  mType(type)
	{ }

public:
	std::string mConstraint;
	std::string mType;
};

typedef std::list<PrototypeConstraint> PrototypeConstraints;


}
}


#endif
