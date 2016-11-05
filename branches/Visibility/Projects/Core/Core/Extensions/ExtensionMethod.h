
#ifndef ObjectiveScript_Core_Core_Extensions_ExtensionMethod_h
#define ObjectiveScript_Core_Core_Extensions_ExtensionMethod_h


// Library includes
#include <string>

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class ExtensionMethod : public Runtime::Method
{
public:
	ExtensionMethod(IScope* parent, const std::string& name, const std::string& type)
	: Runtime::Method(parent, name, type)
	{
		mIsExtensionMethod = true;
	}
};


}


#endif
