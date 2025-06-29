
#ifndef Slang_Extensions_System_Strings_StrPos_h
#define Slang_Extensions_System_Strings_StrPos_h


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
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


class StrPos : public ExtensionMethod
{
public:
	StrPos()
	: ExtensionMethod(0, "strpos", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("value", Designtime::StringType::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("index", Designtime::Int32Type::TYPENAME, 0));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		std::string param_value = (*it++).value().toStdString();
		unsigned long param_index = (*it++).value().toInt();

		if ( param_index > param_value.size() ) {
			throw Runtime::Exceptions::SizeException("index " + Utils::Tools::toString(param_index) + " out of bounds (" + Utils::Tools::toString(param_value.size()) + ")");
		}

		std::string result_value = param_value.substr(param_index, 1);

		*result = Runtime::StringType(result_value);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
