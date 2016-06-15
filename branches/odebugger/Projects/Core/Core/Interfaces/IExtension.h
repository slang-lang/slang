
#ifndef ObjectiveScript_Interfaces_IExtension_h
#define ObjectiveScript_Interfaces_IExtension_h


// Library includes
#include <list>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Runtime {
	class Method;
}

namespace Extensions {


typedef std::list<Runtime::Method*> ExtensionMethods;


class IExtension
{
public:
	virtual ~IExtension() { }

	virtual std::string getName() const = 0;
	virtual void provideMethods(ExtensionMethods& methods) = 0;
};


typedef std::list<IExtension*> ExtensionList;


}
}


#endif
