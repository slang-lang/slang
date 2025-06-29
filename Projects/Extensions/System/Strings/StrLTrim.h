
#ifndef Slang_Extensions_System_Strings_StrLTrim_h
#define Slang_Extensions_System_Strings_StrLTrim_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class StrLTrim : public ExtensionMethod
{
public:
	StrLTrim()
	: ExtensionMethod(0, "strltrim", Designtime::StringType::TYPENAME)
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

		*result = Runtime::StringType(::Utils::Tools::stringTrimLeft(param_value));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
