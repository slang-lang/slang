
#ifndef ObjectiveScript_Extensions_Apache_ApacheExtension_h
#define ObjectiveScript_Extensions_Apache_ApacheExtension_h


// Library includes

// Project includes
#include <Core/Interfaces/IExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Apache {


class ApacheExtension : public IExtension
{
public:
	ApacheExtension();

	std::string getName() const {
		return "Apache";
	}

	void provideMethods(ExtensionMethods &methods);

private:
	void initialize();
	void readGetData();
	void readPostData();
};


}
}
}



#endif
