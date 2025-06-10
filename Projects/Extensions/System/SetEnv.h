
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
#include <Core/Tools.h>

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
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_name = (*it++).value().toStdString();
			std::string param_value = (*it++).value().toStdString();

#ifdef _WIN32
			*result = Runtime::Int32Type(SetEnvironmentVariable(param_name.c_str(), param_value.c_str()));
#else
			auto param_overwrite = (*it++).value().toInt();

			*result = Runtime::Int32Type(setenv(param_name.c_str(), param_value.c_str(), param_overwrite));
#endif
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringType(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
