
#ifndef ObjectiveScript_Extensions_System_ToJson_h
#define ObjectiveScript_Extensions_System_ToJson_h


// Library includes

// Project includes
#include <Core/Extensions/ExtensionMethod.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class ToJson : public ExtensionMethod
{
public:
	ToJson();

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}

#endif
