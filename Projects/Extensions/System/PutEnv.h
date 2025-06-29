
#ifndef Slang_Extensions_System_PutEnv_h
#define Slang_Extensions_System_PutEnv_h


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class PutEnv : public ExtensionMethod
{
public:
	PutEnv()
	: ExtensionMethod(0, "putenv", Designtime::Int32Type::TYPENAME)
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

		*result = Runtime::Int32Type(putenv(const_cast<char*>(param_name.c_str())));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
