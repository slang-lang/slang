
#ifndef ObjectiveScript_Core_Core_Extensions_ExtensionMethod_h
#define ObjectiveScript_Core_Core_Extensions_ExtensionMethod_h


// Library includes
#include <string>

// Project includes
#include <Core/Common/Method.h>
#include <Core/Common/Types.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class ExtensionMethod : public Common::Method
{
public:
	ExtensionMethod(IScope* parent, const std::string& name, const std::string& type, Mutability::E mutabilty = Mutability::Const)
	: Common::Method(parent, name, type)
	{
		mIsExtensionMethod = true;
		mMethodMutability = mutabilty;
	}

	virtual Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token) = 0;
};


}


#endif