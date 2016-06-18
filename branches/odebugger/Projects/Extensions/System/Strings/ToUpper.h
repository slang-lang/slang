
#ifndef ObjectiveScript_Extensions_System_Strings_ToUpper_h
#define ObjectiveScript_Extensions_System_Strings_ToUpper_h


// Library includes
#include <algorithm>
#include <string>

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
namespace Strings {


class ToUpper : public Runtime::Method
{
public:
	ToUpper()
	: Runtime::Method(0, "toUpper", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("value", Designtime::StringObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		try {
			ParameterList::const_iterator it = params.begin();

			std::string param_value = (*it++).value().toStdString();

			std::transform(param_value.begin(), param_value.end(), param_value.begin(), ::toupper);

			*result = Runtime::StringObject(param_value);
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
}


#endif
