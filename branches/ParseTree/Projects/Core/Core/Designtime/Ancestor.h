
#ifndef ObjectiveScript_Designtime_Ancestor_h
#define ObjectiveScript_Designtime_Ancestor_h


// Library includes
#include <set>
#include <string>

// Project includes
#include <Core/Common/TypeDeclaration.h>
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
	Ancestor(const TypeDeclaration& typeDeclaration, Type::E ancestorType, Visibility::E visibility);

public:
	bool operator<(const Ancestor& other) const;
	bool operator==(const Ancestor& other) const;

public:
	Type::E ancestorType() const;
	const PrototypeConstraints& constraints() const;
	const std::string& name() const;
	Visibility::E visibility() const;

private:
	Type::E mAncestorType;
	TypeDeclaration mTypeDeclaration;
	Visibility::E mVisibility;
};

typedef std::set<Ancestor> Ancestors;


}
}


#endif
