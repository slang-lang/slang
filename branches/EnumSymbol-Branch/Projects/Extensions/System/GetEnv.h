
#ifndef ObjectiveScript_Extensions_System_GetEnv_h
#define ObjectiveScript_Extensions_System_GetEnv_h


// Library includes
#include <stdlib.h>

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Method.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


class GetEnv : public Runtime::Method
{
public:
	GetEnv()
	: Runtime::Method(0, "getenv", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("name", Designtime::StringObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_name = (*it++).value().toStdString();

			std::string result_value;

			char *val = getenv(param_name.c_str());
			if (val) {
				result_value = std::string(val);
			}

			*result = Runtime::StringObject(result_value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			mExceptionData = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
