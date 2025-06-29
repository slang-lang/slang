
#ifndef Slang_Extensions_System_GetEnv_h
#define Slang_Extensions_System_GetEnv_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class GetEnv : public ExtensionMethod
{
public:
	GetEnv()
	: ExtensionMethod(0, "getenv", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("envvar", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		std::string param_name = (*it++).value().toStdString();

		std::string result_value;

		char* val = getenv(param_name.c_str());
		if ( val ) {
			result_value = std::string(val);
		}

		*result = Runtime::StringType(result_value);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
