
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

}

class AExtension
{
public:
	AExtension(const std::string& name)
	: mName(name)
	{ }
	virtual ~AExtension() { }

public:
	virtual void initialize(ObjectiveScript::IScope* scope) = 0;
	virtual void provideMethods(ObjectiveScript::Extensions::ExtensionMethods& methods) = 0;

public:
	const std::string& getName() const {
		return mName;
	}

private:
	std::string mName;
};


namespace ObjectiveScript {
namespace Extensions {


typedef std::list<AExtension*> ExtensionList;


}
}


#endif
