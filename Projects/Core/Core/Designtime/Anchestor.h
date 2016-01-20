
#ifndef ObjectiveScript_Designtime_Anchestor_h
#define ObjectiveScript_Designtime_Anchestor_h


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
	Ancestor();
	Ancestor(const std::string& name, Visibility::E visibility);

public:
	const std::string& name() const;
	Visibility::E visibility() const;

protected:

private:
	std::string	mName;
	Visibility::E mVisibility;
};

typedef std::map<std::string, Ancestor> Ancestors;


}
}


#endif
