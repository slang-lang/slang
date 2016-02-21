
#ifndef ObjectiveScript_Designtime_Ancestor_h
#define ObjectiveScript_Designtime_Ancestor_h


// Library includes
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Visibility.h>

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
			Unknown,
			Extends,
			Implements
		};
	};

	Ancestor();
	Ancestor(const std::string& name, Type::E type, Visibility::E visibility);

public:
	const std::string& name() const;
	Type::E type() const;
	Visibility::E visibility() const;

protected:

private:
	std::string	mName;
	Type::E mType;
	Visibility::E mVisibility;
};

typedef std::map<std::string, Ancestor> Ancestors;


}
}


#endif
