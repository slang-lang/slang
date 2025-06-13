
#ifndef Slang_Extensions_System_Strings_StrFind_h
#define Slang_Extensions_System_Strings_StrFind_h


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class StrFind : public ExtensionMethod
{
public:
	StrFind()
	: ExtensionMethod(0, "strfind", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("source", Designtime::StringType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("target", Designtime::StringType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("position", Designtime::Int32Type::TYPENAME, 0, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		std::string param_source = (*it++).value().toStdString();
		std::string param_target = (*it++).value().toStdString();
		unsigned long param_position = (*it).value().toInt();

		int my_result = (int)param_source.find(param_target, param_position);

		*result = Runtime::Int32Type(my_result);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
