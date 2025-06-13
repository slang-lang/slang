
#ifndef Slang_Extensions_System_Strings_ToLower_h
#define Slang_Extensions_System_Strings_ToLower_h


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


class ToLower : public ExtensionMethod
{
public:
	ToLower()
	: ExtensionMethod(0, "toLower", Designtime::StringType::TYPENAME)
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

		std::transform(param_value.begin(), param_value.end(), param_value.begin(), ::tolower);

		*result = Runtime::StringType(param_value);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
