
#ifndef Slang_Extensions_System_SetEnv_h
#define Slang_Extensions_System_SetEnv_h


// Library includes
#include <cstdlib>
#ifdef _WIN32
	// Win32 only methods
#	include <Windows.h>
#else
	// Unix/Linux only
#endif

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class SetEnv : public ExtensionMethod
{
public:
	SetEnv()
	: ExtensionMethod(0, "setenv", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("name", Designtime::StringType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::StringType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("overwrite", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_name  = (*it++).value().toStdString();
		auto param_value = (*it++).value().toStdString();

#ifdef _WIN32
		*result = Runtime::Int32Type(SetEnvironmentVariable(param_name.c_str(), param_value.c_str()));
#else
		auto param_overwrite = (*it++).value().toInt();

		*result = Runtime::Int32Type(setenv(param_name.c_str(), param_value.c_str(), param_overwrite));
#endif

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
