
#ifndef ObjectiveScript_Extensions_System_FromJson_h
#define ObjectiveScript_Extensions_System_FromJson_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class FromJson : public Runtime::Method
{
public:
	FromJson();

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token);
};


}
}

#endif
