
#ifndef ObjectiveScript_Core_Core_Extensions_AExtension_h
#define ObjectiveScript_Core_Core_Extensions_AExtension_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "ExtensionMethod.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IScope;

namespace Extensions {

typedef std::list<ExtensionMethod*> ExtensionMethods;

class AExtension
{
public:
	AExtension(const std::string& name);
	virtual ~AExtension();

public:
	virtual void initialize(IScope* scope);
	virtual void provideMethods(ExtensionMethods& methods) = 0;

public:
	const std::string& getName() const;

protected:

private:
	bool mInitialized;
	std::string mName;
};


typedef std::list<AExtension*> ExtensionList;


}
}


#endif