
#ifndef ObjectiveScript_Extensions_Json_JsonExtension_h
#define ObjectiveScript_Extensions_Json_JsonExtension_h


// Library includes

// Project includes
#include <Core/Interfaces/IExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Json {


class JsonExtension : public IExtension
{
public:
	std::string getName() const {
		return "Json";
	}

	void provideMethods(ExtensionMethods &methods);
};


}
}
}


#endif
