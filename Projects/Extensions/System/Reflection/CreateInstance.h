
#ifndef Slang_Extensions_System_CreateInstance_h
#define Slang_Extensions_System_CreateInstance_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Designtime/BuildInTypes/UserType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Reflection {


class CreateInstance : public ExtensionMethod
{
public:
	CreateInstance()
	: ExtensionMethod(0, "createInstance", Designtime::UserType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("type", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_type = (*it++).value().toStdString();

		auto* newInstance = Controller::Instance().repository()->createReference(param_type, ANONYMOUS_OBJECT, PrototypeConstraints(), Repository::InitilizationType::Final);

		*result = *newInstance;

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
