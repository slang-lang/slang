
#ifndef Slang_Core_Core_Designtime_Ancestor_h
#define Slang_Core_Core_Designtime_Ancestor_h


// Library includes
#include <set>
#include <string>

// Project includes
#include <Core/Common/TypeDeclaration.h>
#include <Core/Common/Visibility.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class Ancestor
{
public:
	class Type
	{
	public:
		enum E {
			Unknown = 0,
			Extends,
			Hidden,
			Implements,
			Replicates
		};
	};

public:
	Ancestor();
	Ancestor(const Common::TypeDeclaration& typeDeclaration, Type::E ancestorType, Visibility::E visibility);

public:
	bool operator<(const Ancestor& other) const;
	bool operator==(const Ancestor& other) const;

public:
	Type::E ancestorType() const;
	const PrototypeConstraints& constraints() const;
	const std::string& name() const;
	const Common::TypeDeclaration& typeDeclaration() const;
	Visibility::E visibility() const;

private:
	Type::E mAncestorType;
	Common::TypeDeclaration mTypeDeclaration;
	Visibility::E mVisibility;
};

typedef std::set<Ancestor> Ancestors;


}
}


#endif
