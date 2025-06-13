
#ifndef Slang_Extensions_System_Strings_ToUpper_h
#define Slang_Extensions_System_Strings_ToUpper_h


// Library includes
#include <algorithm>
#include <string>

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class ToUpper : public ExtensionMethod
{
public:
	ToUpper()
	: ExtensionMethod(0, "toUpper", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("value", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		std::string param_value = (*it++).value().toStdString();

		std::transform(param_value.begin(), param_value.end(), param_value.begin(), ::toupper);

		*result = Runtime::StringType(param_value);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
