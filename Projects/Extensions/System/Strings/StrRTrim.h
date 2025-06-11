
#ifndef Slang_Extensions_System_Strings_StrRTrim_h
#define Slang_Extensions_System_Strings_StrRTrim_h


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class StrRTrim : public ExtensionMethod
{
public:
	StrRTrim()
	: ExtensionMethod(0, "strrtrim", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("value", Designtime::StringType::TYPENAME, 0));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		std::string param_value = (*it++).value().toStdString();

		*result = Runtime::StringType(::Utils::Tools::stringTrimRight(param_value));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
