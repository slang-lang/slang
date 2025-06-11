
#ifndef Slang_Extensions_System_IsKnownType_h
#define Slang_Extensions_System_IsKnownType_h


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/BoolType.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/BoolType.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Reflection {


class IsKnownType : public ExtensionMethod
{
public:
	IsKnownType()
	: ExtensionMethod(0, "isKnownType", Designtime::BoolType::TYPENAME)
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

		std::string param_type = (*it++).value().toStdString();

		*result = Runtime::BoolType( Controller::Instance().repository()->findBluePrintObject(param_type) != nullptr );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
