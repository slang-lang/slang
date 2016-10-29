
#ifndef ObjectiveScript_Extensions_System_FromJson_h
#define ObjectiveScript_Extensions_System_FromJson_h


// Library includes

// Project includes
#include <Core/Extensions/ExtensionMethod.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class FromJson : public ExtensionMethod
{
public:
	FromJson();

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}

#endif
