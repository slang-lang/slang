
#ifndef ObjectiveScript_Core_Core_Extensions_ExtensionMethod_h
#define ObjectiveScript_Core_Core_Extensions_ExtensionMethod_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Common/Method.h>
#include <Core/Common/Types.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class ExtensionMethod : public Common::Method
{
public:
	ExtensionMethod(IScope* parent, const std::string& name, const std::string& type, Mutability::E mutabilty = Mutability::Const)
	: Common::Method(parent, name, Common::TypeDeclaration(type))
	{
		mIsExtensionMethod = true;
		mMethodMutability = mutabilty;
		mMutability = Mutability::Modify;
	}

	virtual Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token) = 0;
};

typedef std::list<ExtensionMethod*> ExtensionMethods;


}
}


#endif
