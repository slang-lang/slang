
#ifndef ObjectiveScript_Designtime_Ancestor_h
#define ObjectiveScript_Designtime_Ancestor_h


// Library includes
#include <set>
#include <string>

// Project includes
#include <Core/Common/PrototypeConstraint.h>
#include <Core/Common/Visibility.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class Ancestor
{
public:
	class Type
	{
	public:
		enum E {
			Extends,
			Implements,
			Replicates,
			Unknown
		};
	};

public:
	Ancestor();
	Ancestor(const std::string& name, Type::E type, Visibility::E visibility, const PrototypeConstraints& constraints);

public:
	bool operator<(const Ancestor& other) const;
	bool operator==(const Ancestor& other) const;

public:
	const PrototypeConstraints& constraints() const;
	const std::string& name() const;
	Type::E type() const;
	Visibility::E visibility() const;

private:
	std::string	mName;
	PrototypeConstraints mPrototypeConstraints;
	Type::E mType;
	Visibility::E mVisibility;
};

typedef std::set<Ancestor> Ancestors;


}
}


#endif
