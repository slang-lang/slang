
#ifndef ObjectiveScript_Extensions_Apache_ApacheExtension_h
#define ObjectiveScript_Extensions_Apache_ApacheExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>
#include <Core/Interfaces/IScope.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Apache {


class ApacheExtension : public AExtension
{
public:
	ApacheExtension();

	void initialize(IScope* scope);
	void provideMethods(ExtensionMethods &methods);

private:
	void readGetData();
	void readPostData();
};


}
}
}



#endif
