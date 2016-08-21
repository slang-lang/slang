
#ifndef ObjectiveScript_Extensions_Json_JsonExtension_h
#define ObjectiveScript_Extensions_Json_JsonExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Json {


class JsonExtension : public AExtension
{
public:
	JsonExtension();

public:
	void provideMethods(ExtensionMethods &methods);
};


}
}
}


#endif
